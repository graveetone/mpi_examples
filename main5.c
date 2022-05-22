#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
	int i, err, num, namelen, bind, verbose, scope;
	int threadsupport;
	char name[100];
	MPI_Datatype datatype;

	err = MPI_T_init_thread(MPI_THREAD_SINGLE,&threadsupport);
	if (err != MPI_SUCCESS)
		return err;
	
	err = MPI_T_cvar_get_num(&num);
	if (err != MPI_SUCCESS)
		return err;
	for (i=0; i<num; i++) {
		namelen=100;
		err = MPI_T_cvar_get_info(i, name, &namelen, &verbose, &datatype, NULL, NULL, NULL, &bind, &scope);
		if (err != MPI_SUCCESS || err != MPI_T_ERR_INVALID_INDEX)
			return err;
		printf("Var %i: %s\n", i, name);
	}
	err = MPI_T_finalize();
	if (err != MPI_SUCCESS)
		return 1;
	else
		return 0;
}