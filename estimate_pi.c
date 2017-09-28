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
   
   /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
   /* ~~~~~~~~~~~~~~~~~PARALLELIZE ME~~~~~~~~~~~~~~~~~~ */
   /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

   /* Random Number Generation via MKL Random Number Stream */        
   float * rand_buffer_x = (float*)malloc(batchsize*sizeof(float)); 
   float * rand_buffer_y = (float*)malloc(batchsize*sizeof(float)); 
   VSLStreamStatePtr stream;
   int SEED = omp_get_thread_num() + time(NULL); /* RNG seed dependent on time of day and thread number*/
   vslNewStream( &stream, VSL_BRNG_SFMT19937, SEED );
   
   /* Loop over Randomly Generated Numbers */
   int count = 0;
   int i,j;
   for(j = 0; j < niter; j+=batchsize)
   {
      vsRngUniform( VSL_RNG_METHOD_UNIFORM_STD, stream, batchsize, rand_buffer_x, 0.0, 1.0 );
      vsRngUniform( VSL_RNG_METHOD_UNIFORM_STD, stream, batchsize, rand_buffer_y, 0.0, 1.0 );
      for(i = 0; i < batchsize; i++)
      {
         float z = rand_buffer_y[i]*rand_buffer_y[i] + rand_buffer_x[i]*rand_buffer_x[i];
         if (z<=1) count++;
      }
   }


   /* Delete the stream and buffers*/        
   vslDeleteStream( &stream );
   free(rand_buffer_x);
   free(rand_buffer_y);

   /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
   /* ~~~~~~~~~~~~~~~~~PARALLELIZE ME~~~~~~~~~~~~~~~~~~ */
   /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


   double pi = (double) count / niter*4;
   printf("num trials=%d, estimate of pi=%f\n", niter, pi);

   return 0;
}
