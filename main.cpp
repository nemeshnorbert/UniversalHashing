// UniversalHashing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "FixedSet.h"
#include "IOTools.h"
#include "TestingTools.h"

// Given a fixed set of integers we need to process in O(1) time a lot of 
// requests to determine whether a new number belongs to a given fixed set of integers.

int main()
{
    Test<int>({ 1, 2, 3 }, { 10, 1, 5, 2 }, { false, true, false, true });
    // Run<int>();
    return 0;
}

