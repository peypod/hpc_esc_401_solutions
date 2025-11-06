#include "jacobi.h"
#include <math.h>
#include "mpi_module.h"

/**
 * @brief      Computes norm of the difference between two matrices
 *
 * @param[in]  p     Parameters
 * @param      mat1  The matrix 1
 * @param      mat2  The matrix 2
 *
 * @return     Returns \sqrt{\sum(mat1_{ij} - mat2_{ij})^2/(nx*ny)}
 */
double norm_diff(params p, double** mat1, double** mat2){

    int local_nx = p.xmax - p.xmin;
    int local_ny = p.ymax - p.ymin;
    //printf("Here, in norm_diff() function, change the serial implementation to MPI setup\n");
    
    double local_sum = 0.0;
    for (int i = 0; i < local_nx; i++) {
        for (int j = 0; j < local_ny; j++) {
            double diff = mat1[i][j] - mat2[i][j];
            local_sum += diff * diff;
        }
    } 
	
    // MPI_Allreduce on local_sum to global_sum 
    double global_sum = 0.0;
    ALLREDUCE(&local_sum, &global_sum);
    
    double ret = sqrt(global_sum / ((double)p.nx * p.ny));

    //printf("global norm: %e \n", ret);

    return ret;
}

/**
 * @brief      Compute a Jacobi iteration to solve Poisson equation. This function updates
 *             u_new and u_old in-place.
 *
 * @param[in]  p      Parameters
 * @param      u_new  The new solution
 * @param      u_old  The old solution
 * @param      f      The source term
 */
void jacobi_step(params p, double** u_new, double** u_old, double** f, int my_rank, int size){

    int local_nx = p.xmax - p.xmin;
    int local_ny = p.ymax - p.ymin;
    
    double dx = 1.0/((double)p.nx - 1);
    double dy = 1.0/((double)p.ny - 1);

    double* fromLeft = new double[p.ymax - p.ymin]; 
    double* fromRight = new double[p.ymax - p.ymin];

    //for (int i=p.xmin; i<p.xmax; i++){
    //    for (int j=p.ymin; j<p.ymax; j++){
    //        u_old[i - p.xmin][j - p.ymin] = u_new[i - p.xmin][j - p.ymin];
    //    }
    //}
    for (int i = 0; i < local_nx; i++)
        for (int j = 0; j < local_ny; j++)
            u_old[i][j] = u_new[i][j];

    halo_comm(p, my_rank, size, u_new, fromLeft, fromRight); 

    //printf("Function jacobi_step in jacobi.cpp : adapt the update of u_new.\n");
    for (int i = 0; i < local_nx; i++) {
        int gi = p.xmin + i; // global x-index
        if (gi == 0 || gi == p.nx - 1) continue; // skip physical boundaries

        for (int j = 0; j < local_ny; j++) {
            int gj = p.ymin + j; // global y-index
            if (gj == 0 || gj == p.ny - 1) continue;

            // Fetch neighbor values:
            double left  = (i == 0)
                           ? fromLeft[j]              // left halo
                           : u_old[i - 1][j];
            double right = (i == local_nx - 1)
                           ? fromRight[j]             // right halo
                           : u_old[i + 1][j];
            double up    = u_old[i][j + 1];
            double down  = u_old[i][j - 1];

            u_new[i][j] = 0.25 * (left + right + up + down
                                  - dx * dy * f[i][j]);
        	
	    //printf("jacobi_step %f at %d %d \n", f[i][j], i, j);    
	}
        
    }
    //    if (p.nx!=p.ny) printf("In function jacobi_step (jacobi.cpp l.26): nx != ny, check jacobi updates\n");
}

