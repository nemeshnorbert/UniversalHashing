#ifndef UNIVERSAL_HASHING_TESTING_TOOLS_H_
#define UNIVERSAL_HASHING_TESTING_TOOLS_H_

// Checks which values in the range [first, last) are in checker's list
template <typename CheckerType, typename IteratorType>
std::vector<bool> CheckContainment(const CheckerType& checker,
    IteratorType first,
    IteratorType last)
{
    std::vector<bool> responses;
    for (auto iterator = first; iterator != last; ++iterator)
    {
        responses.push_back(checker.Contains(*iterator));
    }

    return responses;
}

// Checks which values in collection are in checker's list
template <typename CheckerType, typename CollectionType>
std::vector<bool> CheckContainment(const CheckerType& checker,
    const CollectionType& collection)
{
    return CheckContainment(checker, collection.begin(), collection.end());
}

template <typename ValueType>
bool Test(const std::vector<ValueType>& values,
    const std::vector<ValueType>& numbers,
    const std::vector<bool>& answers)
{
    FixedSet<ValueType> checker;
    checker.Initialize(values);
    auto responses = CheckContainment(checker, numbers);
    std::ostream& stream = std::cerr;
    if (answers != responses)
    {

        stream << "Wrong answer\nfor values: ";
        WriteValues(stream, values);
        stream << "and numbers: ";
        WriteValues(stream, numbers);
        stream << "\nThe correct answer is: ";
        WriteValues(stream, answers);
        return false;
    }
    else
    {
        stream << "Test passed!\n";
    }

    return true;
}

template <typename ValueType>
void Run()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    FixedSet<ValueType> checker;
    checker.Initialize(ReadValues<ValueType>(std::cin));
    WriteResponses(std::cout, CheckContainment(checker, ReadValues<ValueType>(std::cin)));
}


#endif