#include "fixed_set.h"
#include "io_tools.h"

void Run()
{
    std::ostream& stream = std::cout;
    stream
        << "Given a set of integers we perform an O(n^2) preprocessing"
        << " to produce a fixed set.\n"
        << "This structure allows us in O(1) time determine if a given"
        << " number belongs to a fixed set.\n";
    using ValueType = int;
    FixedSet<ValueType> checker;
    size_t fixedSetSize = 0;
    stream << "Enter fixed set size: ";
    std::cin >> fixedSetSize;
    stream << "Enter elements of the fixed set: ";
    checker.Initialize(ReadValues<ValueType>(std::cin, fixedSetSize));
    stream << "Enter test set size: ";
    size_t testSetSize = 0;
    std::cin >> testSetSize;
    stream << "Enter numbers you want to check belong to the fixed set: ";
    std::vector<ValueType> numbers = ReadValues<ValueType>(std::cin, testSetSize);
    stream << "Result: ";
    for (auto iterator = numbers.begin(); iterator != numbers.end(); ++iterator) {
        if (checker.Contains(*iterator))
        {
            stream << *iterator << " belongs to the fixed set\n";
        }
        else
        {
            stream << *iterator << " doesn't belong to the fixed set\n";
        }
    }
}


int main()
{
    Run();
    return 0;
}

