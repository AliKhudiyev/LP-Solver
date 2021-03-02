
#pragma once

#include "variable.hpp"
#include "tableau.hpp"
#include <vector>
#include <initializer_list>

#define LP_LESS_THAN 0
#define LP_LESS_THAN_OR_EQUAL 1
#define LP_GREATER_THAN 2
#define LP_GREATER_THAN_OR_EQUAL 3
#define LP_EQUAL 4

#define LP_MAXIMIZE 0
#define LP_MINIMIZE 1

#define LP_OPTIMAL 0
#define LP_FEASIBLE 1
#define LP_NONE 2

namespace lp{
  using namespace utils;
  using status_t = char;
  
  class Solver{
  private:
    size_t m_basisVariableCount = 0;
    std::vector<Variable> m_variables;
    std::vector<double> m_objective;
    std::vector<std::vector<double>> m_constraints;
    std::vector<char> m_operators;
    bool m_goal;
    
  public:
    Solver() = default;
    ~Solver(){}

    void add_variable(const Variable& variable){
      m_variables.push_back(variable);
      m_basisVariableCount += 1;
    }
    void set_objective(const std::vector<double>& coefficients, bool goal){
      m_objective = coefficients;
      m_goal = goal;
    }
    void set_objective(const std::initializer_list<double>& coefficients, bool goal){
      std::vector<double> coefs;
      for(auto it=coefficients.begin(); it!=coefficients.end(); ++it){
	coefs.push_back(*it);
      }
      set_objective(coefs, goal);
    }
    
    void subject_to(const std::vector<double>& coefficients, char operator_, double number){
      auto constraint = coefficients;
      constraint.push_back(number);
      m_constraints.push_back(constraint);
      m_operators.push_back(operator_);

      if(operator_ != LP_EQUAL){
	auto slack = Variable();
	m_variables.push_back(slack);
      }
    }
    void subject_to(const std::initializer_list<double>& coefficients, char operator_, double number){
      std::vector<double> coefficients_;
      for(auto it=coefficients.begin(); it!=coefficients.end(); ++it){
	coefficients_.push_back(*it);
      }
      subject_to(coefficients_, operator_, number);
    }
    void remove(const std::vector<double>& coefficients, char operator_, double number){
      // TO DO
    }
    
    status_t solve(){
      /* --- */
      Tableau tableau(m_constraints.size()+2, m_variables.size()+1);
      std::vector<std::vector<double>> constraints;
      size_t slack_index = m_basisVariableCount, index = 0;

      for(size_t i=0; i<m_objective.size(); ++i){
	tableau.at(0, i) = m_objective[i];
      }
      for(size_t i=0; i<m_variables.size()+1-m_objective.size(); ++i){
	tableau.at(0, m_objective.size()+i) = 0.0;
      }
      
      for(size_t i=0; i<m_constraints.size(); ++i){
	std::vector<double> constraint;
	for(size_t j=0; j<m_constraints[i].size()-1; ++j){
	  constraint.push_back(m_constraints[i][j]);
	  tableau.at(i, j) = m_constraints[i][j];
	}
	for(size_t j=0; j<m_variables.size()-m_basisVariableCount; ++j){
	  constraint.push_back(0.0);
	  tableau.at(i, m_basisVariableCount+j) = 0.0;
	}
	
        if(m_operators[i] == LP_LESS_THAN || m_operators[i] == LP_LESS_THAN_OR_EQUAL){
	  constraint[slack_index] = 1.0;
	  tableau.at(i, slack_index) = 1.0;
	  ++slack_index;
	}
	else if(m_operators[i] == LP_GREATER_THAN || m_operators[i] == LP_GREATER_THAN_OR_EQUAL){
	  constraint[slack_index] = -1.0;
	  tableau.at(i, slack_index) = -1.0;
	  ++slack_index;
	}
	constraint.push_back(m_constraints[i].back());
	tableau.at(i, m_variables.size()) = m_constraints[i].back();
      }

      for(size_t i=0; i<m_objective.size(); ++i){
	// printf("%lf :\n", m_objective[i]);
	tableau.at(m_constraints.size(), i) = m_objective[i];
      }
      /* --- */

      index = 0;
      std::cout << "Tableau:\n" << tableau << "\n";
      do{
	// TO DO
	size_t row_index, col_index;

	// Find column index for pivot vector
	col_index = tableau.get_index(/*index:*/m_constraints.size(), /*from_row:*/true);
	if(col_index == -1){
	  printf(" -> (column)Stop! [info: cannot be further optimized]\n");
	  break;
	}
	printf(" dbg pivot column: %zu\n", col_index);
	// Find row index for pivot element
	row_index = tableau.get_index(col_index, false);
	if(row_index == -1){
	  printf(" -> (row)Stop! [info: cannot select any pivot element]\n");
	  break;
	}
	printf(" dbg pivot row: %zu; element: %lf\n", row_index, tableau.at(row_index, col_index));

	// Processing with pivot
	double pivot = tableau.at(row_index, col_index);
	
	tableau.mult(1.0 / pivot, row_index);
	for(size_t i=0; i<m_constraints.size()+2; ++i){
	  if(i == row_index) continue;
	  tableau.add(i, row_index, i, -tableau.at(i, col_index));
	}

	std::cout << "Tableau:\n" << tableau << "\n";
      }while(index++ < 10);
      printf(" dbg stopped @%zu iteration...\n", index);
      return 0;
    }
    std::vector<double> get_solution() const{
      std::vector<double> vec;
      for(const auto& variable: m_variables){
	vec.push_back(variable.get());
      }
      return vec;
    }
  };
  
}
