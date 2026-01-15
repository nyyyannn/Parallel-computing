/*Question 1:
Write a OpenMP program to sort an array on n elements using both sequential and parallel
mergesort(using Section). Record the difference in execution time.*/


#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>

void merge(int arr[],int low,int middle,int high)
{
    int temp[high-low+1];
    int j=0;
    int left=low;
    int right=middle+1;
    while(left<=middle && right<=high)
    {
        if(arr[left]<=arr[right])
        {
            temp[j]=arr[left];
            j++;
            left++;
        }
        else
        {
            temp[j]=arr[right];
            j++;
            right++;
        }
    }
    while(left<=middle)
    {
        temp[j]=arr[left];
        left++;
        j++;
    }
    while(right<=high)
    {
        temp[j]=arr[right];
        right++;
        j++;
    }
    for(int i=low;i<=high;i++) //cause high was -1 at the start and hence we include high as well.
    {
        arr[i]=temp[i-low]; //cause let's say low=4 then arr[4]=temp[0], and arr[5]=temp[1] and so on. 
    }
}

void mergesortSequential(int arr[], int low, int high)
{
    if(low>=high)
    {
        return;
    }
    int middle=low+(high-low)/2; //to prevent overflowing (if high is equal to int_max)
    mergesortSequential(arr,low,middle);
    mergesortSequential(arr,middle+1,high);
    merge(arr,low,middle,high);
}

void mergesortParallel(int arr[], int low, int high)
{
    if(low>=high)
    {
        return;
    }
    if(high-low<10000) // to prevent thread overhead for small arrays, hence larger arrays are faster
    {
        mergesortSequential(arr,low,high);
        return;
    }
    int middle=low+(high-low)/2; //to prevent overflowing (if high is equal to int_max)
    #pragma omp parallel sections //split the following code into multiple sections and execute them in parallel
    {
        #pragma omp section
        mergesortParallel(arr, low, middle);

        #pragma omp section
        mergesortParallel(arr, middle+1, high);
    }
    merge(arr,low,middle,high);
}

int main() {
    int n = 100000;
    int *arr_seq = malloc(n * sizeof(int));
    int *arr_par = malloc(n * sizeof(int));

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        int val = rand() % 100000;
        arr_seq[i] = val;
        arr_par[i] = val;
    }

    double start_time = omp_get_wtime();
    mergesortSequential(arr_seq, 0, n-1);
    double seq_time = omp_get_wtime() - start_time;

    omp_set_num_threads(4);

    start_time = omp_get_wtime();
    mergesortParallel(arr_par, 0, n-1);
    double par_time = omp_get_wtime() - start_time;

    printf("Sequential time: %.6f seconds\n", seq_time);
    printf("Parallel time: %.6f seconds\n", par_time);

    free(arr_seq);
    free(arr_par);

    return 0;
}
