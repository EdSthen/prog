#include <iostream>
#include <chrono>
#include <fstream>
#include <stdexcept>

struct Queue {
    int* data;
    size_t capacity;
    size_t read_idx;
    size_t write_idx;
    size_t size;
};

void queue_new(Queue& q, size_t initial_capacity = 4) {
    q.data = new int[initial_capacity];
    q.capacity = initial_capacity;
    q.read_idx = 0;
    q.write_idx = 0;
    q.size = 0;
}

void queue_del(Queue& q) {
    delete[] q.data;
    q.data = nullptr;
    q.capacity = 0;
    q.read_idx = 0;
    q.write_idx = 0;
    q.size = 0;
}

bool queue_poll(Queue& q, int& element) {
    if (q.size == 0) {
        return false;
    }
    
    element = q.data[q.read_idx];
    q.read_idx = (q.read_idx + 1) % q.capacity;
    q.size--;
    return true;
}

bool resize_queue(Queue& q) {
    size_t new_capacity = q.capacity * 2;
    int* new_data = new int[new_capacity];

    for (size_t i = 0; i < q.size; ++i) {
        new_data[i] = q.data[(q.read_idx + i) % q.capacity];
    }

    delete[] q.data;
    q.data = new_data;
    q.read_idx = 0;
    q.write_idx = q.size;
    q.capacity = new_capacity;
    return true;
}

bool queue_push(Queue& q, int element) {
    if (q.size == q.capacity) {
        if (!resize_queue(q)) {
            return false;
        }
    }
    
    q.data[q.write_idx] = element;
    q.write_idx = (q.write_idx + 1) % q.capacity; //цикл
    q.size++;
    return true;
}

void measure() {
    std::ofstream out_file("queue_performance.csv");
    out_file << "N,PushTime,PollTime\n";

    const size_t max_operations = 1000000;
    const size_t step = 10000;

    Queue q;
    queue_new(q);

    for (size_t n = step; n <= max_operations; n += step) {
        auto start_push = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < n; ++i) {
            if (!queue_push(q, i)) {
                throw std::runtime_error("Push failed");
            }
        }
        auto end_push = std::chrono::high_resolution_clock::now();
        auto push_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_push - start_push).count();

        auto start_poll = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < n; ++i) {
            int element;
            if (!queue_poll(q, element)) {
                throw std::runtime_error("Poll failed");
            }
        }
        auto end_poll = std::chrono::high_resolution_clock::now();
        auto poll_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_poll - start_poll).count();

        out_file << n << "," << push_time << "," << poll_time << "\n";
        std::cout << "Measured " << n << " operations\n";
    }

    queue_del(q);
    out_file.close();
}

int main() {
    measure();
    return 0;
}