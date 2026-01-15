/*Question 4:
Write a OpenMP program to find the prime numbers from 1 to n employing parallel for
directive. Record both serial and parallel execution times.
*/

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>

int isPrime(int n)
{
    if(n<=1)
    {
        return 0;
    }
    if(n%2==0)
    {
        return 1;
    }
    int limit=(int)sqrt(n);
    for(int i=3;i<=limit;i+=2)
    {
        if(n%i==0)
        {
            return 1;
        }
    }
    return 0;
}
int main()
{
    int n;
    printf("Enter a number:");
    scanf("%d",&n);
    double st,ed;
    int serial_count=0;

    st=omp_get_wtime();
    for(int i=0;i<n;i++)
    {
        if(isPrime(i))
            serial_count++;
    }
    printf("%d\n",serial_count);
    printf("%.6f\n",omp_get_wtime()-st);

    int parallel_count=0;
    st=omp_get_wtime();
    #pragma omp parallel for reduction(+:parallel_count) schedule(dynamic)
    for(int i=0;i<n;i++)
    {
        if(isPrime(i))
            parallel_count++;
    }
    printf("%d\n",parallel_count);
    printf("%.6f\n",omp_get_wtime()-st);
    return 0;
}
