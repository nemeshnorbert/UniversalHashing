#ifndef UNIVERSAL_HASHING_FIXED_SET_H_
#define UNIVERSAL_HASHING_FIXED_SET_H_

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

#include "UniversalHashHelper.h"

// Class used to check if a given number is in the given set.
// Internally this is a two level hash table.
template <typename ValueType, typename HashHelperType = UniversalHashHelper<ValueType>>
class FixedSet
{
private:
    // A record in a hash table to store the value and the flag if the record is not used
    struct Node
    {
        Node()
        : value()
        , isFree(true)
        {}

        bool isFree;
        ValueType value;
    };

    using HashProviderType = typename HashHelperType::HashProviderType;

public:
    FixedSet()
        : table_()
        , firstLevelHasher_()
        , secondLevelHashers_()
    {}

    // Initializes a set with given values. Note: values must not contain duplicates!
    void Initialize(const std::vector<ValueType>& values)
    {
        table_.clear();
        InitializeFirstLevelTable(values);
        InitializeAllSecondLevelTables(values);
    }

    // Checks if value belongs to a fixed_set
    bool Contains(const ValueType& value) const
    {
        size_t firstLevelCode = firstLevelHasher_(value);
        if (!table_[firstLevelCode].empty())
        {
            size_t secondLevelCode = secondLevelHashers_[firstLevelCode](value);

            if (!table_[firstLevelCode][secondLevelCode].isFree)
            {
                return value == table_[firstLevelCode][secondLevelCode].value;
            }
        }
        return false;
    }

private:
    // Initializes first level hash table. 
    // Actually there is no values in the table after this call
    void InitializeFirstLevelTable(const std::vector<ValueType>& values)
    {
        size_t count = values.size();

        std::vector<size_t> subtablesSizes(count);
        do
        {
            std::fill(subtablesSizes.begin(), subtablesSizes.end(), 0);
            firstLevelHasher_ = HashHelperType::GetRandomHashProvider(count);
            for (size_t index = 0; index < count; ++index)
            {
                ++subtablesSizes[firstLevelHasher_(values[index])];
            }

            for (size_t subtableIndex = 0; subtableIndex < count; ++subtableIndex)
            {
                subtablesSizes[subtableIndex] *= subtablesSizes[subtableIndex];
            }
        } while (std::accumulate(subtablesSizes.begin(), subtablesSizes.end(), 0ULL)
            > 4 * count);

        table_.resize(count);
        secondLevelHashers_.resize(count);
    }

    // Initializes second level hash tables. Fill the table with values
    void InitializeAllSecondLevelTables(const std::vector<ValueType>& values)
    {
        size_t count = values.size();

        std::vector<std::vector<ValueType>> buckets(count);
        for (size_t index = 0; index < count; ++index)
        {
            size_t bucketId = firstLevelHasher_(values[index]);
            buckets[bucketId].push_back(values[index]);
        }

        for (size_t subtableIndex = 0; subtableIndex < count; ++subtableIndex)
        {
            InitializeSecondLevelTable(subtableIndex, buckets[subtableIndex]);
        }
    }

    // Initializes a table of second level with subtableIndex 
    // using values stored in a bucket
    void InitializeSecondLevelTable(size_t subtableIndex,
        const std::vector<ValueType>& bucket)
    {
        size_t count = bucket.size() * bucket.size();
        table_[subtableIndex].resize(count);

        bool collisionsFound = false;
        do
        {
            collisionsFound = false;
            secondLevelHashers_[subtableIndex]
                = HashHelperType::GetRandomHashProvider(count);

            for (size_t index = 0; index < bucket.size(); ++index)
            {
                size_t hash = secondLevelHashers_[subtableIndex](bucket[index]);
                if (table_[subtableIndex][hash].isFree)
                {
                    table_[subtableIndex][hash].value = bucket[index];
                    table_[subtableIndex][hash].isFree = false;
                }
                else
                {
                    SetSubtableFree(subtableIndex);
                    collisionsFound = true;
                    break;
                }
            }
        } while (collisionsFound);
    }

    // Sets all flags in the table of second level to false if initialization failed
    void SetSubtableFree(size_t subtableIndex)
    {
        for (size_t index = 0; index < table_[subtableIndex].size(); ++index)
        {
            table_[subtableIndex][index].isFree = true;
        }
    }

private:
    // Collection of tables of second level
    std::vector<std::vector<Node>> table_;
    // Hash functions of tables of second levels
    std::vector<HashProviderType> secondLevelHashers_;
    // Hash function for initialization of table of first level i.e. table_
    HashProviderType firstLevelHasher_;
};

#endif