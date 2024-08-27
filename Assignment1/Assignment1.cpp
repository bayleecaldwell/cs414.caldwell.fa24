#include <iostream>
#include <random>
#include <algorithm>

void FillWithRandomNumbers(int data[], int size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100000);

    for (int i = 0; i < size; ++i) {
        data[i] = dis(gen);
    }
}

void SortTheArray(int data[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (data[j] > data[j + 1]) {
                std::swap(data[j], data[j + 1]);
            }
        }
    }
}

int main() {
    const int size = 10;
    int data[size];

    FillWithRandomNumbers(data, size);
    SortTheArray(data, size);

    for (int i = 0; i < size; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
