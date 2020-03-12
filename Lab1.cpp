#include "mpi.h"
#include <iostream>

int main( int argc, char *argv[] )
{

int rank, size;

MPI::Init(argc, argv);

    rank = MPI::COMM_WORLD.Get_rank();
    size = MPI::COMM_WORLD.Get_size();
    std::cout << "I am " << rank << " of " << size <<"\n";
MPI::Finalize();

return 0;

}
