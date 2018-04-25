#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <omp.h>

#define LIST_SIZE 100000000
// #define LIST_SIZE 10
#define NUM_THREADS 8

void merge_sort();

int main(){
	merge_sort();
	return 0;
}

struct list_item{list_item* next;int *left,*right,left_size,right_size,*work;};
struct list_item *list_front=NULL,*list_back=NULL;
void add_work_item(int*left,int*right,int left_size,int right_size,int*work){
	//printf("%d  %d\n",left_size,right_size);
	//pthread_mutex_lock(&queue_mutex);
	struct list_item *prev = list_back;
	list_back = new struct list_item;
	list_back->next=NULL;
	list_back->left=left;
	list_back->left_size=left_size;
	list_back->right=right;
	list_back->right_size=right_size;
	list_back->work=work;
	if(list_front == NULL){
		list_front = list_back;
	}
	if(prev != NULL)
		prev->next = list_back;
	//pthread_mutex_unlock(&queue_mutex);
}
struct list_item* get_next_work(){
	struct list_item* temp = list_front;
	if(temp != NULL)
		list_front = list_front->next;
	return temp;
}
// bool init_work_list(int*buf,int size,int*work){
// 	if(size<=2){
// 		add_work_item(buf,size,work);
// 		return false;
// 	}
// 	int half = size/2;
// 	bool swap_left = init_work_list(buf,half,work);
// 	bool swap_right = init_work_list(buf+half,size-half,work+half);
// 	if(swap_left != swap_right){
// 		if(swap_right)
// 			for(int i=0; i<half; i++)
// 				work[i] = buf[i];
// 		else
// 			for(int i=0; i<half; i++)
// 				buf[i] = work[i];
			
// 	}
// 	if(swap_right){
// 		int* temp = work;
// 		work = buf;
// 		buf = temp;
// 	}

// 	add_work_item(buf,half,work);
// 	add_work_item(buf+half,size-half,work+half);
// 	//add_work_item(NULL,0,NULL);

// 	return !swap_right;
// }

bool init_work_2(int*buf,int size,int*work){
	bool swapped = false;
	int step=2;
	//handle the base cases first
	for(int x=0; x<size; x+=2){
		if(x+2<=size){
			add_work_item(buf+x,NULL,2,0,work+x);
		}else
			add_work_item(buf+x,NULL,1,0,work+x);
	}
	// sync all the threads
	for(int x=0; x<NUM_THREADS; x++)
		add_work_item(NULL,NULL,0,0,NULL);

	//now the merging part
	while(step<size){
		for(int curt_step=0; curt_step<size; curt_step+=2*step){
			if(curt_step+2*step<size){
				//normal full merge
				add_work_item(buf+curt_step,buf+curt_step+step,step,step,work+curt_step);
			}else if(curt_step+step<size){
				//left full size, right partial size
				int partial = size - (curt_step+step);
				add_work_item(buf+curt_step,buf+curt_step+step,step,partial,work+curt_step);
			}else{
				//left partial size
				int partial = size - curt_step;
				add_work_item(buf+curt_step,NULL,partial,0,work+curt_step);
			}
		}
		// sync all the threads
		for(int x=0; x<NUM_THREADS; x++)
			add_work_item(NULL,NULL,0,0,NULL);
		
		step*=2;
		swapped = !swapped;
		int*temp = buf;
		buf=work;
		work=temp;
	}
	return swapped;
}


void* worker_thread(void*);
void merge_sort_sort(int* buf,int size,int* work);
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
	//init_work_list(buf,LIST_SIZE,work);
	init_work_2(buf,LIST_SIZE,work);
	#pragma omp parallel num_threads(NUM_THREADS)
	worker_thread(NULL);
	//merge_sort_recurse(buf,LIST_SIZE,work);
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
// void merge_sort_sort(int*left,int*right,int size,int* work){
// 	if(size==1){
// 		return;
// 	}
// 	if(size==2){
// 		if(buf[0] > buf[1]){
// 			int temp = buf[1];
// 			buf[0] = buf[1];
// 			buf[1] = temp;
// 		}
// 		return;
// 	}
// 	int half = size/2;
// 	merge_sort_merge(buf,half,buf+half,size-half,work);
// }
void merge_sort_merge(int* left_buf,int left_size,int* right_buf,int right_size,int* dest){
	if(left_size==1 && right_buf == NULL){
		// *dest = *left_buf;
		return;
	}
	if(left_size==2 && right_buf == NULL){
		if(left_buf[0] > left_buf[1]){
			int temp = left_buf[1];
			left_buf[0] = left_buf[1];
			left_buf[1] = temp;
		}
		// dest[0]=left_buf[0];
		// dest[1]=left_buf[1];
		return;
	}
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

void* worker_thread(void*){
	struct list_item* segment;
	#pragma omp critical
	segment = get_next_work();
	while(segment != NULL){
		if(segment->left!=NULL)
			merge_sort_merge(segment->left,segment->left_size,segment->right,segment->right_size,segment->work);
		else{ // sync command
			#pragma omp barrier
			;}
			;
		#pragma omp critical
		segment = get_next_work();
	}
}