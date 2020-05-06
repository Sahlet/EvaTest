// EvaTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "DiscountSplitter.h"

std::list<records::CheckRow> createTestData()
{
    return
    {
        { L"A", 127, 3, 23 },
        { L"A", 127, 4, 23 },
        { L"A", 128, 4, 23 },
        { L"B", 353, 5, 45 },
        { L"C", 0, 3, 23 },
        { L"D", 10, 4, 124 },
        { L"E", 20, 5, 25 },
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

bool testSplittedCheck(const std::list<records::CheckRow>& check, const std::list<records::CheckRow>& splittedCheck)
{
    return false;
}

int main()
{
    auto check = createTestData();
    auto splittedCheck = check;

    splitByDiscount(splittedCheck);

    std::cout << (testSplittedCheck(check, splittedCheck) ? "test is passed" : "test is NOT passed") << std::endl;
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
