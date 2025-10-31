#include "mpi.h"
#include <stdio.h>

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes and rank of the process
    int n_proc, my_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &n_proc);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int my_sum = 0;
    int send_rank = my_rank;  // Value to send
    int recv_rank = 0;        // Value to receive

    // Compute ranks of left and right neighbours (with wrap-around)
    int left_rank = (my_rank - 1 + n_proc) % n_proc;
    int right_rank = (my_rank + 1) % n_proc;

    // Loop over the number of processes
    for (int i = 0; i < n_proc; i++) {
       
        MPI_Request reqs[2];

        // Post receive first
        MPI_Irecv(&recv_rank, 1, MPI_INT, left_rank, 0, MPI_COMM_WORLD, &reqs[0]);
        // Then post send
        MPI_Isend(&send_rank, 1, MPI_INT, right_rank, 0, MPI_COMM_WORLD, &reqs[1]);

        // Wait for both to complete
        MPI_Waitall(2, reqs, MPI_STATUSES_IGNORE);
	 

        // Update the sum and send buffer
        my_sum += recv_rank;
        send_rank = recv_rank;
    }

    printf("I am process %d out of %d and the sum is %d\n", my_rank, n_proc, my_sum);

    // Finalize the MPI environment
    MPI_Finalize();
}
