/*Question 5:
Write a MPI Program to demonstration of MPI_Send and MPI_Recv.
*/

#include<mpi.h>
#include<stdio.h>

int main(int argc,char* argv[])
{
    int number;
    int rank,size;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(size<2)
    {
        printf("Minimum of 2 processes are required\n");
        MPI_Finalize();
        return 0;
    }

    if(rank==0)
    {
        number=10;
        printf("Process %d sends %d to process 1\n",rank,number);
        MPI_Send(&number,1,MPI_INT,1,0,MPI_COMM_WORLD);
    }
    else if(rank==1)
    {
        MPI_Recv(&number,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("Process %d receives %d from process 0\n",rank,number);
    }
    else
    {
        MPI_Recv(&number,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("Process %d receives %d from process 0\n",rank,number);
    }
    MPI_Finalize();
    return 0;
}
