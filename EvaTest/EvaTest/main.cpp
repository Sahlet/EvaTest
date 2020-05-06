// EvaTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <assert.h>
#include "DiscountSplitter.h"

std::list<records::CheckRow> createTestData()
{
    return
    {
        { L"A", 127, 3, 23 },
        { L"A", 127, 4, 23 },
        { L"A", 128, 4, 23 },
        { L"B", 353, 5, 45 },
        { L"E", 20, 5, 0 },
        { L"F", 30, 6, 26 },
        { L"G", 40, 7, 27 },
        { L"H", 50, 8, 28 },
        { L"I", 60, 9, 29 },
        { L"J", 70, 10, 30 },
        { L"K", 80, 11, 100 },
        { L"L", 90, 12, 100 },
        { L"M", 100, 13, 100 },
        { L"N", 110, 14, 100 },
        { L"O", 120, 15, 100 },
        { L"P", 130, 16, 100 },
        { L"Q", 140, 17, 100 },
        { L"R", 150, 18, 100 },
        { L"S", 160, 19, 100 }
    };
}

bool testSplittingWithInvalidData()
{
    try
    {
        std::list<records::CheckRow> check =
        {
            { L"D", 10, 4, 124 }
        };
        splitByDiscount(check);
        return false;
    }
    catch (const std::exception & e)
    {
        if (e.what() != std::string("discount is greater than price"))
        {
            return false;
        }
    }

    try
    {
        std::list<records::CheckRow> check =
        {
            { L"C", 0, 3, 23 }
        };
        splitByDiscount(check);
        return false;
    }
    catch (const std::exception & e)
    {
        if (e.what() != std::string("the price is 0"))
        {
            return false;
        }
    }

    try
    {
        std::list<records::CheckRow> check =
        {
            { L"C", 123, 0, 23 }
        };
        splitByDiscount(check);
        return false;
    }
    catch (const std::exception & e)
    {
        if (e.what() != std::string("the count is 0"))
        {
            return false;
        }
    }

    return true;
}

bool testSplittedCheck(const std::list<records::CheckRow>& srcCheck, const std::list<records::CheckRow>& splittedCheck)
{
    struct Key
    {
        std::wstring name;
        unsigned int priceForOne = 0;

        bool operator < (const Key& right)
        {
            bool nameLess = this->name < right.name;
            if (nameLess)
            {
                return nameLess;
            }

            if (this->name != right.name)
            {
                return this->priceForOne < right.priceForOne;
            }

            return nameLess;
        }
    };

    typedef records::CheckRow Value;

    std::multimap<Key, Value> srcData, processedData;

    //group rows with equal keys
    for (auto& elem : srcCheck)
    {
        Key key = { elem.name, elem.priceForOne };
        auto iter = srcData.find(key);
        if (iter != srcData.end())
        {
            iter->second.count += elem.count;
            iter->second.sumDiscount += elem.sumDiscount;
        }
        else
        {
            srcData.emplace(key, elem);
        }
    }

    for (auto& elem : splittedCheck)
    {
        processedData.insert({ elem.name, elem.priceForOne }, elem);
    }

    try
    {
#pragma region Test: srcCheck has no invalid data
        for (auto& elem : srcCheck)
        {
            assert(elem.count >= 1);
            assert(elem.priceForOne >= 1);
            assert(elem.count * elem.priceForOne >= elem.sumDiscount);
        }
#pragma endregion

#pragma region Test: splittedCheck has no invalid data
        for (auto& elem : splittedCheck)
        {
            assert(elem.count >= 1);
            assert(elem.priceForOne >= 1);
            assert(elem.count * elem.priceForOne >= elem.sumDiscount);
        }
#pragma endregion

#pragma region Test: equal key set
        for (auto& elem : srcData)
        {
            auto iter = processedData.find(elem.first);
            assert(iter != processedData.end());
        }

        for (auto& elem : processedData)
        {
            auto iter = srcData.find(elem.first);
            assert(iter != srcData.end());
        }
#pragma endregion

#pragma region Test: sum count and discount same with src count end discount
        for (auto& elem : srcData)
        {
            auto range = processedData.equal_range(elem.first);

            unsigned int count = 0;
            unsigned int sumDiscount = 0;
            for (auto iter = range.first; iter != range.second; iter++)
            {
                count += iter->second.count;
                sumDiscount += iter->second.sumDiscount;
            }
            
            assert(count == elem.second.count);
            assert(sumDiscount == elem.second.sumDiscount);
        }
#pragma endregion

#pragma region discount is divided by count in splittedCheck
        for (auto& elem : splittedCheck)
        {
            assert((elem.sumDiscount % elem.count) == 0);
        }
#pragma endregion
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }

    return true;
}

int main()
{
    auto check = createTestData();
    auto splittedCheck = check;

    splitByDiscount(splittedCheck);

    std::cout <<
        (testSplittedCheck(check, splittedCheck) && testSplittingWithInvalidData()
            ? "test is passed" : "test is NOT passed")
        << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
