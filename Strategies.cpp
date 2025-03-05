#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm>

void func() {
    std::cout << "Hello world" << "\r ";
}

int linear(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int bin(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) { return mid; }
        if (arr[mid] < target) { left = mid + 1; }
        else { right = mid - 1; }
    }
    return -1;
}

void strategyA(int arr[], int size, int index) {
    if (index > 0) {
        std::swap(arr[index], arr[0]);
    }
}

void strategyB(int arr[], int index) {
    if (index > 0) {
        std::swap(arr[index], arr[index - 1]);
    }
}

void strategyC(int arr[], int counts[], int index) {
    if (index > 0 && counts[index] > counts[index - 1]) {
        std::swap(arr[index], arr[index - 1]);
    }
}

int main() {
    unsigned n;
    std::cout << "Введите размер массива: ";
    std::cin >> n;
    int* arr = new int[n];
    int* counts = new int[n]();
    std::srand(static_cast<unsigned>(std::time(0)));
    for (unsigned i = 0; i < n; ++i) {
        arr[i] = std::rand() % n;
    }
    std::cout << std::endl;
    //std::sort(arr, arr + n); // Сортировка для бинарного поиска
    float sum = 0;

    auto begin = std::chrono::steady_clock::now();
    for (unsigned cnt0 = 10; cnt0 != 0; --cnt0) {
        for (unsigned cnt = 10000; cnt != 0; --cnt) {
            int target = ((std::rand() % n) > n/2)*(std::rand() % n) + ((std::rand() % n) <= n/2)*(80); // Определение искомого
            int index = linear(arr, n, target);
            if (index != -1) {
                 counts[index]++;
                // strategyA(arr, n, index);
                // strategyB(arr, index);
                 strategyC(arr, counts, index);
            }
        }
    }
    auto end = std::chrono::steady_clock::now();
    auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    sum += time_span.count();
    std::cout << "Итог: " << sum / 100000 << std::endl;

    delete[] arr;
    delete[] counts;
    return 0;
}
