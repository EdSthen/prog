#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm>

void func() {
    std :: cout << "Hello␣world" << "\r " ;
}

int linear(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < i; j++){
            if (arr[i] + arr[j] == target) {
                return i;
            }
        }
    }
    return -1;
}
int bin(int arr[], int size, int target) {
    int left = 0;
    int right= size - 1;
    while (left <= right) {
        int scope = arr[left] + arr[right];
        if (scope == target){
            return 1;
        }
        else if (scope < target){
            left++;
        }
        else{
            right--;
        }
    }
    return -1;
}
int main() {
    unsigned n;
    std::cout << "Введите размер массива: ";
    std::cin >> n;
    int* arr = new int[n];
    std::srand(static_cast<unsigned>(std::time(0)));
    for (unsigned i = 0; i < n; ++i) {
        arr[i] = std::rand() % n;
    }
    std::cout << std::endl;
    //std::sort(arr, arr + n); //сотрировка для bin
    float sum = 0;
    auto begin = std :: chrono :: steady_clock ::now();
    for (unsigned cnt0 = 10; cnt0 != 0;--cnt0){
    int target = -(std::rand() % n); //определение искомого
    for (unsigned cnt = 10; cnt != 0;--cnt){
    linear (arr, n, target); //вызов функции
    std :: cout << 100-(cnt+10*(cnt0-1)) <<"%"<< std::endl;
    }
    }
    auto end = std :: chrono :: steady_clock ::now();
    auto time_span =
    std :: chrono :: duration_cast<std :: chrono :: milliseconds >(end- begin );
    sum+=time_span.count();
    std :: cout << "Итог: " << sum/100 << std :: endl;
    
    return 0;
}