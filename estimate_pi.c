#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "mkl_vsl.h"

#define batchsize 100

int main(int argc, char **argv)
{

   int niter = atoi(argv[1]);
   
   /* Random Number Generation via MKL Random Number Stream */        
   float * rand_buffer_x; 
   float * rand_buffer_y; 
   VSLStreamStatePtr stream;
   int SEED = omp_get_thread_num() + time(NULL); /* RNG seed dependent on time of day and thread number*/
   vslNewStream( &stream, VSL_BRNG_SFMT19937, SEED );
   
   /* Loop over Randomly Generated Numbers */
   int count = 0;
   int i,j,k,threads; //i thread id, j batch id, k batch index
   //dispatch the work to all the threads evenly
   //every thread gets the same amount of work
   //in inner j k loops do the work for each thread
   //combine the count result using reduction
   //each thread gets a unique buffer space

#pragma omp parallel default(shared) private(i,j,k,rand_buffer_x, rand_buffer_y)
   {
	threads = omp_get_num_threads();
	#pragma omp for schedule(static,1) reduction(+:count)
   	for (i=0; i < threads; ++i) {
		rand_buffer_x = (float*)malloc(batchsize*sizeof(float));
		rand_buffer_y = (float*)malloc(batchsize*sizeof(float));
		   for (j = 0; j < niter / threads; j+=batchsize) {
				vsRngUniform( VSL_RNG_METHOD_UNIFORM_STD, stream, batchsize, rand_buffer_x, 0.0, 1.0 );
		   		vsRngUniform( VSL_RNG_METHOD_UNIFORM_STD, stream, batchsize, rand_buffer_y, 0.0, 1.0 );
		   		for (k = 0; k < batchsize; ++k) {
					float z = rand_buffer_y[i]*rand_buffer_y[i] + rand_buffer_x[i]*rand_buffer_x[i];
					if (z<1) count++;
				}
		   }

   }	 
	//for every thread delete the thread local buffer	
	free(rand_buffer_x);
	free(rand_buffer_y);
   }
    //only delete stream once
    vslDeleteStream( &stream );
    double pi = (double) count / niter*4;
   printf("num trials=%d, estimate of pi=%f\n", niter, pi);

   return 0;
}
