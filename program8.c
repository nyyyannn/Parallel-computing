/*Question 8:
Write a MPI Program demonstration of MPI_Scatter and MPI_Gather
*/

#include<stdio.h>
#include<mpi.h>

int main(int argc,char* argv[])
{
    int send_data[10],recv_data,gathered_data[10];
    int rank,size;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(rank==0)
    {
        for(int i=0;i<size;i++)
        {
            send_data[i]=i*10;
        }
    }

    MPI_Scatter(send_data,1,MPI_INT,&recv_data,1,MPI_INT,0,MPI_COMM_WORLD);
    recv_data=recv_data+rank;
    MPI_Gather(&recv_data,1,MPI_INT,gathered_data,1,MPI_INT,0,MPI_COMM_WORLD);

    if(rank==0)
    {
        printf("Gathered data at the root:\n");
        for(int i=0;i<size;i++)
        {
            printf("gathered_data[%d]:%d\n",i,gathered_data[i]);
        }
    }
    MPI_Finalize();
    return 0;
}
