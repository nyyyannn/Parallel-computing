/*Question 2:
Write an OpenMP program that divides the Iterations into chunks containing 2 iterations,
respectively (OMP_SCHEDULE=static,2). Its input should be the number of iterations, and
its output should be which iterations of a parallelized for loop are executed by which thread.
 For example, if there are two threads and four iterations, the output might be the following:
a. Thread 0 : Iterations 0 −− 1
b. Thread 1 : Iterations 2 −− 3
*/

#include<stdlib.h>
#include <stdio.h>
#include <omp.h>

int main(int argc, char* argv[]) {
    int n, i;

    if (argc != 2) {
        printf("Usage: %s <number_of_iterations>\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);  // Number of iterations

    printf("Total Iterations: %d\n", n);

    #pragma omp parallel for schedule(static,2)
    for (i = 0; i < n; i++) {
        int tid = omp_get_thread_num();
        printf("Thread %d executes iteration %d\n", tid, i);
    }

    return 0;
}
