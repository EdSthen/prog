#include <iostream>
#include <chrono>
#include <cmath>
#include <fstream>

struct DynamicArray {
    int* data;
    size_t size;
    size_t capacity;
};

DynamicArray create_array(size_t initial_capacity = 0) {
    DynamicArray arr;
    arr.data = initial_capacity ? new int[initial_capacity] : nullptr; //выделение памяти по потребности
    arr.size = 0;
    arr.capacity = initial_capacity;
    return arr;
}

void delete_array(DynamicArray& arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = arr.capacity = 0;
}


void Strat1(DynamicArray& arr, int value) {
    if (arr.size == arr.capacity) {
        int* new_data = new int[arr.capacity + 1]; // новый массив и его инициализация
        for (size_t i = 0; i < arr.size; ++i) {
            new_data[i] = arr.data[i];
        }
        delete[] arr.data;
        arr.data = new_data;
        arr.capacity++;
    }
    arr.data[arr.size++] = value; // вносим значение
}


void Strat2(DynamicArray& arr, int value) {
    if (arr.size == arr.capacity) {
        const size_t addition = 100; //дополнение за раз
        int* new_data = new int[arr.capacity + addition];
        for (size_t i = 0; i < arr.size; ++i) {
            new_data[i] = arr.data[i];
        }
        delete[] arr.data;
        arr.data = new_data;
        arr.capacity += addition;
    }
    arr.data[arr.size++] = value;
}


void Strat3(DynamicArray& arr, int value) {
    if (arr.size == arr.capacity) {
        size_t new_capacity = arr.capacity == 0 ? 1 : arr.capacity * 2;
        int* new_data = new int[new_capacity];
        for (size_t i = 0; i < arr.size; ++i) {
            new_data[i] = arr.data[i];
        }
        delete[] arr.data;
        arr.data = new_data;
        arr.capacity = new_capacity;
    }
    arr.data[arr.size++] = value;
}

void base() {
    std::ofstream out_file("performance_results.csv"); //вывод в файлик для графиков
    out_file << "N,Time1,Time2,Time3\n";

    const size_t max_n = 200000; //максимум
    const size_t step = 10000; //шаг

    for (size_t n = step; n <= max_n; n += step) {
        auto arr1 = create_array();
        auto start1 = std::chrono::high_resolution_clock::now(); //отсчет
        for (size_t i = 0; i < n; ++i) {
            Strat1(arr1, i);
        }
        auto end1 = std::chrono::high_resolution_clock::now();
        auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count();
        delete_array(arr1);

        auto arr2 = create_array();
        auto start2 = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < n; ++i) {
            Strat2(arr2, i);
        }
        auto end2 = std::chrono::high_resolution_clock::now();
        auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count();
        delete_array(arr2);

        auto arr3 = create_array();
        auto start3 = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < n; ++i) {
            Strat3(arr3, i);
        }
        auto end3 = std::chrono::high_resolution_clock::now();
        auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(end3 - start3).count();
        delete_array(arr3);

        out_file << n << "," << duration1 << "," << duration2 << "," << duration3 << "\n"; //для файлика
        std::cout << "N = " << n << " completed\n";
    }

    out_file.close();
}

int main() {
    base(); //base сделал все сам, в main ничего не понадобилось
    return 0;
}