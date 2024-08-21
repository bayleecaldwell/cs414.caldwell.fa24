#include <iostream>
#include <cstdlib>
#include <ctime>

void FillWithRandomNumbers(int data[], int size) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = 0; i < size; ++i) {
        data[i] = std::rand() % 100001; 
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
    const int size = 100;
    int data[size];

    FillWithRandomNumbers(data, size);
    SortTheArray(data, size);

    for (int i = 0; i < size; ++i) {
        std::cout << data[i] << " ";
    }

    return 0;
}
