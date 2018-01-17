#include <stdio.h>
#include <stdlib.h>

template <typename T>
class vector{
	T* data;
	int length,capacity;
public:
	vector(){
		data = (T*)malloc(sizeof(T));
		length = 0;
		capacity = 1;
	};
	~vector(){delete[] data;}
	void push_back(T& item);
	void push_back(T item);
	void pop_back();
	T& operator[](int index);
	int size(){return length;}
};
template<typename T>
void vector<T>::push_back(T& item){
	if(length >= capacity){
		//need more room, time to realloc()
		int delta = capacity;
		delta %= 128; //only get bigger by steps of 128 at most
		data = (T*)realloc(data,(delta+capacity) * sizeof(T));
		capacity += delta;
	}
	data[length] = item;
	length++;
}
template<typename T>
void vector<T>::push_back(T item){
	if(length >= capacity){
		//need more room, time to realloc()
		int delta = capacity;
		delta %= 128; //only get bigger by steps of 128 at most
		data = (T*)realloc(data,(delta+capacity) * sizeof(T));
		capacity += delta;
	}
	data[length] = item;
	length++;
}

template<typename T>
void vector<T>::pop_back(){
	length--;
}

template<typename T>
T& vector<T>::operator[](int index){
	return data[index];
}

class Counter{
	static int counter;
public:
	int our_value;
	Counter(){
		our_value = counter;
		counter++;
	}
	void print(){printf(" C%d ",our_value);}
};
int Counter::counter = 0;

int main(){
	// vector<int> test;
	// //add items
	// for(int x=0; x<10; x++)
	// 	test.push_back(x);
	// //read items
	// for(int x=0; x<test.size(); x++)
	// 	printf(" %d ",test[x]);
	// printf("\n");

	// //remove items
	// for(int x=0; x<5; x++)
	// 	test.pop_back();
	// //read items
	// for(int x=0; x<test.size(); x++)
	// 	printf(" %d ",test[x]);	
	// printf("\n");

	// //change items
	// for(int x=0; x<5; x++)
	// 	test[x] = (x+1) * 5;
	// //read items
	// for(int x=0; x<test.size(); x++)
	// 	printf(" %d ",test[x]);	
	// printf("\n");

	vector<Counter> test;
	//add items
	for(int x=0; x<10; x++)
		test.push_back(Counter());
	//read items
	for(int x=0; x<test.size(); x++)
		test[x].print();
	printf("\n");

	//remove items
	for(int x=0; x<5; x++)
		test.pop_back();
	//read items
	for(int x=0; x<test.size(); x++)
		test[x].print();
	printf("\n");

	//change items
	for(int x=0; x<5; x++)
		test[x].our_value = (x+1) * 5;
	//read items
	for(int x=0; x<test.size(); x++)
		test[x].print();
	printf("\n");

	return 0;
}