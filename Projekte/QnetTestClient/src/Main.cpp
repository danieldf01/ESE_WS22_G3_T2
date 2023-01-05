#include <iostream>
#include <gtest/gtest.h>
using namespace std;

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	int result = RUN_ALL_TESTS();
	return result;
}
