# hpc_esc_401_solutions

## Assignment 2

### Exercise 2

The default programming environment is cray. 
the command `module spider` shows all modules; the entry for PrgEnv-gnu shows that it requires cray to be loaded.
Similarly, `module avail` shows all available modules, which is a much smaller subset than shown with spider.
`module list` simply shows the currently loaded modules. When swapping between programming environments,
the difference between cray and gnu can be seen by the change in module in `module list`.

The code can be compiled with `make all`. As can be seen in the Makefile, all compiles all files.

### Exercise 3

WIth the -A flag, the squeue filters for the specific user. Therefore, filtering for a nonexistent user such as with `squeue -A k` will print only the header.

### Exercise 4

With a lower number of threads, the OpenMP version runs at a comparable speed. Interestingly enough, there seems to be a sweet spot at about 6 nodes where the performance is minimal by a marginal amount.

Changing the compiler optimization has a significant impact on processing time; it took 22.64s to compute.

# Assignment 2

## Exercise 1

The default version takes approx. 1.483s, whereas the MPI version takes about 1.5ms longer. This minor difference can be explained by the overhead introduced by initializing MPI, even if only a single process is used.

## Exercise 2

The result for the sum is consistently 10022429073.341873, regardless of optimization. The time taken for optimizations -O, -O1 -O2, -O3 are: 1.958, 1.955, 1.081, 1.082, in seconds.
There is a considerable speedup from -O2 and -O3 to twice as fast. Likely key improvements were predictive commoning and loop unrolling. The code could be made even faster by using ffastmath or AVX.

The omp parallelization was added right before the for loop, and the existing sum variable replaced. However, running it with 8 to 128 cpus did not make any difference - it consistently took ~1.0s.

## Exercise 3

If the data that each process works on is small enough, it is possible for the entire data to fit into the CPU cache(s). This provides a very significant speedup, as there aren't any "round trips" required to access the main memory, which is magnitudes slower than accessing the caches.

 






