
# Exercise 1

The openMP solution consistently outperforms openACC, always taking about 0.06s.
The openACC solution needs a minimum of 0.86s, with about 1.3s at the highest. This may be due to the overhead needed for writing and reading from GPU memory.

# Exercise 2

## naive
In the naive implementation, data gets moved data to/from the device every iteration, which is unnecessary and very costly.

## nocopies
in blur_twice_gpu_nocopies, the arrays are moved once and all iterations are done on-device: this reduced transfer overhead is much faster than the naive version.

## Comparison

Naive:
dispersion 1D test of length n = 65540 : 0.500031MB
==== success ====
Host version took 0.0375636 s (0.000375636 s/step)
GPU version took 0.053732 s (0.00053732 s/step)

Nocopies:
dispersion 1D test of length n = 65540 : 0.500031MB
==== success ====
Host version took 0.0369111 s (0.000369111 s/step)
GPU version took 0.036952 s (0.00036952 s/step)

As can be seen, with increasing N the nocopies version is able to outscale the CPU implementation in performance.


# Exercise 3

## Why race conditions?
The loop updates the single shared variable `sum` from many parallel threads; if multiple threads add to `sum` concurrently, the updates can interleave and overwrite each other, producing incorrect results.

## What keyword prevents this?
A reduction can be used to avoid the race: each thread (or gang) accumulates into a private partial sum and the runtime/compiler combines them safely at the end (e.g. `reduction(+:sum)`).


## Comparison

dot product OpenACC of length n = 65536 : 0.5MB
expected 588374 got 588374: success
Host kernel took 0.000174587 s
GPU kernel took 0.000166107 s

At higher n values, the GPU version is able to outperform the CPU version.
