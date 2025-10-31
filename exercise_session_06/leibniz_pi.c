#include "mpi.h"
#include <stdio.h>

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes and rank of the process
    int n_proc, my_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &n_proc);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    long N = 100000000;
    long batch_size = N / n_proc;

    long init_n = batch_size * my_rank;

    double partial_sum = 0.0;
    double global_sum = 0.0;

    // Loop over the number of processes
    for (long i = 0; i < batch_size; i++) {

	long k = init_n + i;
        long divisor = 2 * k + 1;
        double term = ((i % 2 == 0) ? 1.0 : -1.0);
        
        double val = term / (double)divisor;

        partial_sum += val;
    }
    
    int data_count = n_proc - 1;
    MPI_Reduce(&partial_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    global_sum = global_sum * 4.0;
    if (my_rank == 0) {
        printf("global sum: %f", global_sum);
    }

    // Finalize the MPI environment
    MPI_Finalize();
    return 0;
}

