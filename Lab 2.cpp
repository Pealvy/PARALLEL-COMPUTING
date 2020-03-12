#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[]){
    
    //declaring the needed variables
    int rank, size, sum, start, end, accumulator;
    MPI::Status status;

//Beginning of parallel Program
    MPI::Init(argc, argv);

        rank = MPI::COMM_WORLD.Get_rank();
        size = MPI::COMM_WORLD.Get_size();
        sum = 0;

        start = (1000*rank) / size + 1;
        end = (1000*(rank+1)) / size;

    //Main task that would be parallelized for different processes to execute
        for(int i = start; i <= end; i++)
            sum += i;
            
        if(rank != 0){
            MPI_Send(&sum, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
            cout<<"I am process "<<rank<<" with accumulated value of "<<sum<<endl;
        }
        else
        {
            for(int j=1; j < size; j++){
                MPI_Recv(&accumulator, 1, MPI_INT, j, 1, MPI_COMM_WORLD, status);
                sum += accumulator;
                //cout<<"I am "<<rank<<" working on "<<accumulator<<endl;
            }

        }

        if (rank == 0)
            cout<<"The sum from 1 to 1000 is:\t"<<sum<<endl;
        
     MPI::Finalize();
//End of parallel Program
    
    return 0;
}
