#include "testCases.hpp"


int main(void)
{
    Tests testCase;
    testCase.TestOne(); // Border/Movement
    testCase.TestTwo(); // Block collision
    testCase.TestThree(); // rotation
    testCase.TestFour(); // Row Clear
    testCase.TestFive(); // rotation collision
}