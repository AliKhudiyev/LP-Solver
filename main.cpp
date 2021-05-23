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
  /*
  lp::Variable c;
  solver.add_variable(c);
  
  solver.set_objective({-3, -1, 1}, LP_MAXIMIZE);
  solver.subject_to({-3, -1, 5}, LP_GREATER_THAN_OR_EQUAL, 18);
  solver.subject_to({-1, -1, 2}, LP_GREATER_THAN_OR_EQUAL, 5);
  solver.subject_to({-1, 1, 1}, LP_LESS_THAN_OR_EQUAL, 6);
  CORRECT!
  */
  /*
  solver.set_objective({2, 3}, LP_MAXIMIZE);
  solver.subject_to({1, 1}, LP_GREATER_THAN_OR_EQUAL, 3);
  solver.subject_to({1, -2}, LP_LESS_THAN_OR_EQUAL, 4);
  CORRECT!
  */
  /*
  lp::Variable c, d;
  solver.add_variable(c);
  solver.add_variable(d);
  
  solver.set_objective({2, 3, 21, 2}, LP_MAXIMIZE);
  solver.subject_to({1, 1, -3, 0}, LP_LESS_THAN_OR_EQUAL, 2);
  solver.subject_to({2, -1, 1, 2}, LP_LESS_THAN_OR_EQUAL, 2);
  solver.subject_to({2, 1, 2, -1}, LP_LESS_THAN_OR_EQUAL, 1);
  CORRECT!
  */
  /*
  lp::Variable c;
  solver.add_variable(c);
  
  solver.set_objective({4, -1, 1}, LP_MAXIMIZE);
  solver.subject_to({2, 1, 1}, LP_LESS_THAN_OR_EQUAL, 6);
  solver.subject_to({-2, 2, 0}, LP_LESS_THAN_OR_EQUAL, 4);
  CORRECT!
  */
  /*
  lp::Variable c, d, e;
  solver.add_variable(c);
  solver.add_variable(d);
  solver.add_variable(e);

  solver.set_objective({1, 1, 1, 1, 1}, LP_MAXIMIZE);
  solver.subject_to({1, 3, 2, 0, 1}, LP_LESS_THAN_OR_EQUAL, 5);
  solver.subject_to({1, 1, 4, 1, 0}, LP_LESS_THAN_OR_EQUAL, 3);
  CORRECT!
  */
  /*
  solver.set_objective({1, 1}, LP_MAXIMIZE);
  solver.subject_to({2, 3}, LP_GREATER_THAN_OR_EQUAL, 3);
  solver.subject_to({-3, 2}, LP_LESS_THAN_OR_EQUAL, -1);
  CORRECT!
  */
  /*
  solver.set_objective({24, 16}, LP_MAXIMIZE);
  solver.subject_to({1, 2}, LP_LESS_THAN_OR_EQUAL, 150);
  solver.subject_to({4, 2}, LP_LESS_THAN_OR_EQUAL, 400);
  Exam Q2
  */
  /*
  lp::Variable c;
  solver.add_variable(c);

  solver.set_objective({3, 2, 1}, LP_MAXIMIZE);
  solver.subject_to({1, 1, 1}, LP_LESS_THAN_OR_EQUAL, 3);
  solver.subject_to({2, 0, 1}, LP_GREATER_THAN_OR_EQUAL, 2);
  solver.subject_to({-1, 1, 1}, LP_GREATER_THAN_OR_EQUAL, 0);
  Exam Q3
  */

  /*
  solver.set_objective({-200, 500}, LP_MAXIMIZE);
  solver.subject_to({1, 0}, LP_LESS_THAN_OR_EQUAL, 200);
  solver.subject_to({0, 1}, LP_LESS_THAN_OR_EQUAL, 170);
  solver.subject_to({1, 0}, LP_GREATER_THAN_OR_EQUAL, 100);
  // solver.subject_to({0, 1}, LP_LESS_THAN_OR_EQUAL, 170);
  solver.subject_to({0, 1}, LP_GREATER_THAN_OR_EQUAL, 80);
  solver.subject_to({1, 1}, LP_GREATER_THAN_OR_EQUAL, 200);
  */

  lp::Variable c;
  solver.add_variable(c);
  solver.set_objective({-20, 36, 8}, LP_MAXIMIZE);
  solver.subject_to({-2, 10, 2}, LP_LESS_THAN_OR_EQUAL, -4);
  solver.subject_to({-1, 1, 8}, LP_LESS_THAN_OR_EQUAL, -2);
  
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
