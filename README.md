# LP-Solver

(*This project has been partially developed on a discord live stream.*)

If you have a linear (programming) problem then you should have a system of inequalities in the following form:

- Objective function to be minimized/maximized:

  z = c[0] \* x[0] + c[1] \* x[1] + ...

- Constraints:

  a[0][0] \* x[0] + a[0][1] \* x[1] + ... <= b[0]

  a[1][0] \* x[0] + a[1][1] \* x[1] + ... <= b[1]

  . <= .

  . <= .

  . <= .

If you want to solve such problem then you may use different techniques which leads to the same solution sooner or later. This program uses the Simplex method created by George Dantzig. To deal with artificial variables (if any), it applies the 2-phase method to the problem.

## How to use

This is a header-only library, so, you only need to include the header file in your program. The API is pretty straight forward; all the functions are self-documented and easy to use. To solve your linear problem, proceed as shown below:

- Create your variables with boundaries (lp::Variable)
- Create your solver (lp::Solver)
- Add all your variables to the solver (*member function*: add_variable(variable))
- Add an objective function to the solver (*member function*: set_objective(objective))
- Add as many constraints as you want to the solver (*member function*: subject_to(constraint))
- Invoke the solver (*member function*: solve(void))

### Example

- Objective function:

  *Maximize* (3x + 2y)

- Constraints:

  x + 3y <= 10

  2x + y <= 9

```c
#include "solver.hpp"

using namespace std;

int main(){
    lp::Variable a, b;
    lp::Solver solver;

    solver.add_variable(a);
    solver.add_variable(b);

    solver.set_objective({3, 2}, LP_MAXIMIZE);
    solver.subject_to({1, 3}, LP_LESS_THAN_OR_EQUAL, 10);
    solver.subject_to({2, 1}, LP_LESS_THAN_OR_EQUAL, 9);

    auto status = solver.solve();
    
    if(status == LP_OPTIMAL){         // The solution is optimal
        // ...
    }
    else if(status == LP_FEASIBLE){   // The solution is not optimal but feasible
        // ...
    }
    else{                             // LP_NONE: No feasible solution
        return -1;
    }

    auto solution = solver.get_solution();
    for(const auto& number: solution){
        printf("%lf, ", number);
    }	printf("\n");
    return 0;
}
```