#include <map>
#include <functional>
#include <iostream>
#include <stdexcept>

struct Switcher {
    std::map<int, std::function<void()>> cases_;

    void addCase(int key, std::function<void()> func) {
        cases_[key] = func;
    }

    void operator()(int key) {
        if (cases_.find(key) == cases_.end()) {
            throw std::runtime_error("No case for this key");
        }
        cases_[key]();
    }
};

void testCase1() {
    std::cout << "Case 1 executed\n";
}

void testCase2() {
    std::cout << "Case 2 executed\n";
}

int main() {
    Switcher sw;
    sw.addCase(1, testCase1);
    sw.addCase(2, testCase2);

    sw(1); 
    sw(2); 

    try {
        sw(3);
    } catch (std::runtime_error& e) {
        std::cout << e.what() << "\n";
    }

    return 0;
}
