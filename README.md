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

# Assignment 4



# Part 1

## Accessing Directories

Home directory:
drwx------ 2 kpowell uzh8 4096 Oct 16 16:49 /users/kpowell
Scratch directory:
drwxr-x---+ 2 kpowell uzh8 4096 Sep 24 13:22 /capstor/scratch/cscs/kpowell

Accessing other students / group members directories isn't possible, as only the user has any permissions for them, unlike the scratch directory.

drwx------ 2 ggomezde uzh8 4096 Oct 10 09:23 ggomezde

## New Directory permissions

The permissions of a new directory are: drwxr-xr-x
So full permission for user, and read-execute permissions for group and other users.

## Accessing users/meberlei

The permissions for meberlei are the same as for other uzh8 users, drwx------.
It is not possible to view or edit anything within that directory, regardless of if the path exists or not.

## Full permission for user only

Command used: chmod 700 dir_name

## File on Scratch

text_file.txt created, permissions set using chmod 770 text_file.txt

## File with permissions 000

A file becomes uninteractable, as no permissions exist for it.
Although the file can't be read, written, or executed, it's permissions can still be modified to make it accessible again.


# Part 2


## Binary Matching regex

As it isn't specified on the question sheet, these are the regex's that would match the entire binary string.

```
- end with 00
	.*00$
- start and end with 1
	^1.*1$
- contain the pattern 110
	.*110.*
- contain at least three times a 1
	(.*1){3}.*
- contain at least three consecutive 1s
	.*1{3}.*

  ```


## Temperature Reading

The average temperature was computed as 20.57.

# Prime factoring

## Factor command

factor prints a number followed by its prime factorization.  
factor 20 prints:
	20: 2 2 5
showing that it has 3 prime factors, indicating that it's a composite.
factor 31 prints:
	31: 31
the fact that it only has itself as a prime factor demonstrates that it's a prime number.

## Distinguishing primes

by piping the output of factor into wc -w, the number of words is counted, i.e. the amount of factors printed. If the resulting number is 2, e.g. for "31: 31", then the number is a prime.

## Capturing and processing outputs

The factor command output is captured into a variable. On a seperate line, that value is then piped into wc and also captured into a variable, on which the final if-block is run to test whether the word count is 2 and therefore the number prime.

## Performance timings

4230283 is a prime and 457286217100 is a composite. Running on the eiger server, both took ~10ms to compute.







