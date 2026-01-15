/*Question 6:
Write a MPI program to demonstration of deadlock using point to point communication and
avoidance of deadlock by altering the call sequence
*/

#include<stdio.h>
#include<mpi.h>

#define DEADLOCK_PART 2

int main(int argc,char* argv[])
{
    int size,rank;
    int number=100;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(size<2)
    {
        printf("Minimum 2 processes are required.");
        MPI_Finalize();
        return 0;
    }

#if(DEADLOCK_PART==1)
    if(rank==0)
    {
        printf("Process 0 waiting to receive from process 1\n");
        MPI_Recv(&number,1,MPI_INT,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Send(&number,1,MPI_INT,1,0,MPI_COMM_WORLD);
    }
    else if(rank==1)
    {
        printf("Process 1 waiting to receive from process 0\n");
        MPI_Recv(&number,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Send(&number,1,MPI_INT,0,0,MPI_COMM_WORLD);
    }

#elif(DEADLOCK_PART==2)
    if(rank==0)
    {
        MPI_Send(&number,1,MPI_INT,1,0,MPI_COMM_WORLD);
        MPI_Recv(&number,1,MPI_INT,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("Process 0 sent and received back: %d\n",number);
    }
    else if(rank==1)
    {
        MPI_Recv(&number,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Send(&number,1,MPI_INT,0,0,MPI_COMM_WORLD);
        printf("Process 1 received and sent back: %d\n",number);
    }
#endif

    MPI_Finalize();
    return 0;
}
