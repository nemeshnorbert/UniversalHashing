#include <cassert>
#include <set>
#include "fixed_set.h"
#include "io_tools.h"


template <typename ValueType>
std::vector<ValueType> GetRandomValues(const ValueType& min, const ValueType& max, size_t count)
{
    assert(min <= max);
    static std::mt19937_64 engine;
    std::uniform_int_distribution<ValueType> generator(min, max);
    std::vector<ValueType> values;
    for (size_t index = 0; index < count; ++index)
    {
        values.push_back(generator(engine));
    }
    return values;
}


template <typename ValueType>
bool RunTest(const std::vector<ValueType>& values, const std::vector<ValueType>& numbers)
{
    FixedSet<ValueType> checker;
    checker.Initialize(values);
    std::set<ValueType> collection = std::set<ValueType>(values.begin(), values.end());

    auto& stream = std::cout;
    for (auto iterator = numbers.begin(); iterator != numbers.end(); ++iterator)
    {
        const auto number = *iterator;
        auto decision = checker.Contains(number);
        auto truth = (collection.find(number) != collection.end());
        if (decision != truth)
        {
            stream
                << "Error: value "
                << number
                << (truth ? " belongs " : " does not belong ")
                << "to the fixed set "
                << "while algorithm says it "
                << (decision ? "is" : "is not")
                << "\n";
            stream << "Values:\n";
            WriteValues(stream, values);
            return false;
        }
    }
    stream << "Test passed\n";
    return true;
}

int main() {
    for (int attempt = 0; attempt < 10; ++attempt)
    {
        if(!RunTest(GetRandomValues(0, 10000, 100), GetRandomValues(-10000, 10000, 100000)))
        {
            return 1;
        }
    }
    return 0;
}
