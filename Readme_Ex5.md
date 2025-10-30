# Assignment 5


## Exercise 1

init_f sets up the right-hand side of the Poisson equation and sets the boundary values for the initial condition.

jacobi_step applies one relaxation step of the Jacobi iterative method to converge towards the steady-state solution of the Poisson equation.

norm_diff measures how much the solution changed between two Jacobi iterations and measures how much the solution has converged.

Note: the algorithm doesn't seem to converge in my implementation, however I haven't found any reasons for it

## Exercise 3

Parallelizing the second loop leads to inconsistent results due to the race condition.
This isn't an issue with the first loop, as the order and batching has no effect on the final result.

Using the directives at the for loops solves this - reduction being the most efficient among these.


