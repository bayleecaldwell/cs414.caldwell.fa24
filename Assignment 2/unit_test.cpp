#include <iostream>
#include "case_of.h"

int main() {
    std::unordered_map<int, std::function<std::string()>> cases = {
        {1, []() { return "Value is 1"; }},
        {2, []() { return "Value is 2"; }},
        {3, []() { return "Value is 3"; }},
        {4, []() { return "Value is 4"; }}
    };

    if (CaseOf(1, cases, []() { return "Unknown value"; }).evaluate() != "Value is 1") {
        std::cout << "Test failed: CaseOf(1, cases, []() { return \"Unknown value\"; }).evaluate() != \"Value is 1\"\n";
        return 1;
    }

    if (CaseOf(2, cases, []() { return "Unknown value"; }).evaluate() != "Value is 2") {
        std::cout << "Test failed: CaseOf(2, cases, []() { return \"Unknown value\"; }).evaluate() != \"Value is 2\"\n";
        return 1;
    }

    if (CaseOf(3, cases, []() { return "Unknown value"; }).evaluate() != "Value is 3") {
        std::cout << "Test failed: CaseOf(3, cases, []() { return \"Unknown value\"; }).evaluate() != \"Value is 3\"\n";
        return 1;
    }

    if (CaseOf(4, cases, []() { return "Unknown value"; }).evaluate() != "Value is 4") {
        std::cout << "Test failed: CaseOf(4, cases, []() { return \"Unknown value\"; }).evaluate() != \"Value is 4\"\n";
        return 1;
    }

    if (CaseOf(5, cases, []() { return "Unknown value"; }).evaluate() != "Unknown value") {
        std::cout << "Test failed: CaseOf(5, cases, []() { return \"Unknown value\"; }).evaluate() != \"Unknown value\"\n";
        return 1;
    }

    std::cout << "All tests passed\n";
    return 0;
}
