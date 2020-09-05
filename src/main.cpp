#include "fixed_set.h"
#include "io_tools.h"

// Given a fixed set of integers we need to process in O(1) time a lot of
// requests to determine whether a new number belongs to a given fixed set of integers.

template <typename ValueType>
void Run()
{
    FixedSet<ValueType> checker;
    size_t fixedSetSize = 0;
    std::cout << "Enter fixed set size:\n";
    std::cin >> fixedSetSize;
    std::cout << "Enter elements of the fixed set\n";
    checker.Initialize(ReadValues<ValueType>(std::cin, fixedSetSize));
    std::cout << "Enter test set size:\n";
    size_t testSetSize = 0;
    std::cin >> testSetSize;
    std::cout << "Enter numbers you want to check belong to the fixed set\n";
    std::vector<ValueType> numbers = ReadValues<ValueType>(std::cin, testSetSize);
    std::cout << "Result:\n";
    for (auto iterator = numbers.begin(); iterator != numbers.end(); ++iterator) {
        if (checker.Contains(*iterator))
        {
            std::cout << *iterator << " belongs to the fixed set\n";
        }
        else
        {
            std::cout << *iterator << " doesn't belong to the fixed set\n";
        }
    }
}


int main()
{
    Run<int>();
    return 0;
}

