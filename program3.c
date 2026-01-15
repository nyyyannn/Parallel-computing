/*Question 3:
Write a OpenMP program to calculate n Fibonacci numbers using tasks.
*/

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

long long fib(int n)
{
    if(n<=1)
    {
        return n;
    }
    long long x,y;

    #pragma omp task shared(x)
    x=fib(n-1);

    #pragma omp task shared(y)
    y=fib(n-2);

    #pragma omp taskwait
    return x+y;
}
int main()
{
    int n;
    printf("Enter n:");
    scanf("%d",&n);
    
    #pragma omp parallel
    {
        #pragma omp single
        {
            for(int i=0;i<n;i++)
            {
                long long res=fib(i);
                printf("Fib(%d): %lld\n",i,res);
            }
        }
    }
    return 0;
}
