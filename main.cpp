#include <iostream>
#include <limits>
#include <cmath>
#include "include/solver.hpp"

using namespace std;

int main(int argc, char** argv){
  LP_PRINT_INFO;
  
  lp::Variable a, b;
  lp::Solver solver;
  
  solver.add_variable(a);
  solver.add_variable(b);

  /*
  solver.set_objective({3, 2}, LP_MAXIMIZE);
  solver.subject_to({1, 3}, LP_GREATER_THAN_OR_EQUAL, 10);
  solver.subject_to({2, 1}, LP_LESS_THAN_OR_EQUAL, 9);
  CORRECT!
  */
  /*
  solver.set_objective({3, 5}, LP_MAXIMIZE);
  solver.subject_to({1, 0}, LP_LESS_THAN_OR_EQUAL, 4000);
  solver.subject_to({0, 1}, LP_LESS_THAN_OR_EQUAL, 5000);
  solver.subject_to({1, 2./3.}, LP_LESS_THAN_OR_EQUAL, 6000);
  CORRECT!
  */
  lp::Variable c;
  solver.add_variable(c);
  
  solver.set_objective({-3, -1, 1}, LP_MAXIMIZE);
  solver.subject_to({-3, -1, 5}, LP_GREATER_THAN_OR_EQUAL, 18);
  solver.subject_to({-1, -1, 2}, LP_GREATER_THAN_OR_EQUAL, 5);
  solver.subject_to({-1, 1, 1}, LP_LESS_THAN_OR_EQUAL, 6);
  
  auto status = solver.solve();

  /*
  if(status == LP_NONE){
    return -1;
  }
  auto solution = solver.get_solutuion();
  for(const auto& number: solution){
    printf("%lf, ", number);
  }
  printf("\n");
  */
  return 0;
}
