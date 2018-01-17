#include <stdio.h>
#include <stdlib.h>

struct DynamicArray{
	void *data;
	int capacity;
	int length; // here for my own convenience
};

struct DynamicArray* make_array(int size){
	if(size<=0)
		size = 1;
	struct DynamicArray *info = (struct DynamicArray*)malloc(sizeof(struct DynamicArray));
	info->data = malloc(size);
	info->capacity = size;
	info->length = 0;
}
void delete_array(struct DynamicArray* info){
	free(info->data);
	free(info);
}
void resize_array(struct DynamicArray* info,int size){
	if(size==0) size = 1;
	if(size<0){
		int delta = info->capacity;
		if(delta > 128) delta = 128;
		info->data = realloc(info->data,delta+info->capacity);
		info->capacity += delta;
	}else{
		info->data = realloc(info->data,size);
		info->capacity = size;
	}
}

int main(){
	//Make array and fill with 50s
	struct DynamicArray *array = make_array(10*sizeof(int));
	for(int x=0; x<10; x++)
		((int*)array->data)[x] = 50;
	array->length = 10; // just to help me bookkeep

	//lets just check that things are working as we expect
	//print all 10 indicies
	for(int x=0; x<array->length; x++){
		printf(" %3d ",((int*)array->data)[x]);
	}
	printf("\n");
	
	//now lets make the array larger
	resize_array(array,30*sizeof(int));
	for(int x=0; x<10; x++)
		((int*)array->data)[x+10] = 100;
	for(int x=0; x<10; x++)
		((int*)array->data)[x+20] = 150;
	array->length = 30; // just to help me bookkeep

	//lets just check that things are working as we expect
	for(int x=0; x<array->length; x++){
		if(x%10 == 0)
			printf("\n");
		printf(" %3d ",((int*)array->data)[x]);
	}
	printf("\n");

	//now lets make the array smaller
	resize_array(array,20*sizeof(int));
	array->length = 20; // just to help me bookkeep

	//lets just check that things are working as we expect
	for(int x=0; x<array->length; x++){
		if(x%10 == 0)
			printf("\n");
		printf(" %3d ",((int*)array->data)[x]);
	}
	printf("\n");

	return 0;
}