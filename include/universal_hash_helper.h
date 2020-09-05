#ifndef UNIVERSAL_HASHING_UNIVERSAL_HASH_HELPER_H_
#define UNIVERSAL_HASHING_UNIVERSAL_HASH_HELPER_H_

#include <random>
#include <cstddef>

// Template class representing universal hashing
template<typename ValueType>
class UniversalHashHelper;

// Specialization for universal hash functions on int
template<>
class UniversalHashHelper<int>
{
public:
    class HashProvider
    {
    public:
        HashProvider()
            : multiplier_(0)
            , summand_(0)
            , count_(0)
            , prime_(0)
        {}

        HashProvider(size_t multiplier, size_t summand, size_t count, size_t prime)
            : multiplier_(multiplier)
            , summand_(summand)
            , count_(count)
            , prime_(prime)
        {}

        size_t operator () (int value) const
        {
            long long int multiplier = multiplier_;
            long long int summand = summand_;
            long long int prime = prime_;
            long long int count = count_;
            long long int number = value;

            long long int hash = (multiplier * number + summand) % prime;
            return static_cast<size_t>(((hash + prime) % prime) % count);
        }

    private:
        size_t multiplier_;
        size_t summand_;
        size_t count_;
        size_t prime_;
    };

    using HashProviderType = HashProvider;

    // Specialization for universal hash functions on int
    static HashProviderType GetRandomHashProvider(size_t collectionSize)
    {
        const size_t PRIME = 2147483659;

        static std::mt19937_64 engine;
        static std::uniform_int_distribution<size_t> aGenerator(1, PRIME);
        static std::uniform_int_distribution<size_t> bGenerator(0, PRIME);

        return HashProvider(aGenerator(engine), bGenerator(engine), collectionSize, PRIME);
    }
};

#endif
