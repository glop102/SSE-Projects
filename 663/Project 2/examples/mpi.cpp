#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <sys/time.h>

void hello_world_wikipedia();
void hello_world_book();
void hello_world_masterOnlySend();
void merge_sort();

int main(int argc, char **argv)
{
	//hello_world_wikipedia();
	//hello_world_book();
	//hello_world_masterOnlySend();
	merge_sort();
	return 0;
}

void hello_world_wikipedia(){
	char buf[256];
	int my_rank, num_procs;

	/* Initialize the infrastructure necessary for communication */
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

	if (my_rank == 0) {
		int other_rank;
		printf("We have %i processes.\n", num_procs);

		/* Send messages to all other processes */
		for (other_rank = 1; other_rank < num_procs; other_rank++){
			sprintf(buf, "Hello %i!", other_rank);
			MPI_Send(buf, sizeof(buf), MPI_CHAR, other_rank, 0, MPI_COMM_WORLD);
		}

		/* Receive messages from all other process */
		for (other_rank = 1; other_rank < num_procs; other_rank++){
			MPI_Recv(buf, sizeof(buf), MPI_CHAR, other_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("%s\n", buf);
		}

	}else{

		/* Receive message from process #0 */
		MPI_Recv(buf, sizeof(buf), MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		/* Send message to process #0 */
		sprintf(buf, "Process %i reporting for duty.", my_rank);
		MPI_Send(buf, sizeof(buf), MPI_CHAR, 0, 0, MPI_COMM_WORLD);

	}

	/* Tear down the communication infrastructure */
	MPI_Finalize();
}

void hello_world_masterOnlySend(){
	char buf[256];
	int my_rank, num_procs;

	/* Initialize the infrastructure necessary for communication */
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

	if (my_rank == 0) {
		printf("Master process of %d processes\n",num_procs);

		for (int other_rank = 1; other_rank < num_procs; other_rank++){
			sprintf(buf,"Process %d of %d",other_rank,num_procs);
			MPI_Send(buf, strlen(buf)+1, MPI_CHAR, other_rank, 0, MPI_COMM_WORLD);
		}
	}else{
		MPI_Recv(buf, sizeof(buf), MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("%s\n",buf);
	}

	/* Tear down the communication infrastructure */
	MPI_Finalize();
}

void hello_world_book(){
	char buf[256];
	int my_rank, num_procs;

	/* Initialize the infrastructure necessary for communication */
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

	if (my_rank == 0) {
		printf("Master process of %d processes\n",num_procs);

		for (int other_rank = 1; other_rank < num_procs; other_rank++){
			MPI_Recv(buf, sizeof(buf), MPI_CHAR, other_rank, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			printf("%s\n",buf);
		}
	}else{
		sprintf(buf,"Process %d of %d",my_rank,num_procs);
		MPI_Send(buf, strlen(buf)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
	}

	/* Tear down the communication infrastructure */
	MPI_Finalize();
}


#define LIST_SIZE 100000000
bool merge_sort_recurse(int* buf,int size,int* work);
void merge_sort_merge(int* left_buf,int left_size,int* right_buf,int right_size,int* dest);
bool gather_tree(int* local_buf,int* local_work,int local_buf_len,int num_procs,int my_rank);
void merge_sort(){
	struct timeval timecheck;
	long start_time,end_time;
	int my_rank, num_procs;
	srand(time(NULL));

	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

	int local_buf_len = LIST_SIZE / num_procs; // how elements are in normal buffs
	int buf_extra_elms = LIST_SIZE - local_buf_len*num_procs; // how many extra elms the master will have to do itself
	int* local_buf = (int*)malloc(LIST_SIZE*sizeof(int));
	int* local_work = (int*)malloc(LIST_SIZE*sizeof(int));

	if(my_rank == 0){
		int* buf = (int*)malloc(LIST_SIZE*sizeof(int));
		for(int i=0;i<LIST_SIZE;i++)
			buf[i] = (rand()/(double)(RAND_MAX)) * LIST_SIZE;

		MPI_Barrier(MPI_COMM_WORLD);
		gettimeofday(&timecheck, NULL);
		start_time = (long)timecheck.tv_sec * 1000000 + (long)timecheck.tv_usec;

		MPI_Scatter(buf, local_buf_len, MPI_INT,
			local_buf, local_buf_len, MPI_INT, 0,
			MPI_COMM_WORLD);
		for(int x=0; x<buf_extra_elms; x++)
			local_buf[x+local_buf_len] = buf[x + (local_buf_len*num_procs)];
		bool swapped =
		merge_sort_recurse(local_buf,local_buf_len+buf_extra_elms,local_work);

		int extras[buf_extra_elms];
		for(int x=0; x<buf_extra_elms; x++)
			extras[x] = local_buf[x+local_buf_len];

		if(swapped){
			int* temp = local_buf;
			local_buf = local_work;
			local_work = temp;
		}
		swapped = gather_tree(local_buf,local_work,local_buf_len,num_procs,my_rank);
		free(buf);
	}else{
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Scatter(NULL, 0, MPI_INT,
			local_buf, local_buf_len, MPI_INT, 0,
			MPI_COMM_WORLD);
		bool swapped =
		merge_sort_recurse(local_buf,local_buf_len,local_work);

		if(swapped){
			int* temp = local_buf;
			local_buf = local_work;
			local_work = temp;
		}
		swapped = gather_tree(local_buf,local_work,local_buf_len,num_procs,my_rank);
	}

	MPI_Barrier(MPI_COMM_WORLD);

	if(my_rank == 0){
		gettimeofday(&timecheck, NULL);
		end_time = (long)timecheck.tv_sec * 1000000 + (long)timecheck.tv_usec;

		printf("Time Taken : %ld\n",end_time - start_time);
	}

	free(local_buf);
	free(local_work);

	MPI_Finalize();
}
bool merge_sort_recurse(int* buf,int size,int* work){
	if(size==1){
		// *work = *buf;
		return false;
	}
	if(size==2){
		if(buf[0] > buf[1]){
			int temp = buf[1];
			buf[0] = buf[1];
			buf[1] = temp;
		}
		// work[0] = buf[0];
		// work[1] = buf[1];
		//printf("  %d  %d\n\n",work[0],work[1]);
		return false;
	}
	// recursive part
	int half = size/2;
	bool swap_left=false,swap_right=false;
		swap_left =
		merge_sort_recurse(buf,half,work);
		swap_right =
		merge_sort_recurse(buf+half,size-half,work+half); // subtraction for odd sizes
	if(swap_left != swap_right){
		if(swap_right)
			for(int i=0; i<half; i++)
				work[i] = buf[i];
		else
			for(int i=0; i<half; i++)
				buf[i] = work[i];
			
	}
	if(swap_right){
		int* temp = work;
		work = buf;
		buf = temp;
	}
	merge_sort_merge(buf,half,buf+half,size-half,work);

	return !swap_right;
}

void merge_sort_merge(int* left_buf,int left_size,int* right_buf,int right_size,int* dest){
	while(left_size && right_size){
		if(*left_buf <= *right_buf){
			*dest = *left_buf;
			left_size--;
			left_buf++;
		}else{
			*dest = *right_buf;
			right_size--;
			right_buf++;
		}
		dest++;
	}
	while(left_size){
		*dest = *left_buf;
		left_size--;
		left_buf++;
		dest++;
	}
	while(right_size){
		*dest = *right_buf;
		right_size--;
		right_buf++;
		dest++;
	}

	return;
}

//0 1 2 3 4 5 6 7 8 9
//0 1 2 3 4
//0 1 2
//0    2

//0 1 2 3 4 5 6 7 8
//0 1 2 3          8
//0 1              8
//0                8

//0 1 2 3 4 5 6 7
//0 1 2 3
//0 1
//0

//0 1 2 3 4 5 6     h=3
//0 1 2        6    h=1
//0 1  2       6    h=1
//0    2       6    h=0
bool gather_tree(int* local_buf,int* local_work,int local_buf_len,int num_procs,int my_rank){
	bool swapped = false;

	int half = num_procs/2;
	int extra_proc=0,extra_size;
	while(half){
		if(my_rank<half){
			MPI_Recv(local_buf+local_buf_len, local_buf_len, MPI_INT, my_rank+half, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			merge_sort_merge(local_buf,local_buf_len,local_buf+local_buf_len,local_buf_len,local_work);
		}else if(my_rank<(2*half)){
			MPI_Send(local_buf, local_buf_len, MPI_INT, my_rank-half, 0, MPI_COMM_WORLD);
			return swapped; //we gave our work to someone else, so we are done
		}else{
			// printf("%d is extra\n",my_rank);
			// if(extra_proc==0){
			// 	extra_proc = my_rank;
			// 	extra_size = local_buf_len;
			// }else{
			// 	if(extra_proc == my_rank){
			// 		MPI_Send(local_buf, extra_size, MPI_INT, my_rank-half, 0, MPI_COMM_WORLD);
			// 		return swapped; //we gave our work to someone else, so we are done
			// 	}else{
			// 		MPI_Recv(local_buf+local_buf_len, local_buf_len, MPI_INT, my_rank+half, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			// 		merge_sort_merge(local_buf,local_buf_len,local_buf+local_buf_len,local_buf_len,local_work);
			// 	}
			// 	extra_proc = 0;
			// }
		}
		half/=2;
		local_buf_len*=2;
		swapped = !swapped;
		int* temp = local_buf;
		local_work = local_buf;
		local_buf=temp;
	}
	return swapped;
}