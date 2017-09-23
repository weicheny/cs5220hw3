# Estimating Pi via Monte Carlo

In this HW, we will cover some OpenMP basics. If you have any
questions, don't hesitate to post on Piazza or come to OH!  
**Submission:** A tarball/git-link of the provided directory

# OpenMP

As mentioned in class, OpenMP is a simple, but powerful, API for
writing parallel code on shared memory machines.  In an ideal case,
OpenMP can be used to introduce parallelism without changing the code
base drastically, though it is ogten necessary to re-architect a
code to be "parallelism-friendly" before adding OpenMP directives will
significantly improve performance.  In this homework, you will use
OpenMP to parallelize a toy problem.

# How to Estimate Pi

The idea behind this HW is actually rather simple. We know the area of
a unit circle must be equal to Pi. Therefore, one can come up with an
approximation to Pi via a "dartboard" approach... by randomly shooting
points inside the square perfectly enclosing the unit circle, and
estimating the proportion of points that land inside the unit
circle. This is the essence of Monte Carlo algorithms:
expressing a quantity of interest as the expected value of a random
variable, then estimating that random variable through a sample mean.

To be a bit more precise, consider the unit cube and the first orthant
of the unit circle, which have areas 1 and Pi/4, respectively. We
sample *n* points in the unit cube, calculate the proportion of points
landing inside the unit circle, and multiply that estimate by 4 to
estimate Pi. 
See this [link](http://mathfaculty.fullerton.edu/mathews/n2003/montecarlopimod.html) for more details.

# Instructions

We have given you *estimate-pi.c*, the makefile, and a job script. You
run *estimate-pi* as follows:

```
./estimate-pi 500
```

This will sample 500 points and spit out an estimation an estimate of
Pi using the strategy outlined earlier. Your job is parallelize the
for loop via OpenMP. We suggest either

* Performing a reduction operation
* Performing independent work and averaging Pi estimates between threads

You only need to try one approach, but we recommend trying both! The code is separated 
into two chunks. The first chunk creates a buffer and fills it with random numbers. 
The second chunk loops over that buffer and calculates our estimate of pi. We want 
you to parallelize both chunks; each thread should have its *own* private buffer 
and loop over that private buffer. 

# Random Number Generation

Efficient and accurate parallel random number generators are not provided in the C 
standard libraries (the default ones are either not thread safe, inaccurate, or both!). 
Consequently, we use Intel's random number streams provided in MKL as our random number 
generators, as they are thread safe and accurate. We have already provided the logic 
for generating thread-private random number streams, so that you do not need to worry 
about dealing with random number generation yourself. 


# Tips and Hints

Please see the class lecture slides for an introduction to OpenMP. For
a more comprehensive tutorial, Lawrence Livermore National Labs has a
well-written [guide].  Those that are heroically inclined may also
take a look at the [OpenMP standard] itself.

[guide]: https://computing.llnl.gov/tutorials/openMP/
[OpenMP Standard]: http://www.openmp.org/wp-content/uploads/openmp-4.5.pdf
