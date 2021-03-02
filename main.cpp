#include <iostream>
#include "solver.hpp"

using namespace std;

int main(int argc, char** argv){
  lp::Variable a, b;
  lp::Solver solver;
  
  solver.add_variable(a);
  solver.add_variable(b);

  solver.set_objective({3 ,2}, LP_MAXIMIZE);
  solver.subject_to({1, 3}, LP_LESS_THAN_OR_EQUAL, 10);
  solver.subject_to({2, 1}, LP_LESS_THAN_OR_EQUAL, 9);

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
