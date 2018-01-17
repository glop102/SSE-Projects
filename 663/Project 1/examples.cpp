#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

//1-11 = 16:00 to 17:30 - move files in git and setup readme files
//1-12 = 18:00 to 18:30 - start on example.cpp
//1-13 = 19:00 to  2:30 - make outline of example.cpp, get basic things ready, simple coding start, get VM ready with visual studio and cygwin+git, start latex document
//1-14 = 00:00 to  4:00 - work on examples and report
//1-16 = 12:00 to  0:30 - finish C part of the paper (-30 mins for lunch)(-30mins to fix vacuum)
//1-17 = 14:30 to 15:00 - prrof read and send to prof to do a quick look over

/* topics

simple pointers in a 1d memory
pointers to walk an array
	going out of bounds of the array
pointers are invalid outside of their scope
	show still get right value when read from invalid location when ar leaves the scope
	explain why this is bad
malloc() - a "replacment" for global variables
	gives back memory that your program holds until the program ends
	free() - tell the OS that we dont need this memory any more
calloc()
realloc()
	what it does
	example making a dynamicly sizing array (like std::vector) with a struct and functions
volatile - also mention that often it is not needed as it gets in the way of optimisers in compilers
make dynamicly sized array thingy but using a class

new and delete
new[] and delete[]
reference counting to know when to clean up
defered copy until write for an object
	http://doc.qt.io/archives/qt-4.8/implicit-sharing.html#implicit-data-sharing
	lets you pass objects by value but keep the bulk of data frrom needing to be copied until written
*/

//simple pointers
// showing a pointer is just a reference to a point in memory
void simple_pointer(){
	int a;
	a = 10;
	printf("%d\n",a);

	int *p;
	p = &a;
	printf("%d\n",*p);

	*p = 25;
	printf("%d\n",a);
}

//===========================================================================================================
void pointers_walking_arrays(){
	int b[4];
	b[0]=2; b[1]=5; b[2]=8; b[3]=11;

	int *p = b;
	printf("%d %d %d\n",*p,(*p)+1,*(p+1));

	for(int x=0; x<4; x++)
		*(p+x) = 4*x;
	printf("%d %d %d %d\n",b[0],b[1],b[2],b[3]);
}

void pointers_walking_arrays2(){
	//pointers can themselves be changed
	int b[4];
	b[0]=2; b[1]=4; b[2]=6; b[3]=8;
	int *p = b;
	p += 2;
	printf("%d\n",*p);

	//pointers can be used to walk arrays of characters
	char s[50]="Some Length";
	char *sp = s;

	int counter=0;
	while(*sp != 0){
		counter+=1;
		sp += 1;
	}
	printf("%d\n",counter);
}

//===========================================================================================================
int* __scope_of_variables(){
	int x=25;
	return &x;
}
void scope_of_variables(){
	int *p=__scope_of_variables();
	printf("%d\n",*p);
}

void scope_of_variables2(){
	int *p;
	{ // some other scope
		int x = 100;
		p = &x;
	}
	printf("%d\n",*p);
}

//===========================================================================================================
void malloc_simple(){
	int *p = (int*)malloc(4*sizeof(int));
	for(int x=0; x<4; x++)
		p[x] = x*4;
	printf("%d %d %d %d\n",p[0],p[1],p[2],p[3]);
	free(p);
}

int* __malloc_single(){
	int *p = (int*)malloc(sizeof(int));
	*p = 25;
	return p;
}
void malloc_single(){
	int *p = __malloc_single();
	printf("%d\n",*p);
	free(p);
}

void calloc_call(){
	int *p = (int*)calloc(4,sizeof(int));
	for(int x=0; x<4; x++)
		p[x] = x*4;
	printf("%d %d %d %d\n",p[0],p[1],p[2],p[3]);
	free(p);
}

void realloc_example(){
	int *p = (int*)calloc(2,sizeof(int));
	p[0]=1; p[1]=1;

	p = (int*)realloc(p,20*sizeof(int));
	for(int x=2; x<20; x++)
		p[x] = p[x-1] + p[x-2];
	printf("%d\n",p[19]);
	free(p);
}

void page_size(){
	printf("%d\n",getpagesize());
}

//===========================================================================================================
class Simple{
public:
	Simple(){printf("Constructed\n");}
	~Simple(){printf("Destructed\n");}
};

void object_malloc(){
	Simple *p = (Simple*)malloc(sizeof(Simple));
	free(p);
}
void object_new(){
	Simple *p = new Simple;
	delete p;
}

class HelloWorld{
public:
	void print(){printf("Hello World\n");}
};
HelloWorld* __some_other_scope(){
	return new HelloWorld;
}
void some_other_scope(){
	HelloWorld *ppp = __some_other_scope();
	ppp->print();
	delete ppp;
}

class Counter{
	static int counter;
	int our_value;
public:
	Counter(){
		our_value = counter;
		counter++;
	}
	void print(){printf(" %d ",our_value);}
};
int Counter::counter = 0;
void object_array(){
	Counter *array = new Counter[5];
	for(int x=0; x<5; x++)
		array[x].print();
	printf("\n");
	delete[] array;
}

int main(){
	// simple_pointer();

	// pointers_walking_arrays();
	// pointers_walking_arrays2();

	// scope_of_variables();
	// scope_of_variables2();

	// malloc_simple();
	// malloc_single();
	// calloc_call();
	// realloc_example();
	// page_size();

	// object_malloc();
	// object_new();
	// some_other_scope();
	object_array();
	return 0;
}