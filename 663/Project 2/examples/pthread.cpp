#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

void merge_sort();
int main(){
	merge_sort();
	return 0;
}


#define LIST_SIZE 10000
struct Params{bool *return_value;int* buf;int size;int* work;};
void* merge_sort_recurse_driver(void* params);
bool merge_sort_recurse(int* buf,int size,int* work);
void merge_sort_merge(int* left_buf,int left_size,int* right_buf,int right_size,int* dest);
void merge_sort(){
	struct timeval timecheck;
	long start_time,end_time;
	srand(time(NULL));

	int* buf = (int*)malloc(LIST_SIZE*sizeof(int));
	int* work = (int*)malloc(LIST_SIZE*sizeof(int));
	for(int i=0;i<LIST_SIZE;i++)
		buf[i] = (rand()/(double)(RAND_MAX)) * LIST_SIZE;

	gettimeofday(&timecheck, NULL);
	start_time = (long)timecheck.tv_sec * 1000000 + (long)timecheck.tv_usec;
	bool is_backwards =
	merge_sort_recurse(buf,LIST_SIZE,work);
	gettimeofday(&timecheck, NULL);
	end_time = (long)timecheck.tv_sec * 1000000 + (long)timecheck.tv_usec;

	// for(int x=0; x<LIST_SIZE; x++)
	// 	if(is_backwards)
	// 		printf("%d  ", work[x]);
	// 	else
	// 		printf("%d  ", buf[x]);
	// printf("\n");
	printf("Time Taken in us : %ld\n",end_time - start_time);
	free(buf);
	free(work);
}
void* merge_sort_recurse_driver(void* param_pointer){
	Params* param = (Params*) param_pointer;
	*(param->return_value) = merge_sort_recurse(param->buf,param->size,param->work);
	return NULL;
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
	{	
		Params left={&swap_left,buf,half,work},
		right={&swap_right,buf+half,size-half,work+half};
		pthread_t handles[2];
		pthread_create(handles,NULL,merge_sort_recurse_driver,&left);
		pthread_create(handles+1,NULL,merge_sort_recurse_driver,&right);
		pthread_join(handles[0],NULL);
		pthread_join(handles[1],NULL);
	}
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