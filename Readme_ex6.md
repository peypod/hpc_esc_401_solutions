
# Exercise 1

The execution freezes due to each process waiting for another, leading to a circular waiting that causes a deadlock.

## change to two groups

by dividing the processes into two groups, it forms a neater chain where a process receives first from a process that sends first.
## change to async

changing this setup to use asynchronous messaging resolves the deadlock, as the processes are no longer stuck waiting for each-other


# Exercise 2

Approximated pi value: 3.141593
