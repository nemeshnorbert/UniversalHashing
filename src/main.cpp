#include "fixed_set.h"
#include "io_tools.h"

void Run()
{
    std::ostream& out = std::cout;
    std::istream& in = std::cin;
    out
        << "Given a set of integers we perform an O(n^2) preprocessing"
        << " to produce a fixed set.\n"
        << "This structure allows us in O(1) time determine if a given"
        << " number belongs to a fixed set.\n";
    using ValueType = int;
    FixedSet<ValueType> checker;
    size_t fixedSetSize = 0;
    out << "Enter fixed set size: ";
    in >> fixedSetSize;
    out << "Enter elements of the fixed set: ";
    checker.Initialize(ReadValues<ValueType>(in, fixedSetSize));
    out << "Enter test set size: ";
    size_t testSetSize = 0;
    in >> testSetSize;
    out << "Enter numbers you want to check belong to the fixed set: ";
    std::vector<ValueType> numbers = ReadValues<ValueType>(in, testSetSize);
    out << "Result: ";
    for (auto iterator = numbers.begin(); iterator != numbers.end(); ++iterator) {
        if (checker.Contains(*iterator))
        {
            out << *iterator << " belongs to the fixed set\n";
        }
        else
        {
            out << *iterator << " doesn't belong to the fixed set\n";
        }
    }
}


int main()
{
    Run();
    return 0;
}

