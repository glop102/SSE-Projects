#include <stdlib.h>
#include <stdio.h>

//1-11 = 16:00 to 17:30 - move files in git and setup readme files
//1-12 = 18:00 to 18:30 - start on example.cpp
//1-13 = 19:00 to 2:30 - make outline of example.cpp, get basic things ready, simple coding start, get VM ready with visual studio and cygwin+git, start latex document
//1-14 = 00:00 to 4:00 - work on examples and report

/* topics

simple pointers in a 1d memory
pointers to walk an array
	going out of bounds of the array
pointers are invalid outside of their scope
	show still get right value when read from invalid location when ar leaves the scope
	explain why this is bad
pointers to pointers - 2d array
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

int main(){
	// simple_pointer();
	// pointers_walking_arrays();
	// pointers_walking_arrays2();
	return 0;
}