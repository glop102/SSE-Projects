#include "pch.h"
#include "../test_1/simple_functions.cpp"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(SimpleFunctions, voidOperation) {
	TestFunction();
}
TEST(SimpleFunctions, simpleFive) {
	ASSERT_EQ( hardCodedFive() ,5);
}
TEST(SimpleFunctions, simpleFive_fail) {
	EXPECT_EQ(hardCodedFive(), 6);
}

//Abusing that structs always do memory layout the same way
TEST(BadPractice, castingStructs) {
	struct S1 *s = new struct S1;
	changeS1(s);
	EXPECT_EQ(s->a, 100);
	EXPECT_EQ(s->b, 50);
	changeS2((struct S2*)s);
	EXPECT_EQ(s->a, 4);
	EXPECT_EQ(s->b, 5);
	delete s;
}
TEST(BadPractice, castingStructsAgain) {
	struct S1 *s = new struct S1;
	changeS1(s);
	EXPECT_EQ(s->a, 100);
	EXPECT_EQ(s->b, 50);
	changeUsingBytes((struct S3*)s,1234567);
	EXPECT_EQ(s->a, 1234567);
	EXPECT_EQ(s->b, 50);
	changeUsingBytes((struct S3*)s, -1234567);
	EXPECT_EQ(s->a, -1234567);
	delete s;
}
TEST(BadPractice, derefrencingLoacalVariables) {
	int *a = returningLocalVariable();
	EXPECT_NE(*a,5);
}
TEST(BadPractice, castingClasses) {
	//this works the same as the structs - if the sizes are the same, then everything works out just fine
	Ex1 *a = new Ex1;
	a->setValues();
	EXPECT_EQ(a->a, 10);
	EXPECT_EQ(a->b, 20);

	((Ex2*)a)->setValues();
	EXPECT_EQ(a->a, 30);
	EXPECT_EQ(a->b, 40);

	((Ex3*)a)->changeValuesToSomethingElse();
	EXPECT_EQ(a->a, 50);
	EXPECT_EQ(a->b, 60);

	((Ex4*)a)->changeValuesToSomethingElse();
	EXPECT_EQ(a->a, 70);
	EXPECT_EQ(a->b, 80);

	((Ex5*)a)->changeValuesToSomethingElse();
	EXPECT_EQ(a->a, 90);
	EXPECT_EQ(a->b,100);

	((Ex6*)a)->changeValuesToSomethingElse();
	EXPECT_EQ(a->a, 110);
	EXPECT_EQ(a->b, 120);

	//this access an entierly new variable that our object doesn't have
	//this is bound to crash programs when data changes over page lines or something, and really drive people nuts
	((Ex6*)a)->randomOtherFunction();
	EXPECT_EQ(a->a, 700);
	EXPECT_EQ(a->b, 800);

	delete a;
}

//TEST(BadPractice, castingClasses_breaking) {
//	Ex1 *a = new Ex1;
//	Ex1 *b = new Ex1;

	//this access an entierly new variable that our object doesn't have
	//this time around, it seems to cause an infinate loop of some sort, and never finishes
//	((Ex6*)a)->randomOtherFunction();
//	EXPECT_EQ(a->a, 700);
//	EXPECT_EQ(a->b, 800);
//	EXPECT_EQ(b->a, 900);

//	delete a;
//	delete b;
	//even telling it to cancel the test does nothing to stop it
	//the cpu is being used 0% but the program never actually exits
	//i have to kill it under task manager
	//the only operational difference is that i have defined a second object b
	//when a cast as something else does an erronious write to a third variable, it moves into territory it should not have
//}