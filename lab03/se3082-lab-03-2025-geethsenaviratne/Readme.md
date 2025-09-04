e

![lab](/resources/pclogo.png)
## <div align="center">Lab 03</div>

1. Write a serial and parallel program that uses OpenMP

## Instructions

1. Use your AWS EC2 instance or another linux instance that has openmp to complete the Lab Exercises
2. For timing the perfornance of your solutons use the code snippet given at the end of the lab sheet
3. Calculate the time for running the program serially and calculate seperately the program for running the program in parallel using OpenMP, change the number of threads as follows 1,2,4,8,16 in each instance.
4. Is your parallel solution answer correct, if it is not do you have an idea why this is the case.

## Exercise 1:

In this program we will write a serial program to calculate Pi.  We will write a parallel implementation later.

![lab](/resources/equation.png)

1.	Goto the terminal window of your computer and create a folder called lab02
2. Clone your repo to your local (git clone https://your github repo)
3. Write a program in C to calculate Pi using the above formulae.  Use a large integer for N
4.	Use Secure Copy to copy this program to your linux machine (e.g. AWS EC2)
5.	Use SSH to login to your Linux Machine
6.	Compile and Run the program in AWC EC2
7.	Use Secure Copy to get the results back to your machine

8. Commit and push the code to your repo.

```
git add .
git commit -m "<put a message here>"
git push
```

## Exercise 2:

Have a look at the Exercise you did in Lab02.
Can you parallize the  program you wrote in Exercise 1using OpenMP, the easiest way is to parallelize for loops you have written


1.	Compile and run your program using the command below
```
gcc -fopenmp lab02.c -o lab02.o
./lab02.o
```
3.	Time the serial and the parallel program, do  you notice a difference.
4.	How many cores does your linux machine have?
5.	Use an new EC2 configuration that is higher tryout the program and change the number of threads used (See Lab02), is there a difference when you run the serial program and the parallel program in this higher EC2 configuration.
6.	What is the speedup for both EC2 instances when you change number of threads
7.	Ensure your instances are stopped when you complete the lab and delete unwanted resources in AWS

 
## Exercise 3:

Parallelize the following problem and run it in both EC2 instances and evaluate the performance
![lab](/resources/q2.png)

1. Use an new EC2 configuration that is higher tryout the program and change the number of threads used (See Lab02), is there a difference when you run the serial program and the parallel program in this higher EC2 configuration.
2.	What is the speedup for both EC2 instances when you change number of threads
3.	Ensure your instances are stopped when you complete the lab and delete unwanted resources in AWS

## Exercise 4

Parallelize the computation of Pi using the “Monte Carlo method” (Use the sample C code in the following link).

https://www.geeksforgeeks.org/dsa/estimating-the-value-of-pi-using-monte-carlo-parallel-computing-method/

Find the calculation for 10,000,000 times.

Time your parallel Results
Timing can be obtained as follows
```c
double tstart, tcalc
tstart = omp_get_wtime();

 // code to be timed in here

tstop  = omp_get_wtime();

tcalc = tstop - tstart;  // time in milli seconds
```







