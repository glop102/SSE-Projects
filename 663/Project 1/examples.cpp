#include <stdlib.h>
#include <stdio.h>

//1-11 = 16:00 to 17:30 - move files in git and setup readme files
//1-12 = 18:00 to 18:30 - start on example.cpp
//1-13 = 19:00 to 2:30 - make outline of example.cpp, get basic things ready, simple coding start, get VM ready with visual studio and cygwin+git, start latex document

/* topics

simple pointers in a 2d memory
pointers to pointers
pointers are invalid outside of their scope
	show still get right value when read from invalid location when ar leaves the scope
	explain why this is bad
pointers to walk an array
	going out of bounds of the array
malloc() - a "replacment" for global variables
	gives back memory that your program holds until the program ends
	free() - tell the OS that we dont need this memory any more
calloc()
realloc()
	what it does
	example making a dynamicly sizing array (like std::vector) with a struct and functions
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
	//normal way
	int a;
	a = 10;
	printf("%d\n",a);


	int *p;
	p = &a;
	printf("%d\n",*p);

	*p = 25;
	printf("%d\n",a);
}

int main(){
	simple_pointer();
	return 0;
}