/*Question 7:
Write a MPI Program to demonstration of Broadcast operation.
*/

#include<stdio.h>
#include<mpi.h>

int main(int argc,char* argv[])
{
    int rank;
    int size;
    int number;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(rank==0)
    {
        number=100;
        printf("Process %d broadcasting %d to all other processes\n",rank,number);
    }
    MPI_Bcast(&number,1,MPI_INT,0,MPI_COMM_WORLD);
    printf("Process %d received %d from process 0\n",rank,number);

    MPI_Finalize();
    return 0;

}
