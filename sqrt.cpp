#include<iostream>
#include<cmath>
#include<string>
#include<mpi.h>
#include<cstdlib>
#include <iomanip>
#include<ctime>
using namespace std;
int main(int argc, char** argv){
	int numprocs,myid,source,N,i;
	string name;
	double sum,local=0.0;
	N=atoi(argv[1]);
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);

	double start=MPI_Wtime();
	for(i=myid;i<N;i=i+numprocs){
		local+=sqrt(i*(i+1));
	}
	MPI_Reduce(&local,&sum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	if(myid==0){
		// cout<<"The SqrtSum of Data["<<N<<"] is "<<setprecision(5)<<sum<<endl;
		double end=MPI_Wtime();
		double time=end-start;
		printf("The runtime is %16.15f ms\n",time*1000);
		printf("The SqrtSum value=%16.15f\n",sum);
		
	}
	MPI_Finalize();
}
