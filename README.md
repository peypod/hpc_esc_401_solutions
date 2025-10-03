# hpc_esc_401_solutions

## Assignment 2

### Exercise 2

The default programming environment is cray. 
the command `module spider` shows all modules; the entry for PrgEnv-gnu shows that it requires cray to be loaded.
Similarly, `module avail` shows all available modules, which is a much smaller subset than shown with spider.
`module list` simply shows the currently loaded modules. When swapping between programming environments,
the difference between cray and gnu can be seen by the change in module in `module list`.

The code can be compiled with `make all`. As can be seen in the Makefile, all compiles all files.

# Exercise 3

WIth the -A flag, the squeue filters for the specific user. Therefore, filtering for a nonexistent user such as with `squeue -A k` will print only the header.

# Exercise 4


With a lower number of threads, the OpenMP version runs at a comparable speed. Interestingly enough, there seems to be a sweet spot at about 6 nodes where the performance is minimal by a marginal amount.

Changing the compiler optimization has a significant impact on processing time; it took 22.64s to compute.


 






