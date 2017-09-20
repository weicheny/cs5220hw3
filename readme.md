# Estimating Pi via Monte Carlo
-----------

In this HW, we will cover some OpenMP basics. If you have any questions, don't hesitate to post on Piazza or come to OH! 
**Submission:** A tarball/git-link of the provided directory

# OpenMP
-----------
As mentioned in class, OpenMP is a simple, but deceptively powerful, API for writing parallel code on shared memory machines. Many production codes use it OpenMP to introduce parallelism without changing the code base drastically. In this homework, you will do the same on a toy problem. 

# How to Estimate Pi
------------
The idea behind this HW is actually rather simple. We know the area of a unit circle must be equal to Pi. Therefore, one can come up with an approximation to Pi via a "dartboard" approach... by randomly shooting points inside the square perfectly enclosing the unit circle, and estimating the proportion of points that land inside the unit circle. This is the essence of Monte Carlo algorithms; randomly sampling to produce an expected value aligning with a desired numeric answer. 

To be a bit more precise, consider the unit cube and the first orthant of the unit circle, which have areas 1 and Pi/4, respectively. We sample *n* points in the unit cube, calculate the proportion of points landing inside the unit circle, and multiply that estimate by 4 to estimate Pi. See this [link](http://mathfaculty.fullerton.edu/mathews/n2003/montecarlopimod.html) for more details.

# Instructions
-------------
We have given you *estimate-pi.c*, the makefile, and a job script. You run *estimate-pi* as follows:

```
./estimate-pi 500
```

This will sample 500 points and spit out an estimation an estimate of Pi using the strategy outlined earlier. Your job is parallelize the for loop via OpenMP. We suggest either

* Performing a reduction operation
* Performing independent work and averaging Pi estimates between threads

You only need to try one approach, but we recommend trying both! 


# Tips and Hints
------------
Please see the class lecture slides for an introduction to OpenMP. For a more comprehensive tutorial, Lawrence Livermore National Labs has a well-written [guide](https://computing.llnl.gov/tutorials/openMP/). Those that are heroically inclined may also take a look at the [OpenMP standard](http://www.openmp.org/wp-content/uploads/openmp-4.5.pdf) itself. 

