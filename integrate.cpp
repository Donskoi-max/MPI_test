#define a 10
#define b 100
#include<mpi.h>
#include<iostream>
using namespace std;
int main(int argc, char** argv)
{
    int myid,numprocs,N;
    N=atoi(argv[1]);
    int i,source;
    double local=0.0,local1=0.0,dx=(double)((b-a+0.0)/N);
    double inte,x;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    double start=MPI_Wtime();
    if(myid!=0){
        for(i=myid-1;i<N;i=i+numprocs-1){
            x=a+i*dx+dx/2;
            local+=(x*x*x*dx);
        }
        MPI_Send(&local,1,MPI_DOUBLE,0,99,MPI_COMM_WORLD);
    }
    else{
        for(source=1;source<numprocs;source++){
            MPI_Recv(&local1,1,MPI_DOUBLE,source,99,MPI_COMM_WORLD,&status);
            inte=inte+local1;
        }
        double end=MPI_Wtime();
		double time=end-start;
		printf("The runtime is %16.15f ms\n",time*1000);
        printf("The integral of x^3 in region [%d,%d] =%16.15f\n",a,b,inte);
    }
    MPI_Finalize();
}