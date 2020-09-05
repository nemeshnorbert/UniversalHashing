#ifndef UNIVERSAL_HASHING_IO_TOOLS_H_
#define UNIVERSAL_HASHING_IO_TOOLS_H_

#include <vector>
#include <iostream>

// Template function to read values from the stream
template <typename ValueType>
std::vector<ValueType> ReadValues(std::istream& inputStream, size_t count)
{
    std::vector<ValueType> numbers(count);

    for (size_t index = 0; index < count; ++index)
    {
        inputStream >> numbers[index];
    }

    return numbers;
}

template<typename ValueType>
void WriteValues(std::ostream& outputStream,
    const std::vector<ValueType>& values,
    bool printSize = false)
{
    if (printSize)
    {
        outputStream << values.size() << '\n';
    }
    for (size_t index = 0; index < values.size(); ++index)
    {
        outputStream << values[index] << ' ';
    }
    outputStream << '\n';
}

// Writes results of checking to the stream. true -> "Yes", false -> "No"
void WriteResponses(std::ostream& outputStream, const std::vector<bool>& responses)
{
    for (size_t index = 0; index < responses.size(); ++index)
    {
        outputStream << (responses[index] ? "Yes" : "No") << '\n';
    }
}


#endif
