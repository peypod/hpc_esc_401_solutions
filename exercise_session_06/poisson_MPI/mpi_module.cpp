#include "mpi.h"
#include <stdio.h>
#include "init.h"

int start_MPI(int* my_rank, int* size){
        printf("Setting MPI environment\n");
        MPI_Init(NULL,NULL);
        MPI_Comm_size(MPI_COMM_WORLD,size);
        MPI_Comm_rank(MPI_COMM_WORLD,my_rank);

        return 0;
}

int close_MPI(){
        MPI_Finalize();
        return 0;
}

int mpi_get_domain(int nx, int ny, int my_rank, int size, int* min_x, int* max_x, int* min_y, int* max_y){
        /*
        define corners or local domains
        */

	// Method used: II, dividing domains along x-axis and peeling remainder along first rem domains


        // size per domain
        int batch = nx / size;
        // remainder of domain division
        int rem  = nx % size;
        int local_nx;

        if (my_rank < rem) {
                // appends domain with remainder
                local_nx = batch + 1;
                *min_x = my_rank * local_nx;
        } else {
		// set span normally
                local_nx = batch;
                // set min_x relative to batch size per rank
		//offset with remainder
                *min_x = rem * (batch + 1) + (my_rank - rem) * batch;
        }
        // set max_x relative to min_x
        *max_x = *min_x + local_nx;

        // set y range of domain
        *min_y = 0;
        *max_y = ny;
        printf("I am rank %d and my domain is: xmin, xmax, ymin, ymax: %d %d %d %d\n",my_rank,*min_x,*max_x,*min_y,*max_y);
        return 0;
}

int halo_comm(params p, int my_rank, int size, double** u, double* fromLeft, double* fromRight){

        /*this function, vectors fromLeft and fromRight should be received from the neighbours of my_rank process*/
        /*if you want to implement also cartesian topology, you need fromTop and fromBottom in addition to fromLeft a
        nd fromRight*/

        for (int j=0;j<(p.ymax - p.ymin);j++) {fromLeft[j] = 0; fromRight[j] = 0;} //initialize fromLeft and fromRight

        /* define columns to be sent to right neighbour and to the left neighbour, 
        also receive one both form left and right neighbour*/

	// Method used: II, non blocking communication
	

        int local_nx = p.xmax - p.xmin;
        int local_ny = p.ymax - p.ymin;

	// neighbour ranks, with wrap-around
        int left_rank  = (p.xmin == 0) ? MPI_PROC_NULL : my_rank - 1;
        int right_rank = (p.xmax == p.nx) ? MPI_PROC_NULL : my_rank + 1;

        double* column_to_right = new double [local_ny];
        for (int j=0;j<(local_ny);j++) column_to_right[j] = u[local_nx - 1][j]; 
        double* column_to_left = new double [p.ymax - p.ymin];
        for (int j=0;j<(local_ny);j++) column_to_left[j] = u[0][j]; 

        // array of comms for MPI_Waitall
        MPI_Request reqs[4];
        int reqcount = 0;

        //  do receives first, track with reqs array
        MPI_Irecv(fromLeft,  local_ny, MPI_DOUBLE, left_rank,  200, MPI_COMM_WORLD, &reqs[reqcount++]);
        MPI_Irecv(fromRight, local_ny, MPI_DOUBLE, right_rank, 100, MPI_COMM_WORLD, &reqs[reqcount++]);

        // sends after receives
        MPI_Isend(column_to_left,  local_ny, MPI_DOUBLE, left_rank,  100, MPI_COMM_WORLD, &reqs[reqcount++]);
        MPI_Isend(column_to_right, local_ny, MPI_DOUBLE, right_rank, 200, MPI_COMM_WORLD, &reqs[reqcount++]);

        // Wait for all comms to complete
        if (reqcount > 0)
                MPI_Waitall(reqcount, reqs, MPI_STATUSES_IGNORE);
        return 0;
}

int ALLREDUCE(double* loc_diff, double* loc_sumdiff){

        MPI_Allreduce(loc_diff, loc_sumdiff, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
        return 0;
}

