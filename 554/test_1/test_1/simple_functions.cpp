#pragma once
#include "stdafx.h"

void TestFunction() {
	//does nothing
}

int hardCodedFive() {
	return 5;
}

struct S1 {
	int a, b;
};
struct S2 {
	int c, d;
};
void changeS1(struct S1 *s) {
	s->a = 100;
	s->b = 50;
}
void changeS2(struct S2 *s) {
	s->c = 4;
	s->d = 5;
}

struct S3 {
	char first;
	unsigned char second;
	unsigned char third;
	unsigned char fourth;
};
void changeUsingBytes(struct S3 *s, int val) {
	s->first = (val >> 0 * 8) & 0xFF;
	s->second = (val >> 1 * 8) & 0xFF;
	s->third = (val >> 2 * 8) & 0xFF;
	s->fourth = (val >> 3 * 8) & 0xFF;
}

int* returningLocalVariable() {
	int a = 5;
	return &a;
}


class Ex1 {
public:
	int a;
	int b;
	void setValues() { a = 10, b = 20; }
};
class Ex2 {
public:
	int c;
	int d;
	void setValues() { c = 30, d = 40; }
};
class Ex3 {
public:
	int e;
	int f;
	void changeValuesToSomethingElse() { e = 50, f = 60; }
};
class Ex4 {
public:
	int g;
	int h;
	void changeValuesToSomethingElse() { g = 70, h = 80; }
	void randomOtherFunction() { g = 700, h = 800; };
};
class Ex5 {
public:
	int g;
	int h;
	void randomOtherFunction() { g = 700, h = 800; };
	void changeValuesToSomethingElse() { g = 90, h = 100; }
};
class Ex6 {
public:
	int g;
	int h;
	int q;
	void randomOtherFunction() { g = 700, h = 800, q=900; };
	void changeValuesToSomethingElse() { g = 110, h = 120; }
};