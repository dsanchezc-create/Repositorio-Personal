#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <vector>
#include <stdexcept>
#include <iostream>

template<typename T, typename Compare>
class BinaryHeap {
private:
    std::vector<T> data;
    Compare comp;

    void percolateUp(int hole) {
        T tmp = data[hole];
        // Mientras hole > 0 y el elemento tmp cumpla la condición con su padre
        for (; hole > 0 && comp(tmp, data[(hole - 1) / 2]); hole = (hole - 1) / 2) {
            data[hole] = data[(hole - 1) / 2];
        }
        data[hole] = tmp;
    }

    void percolateDown(int hole) {
        int child;
        T tmp = data[hole];
        for (; hole * 2 + 1 < (int)data.size(); hole = child) {
            child = hole * 2 + 1;
            // Elegir el hijo que más cumpla la condición del comparador
            if (child != (int)data.size() - 1 && comp(data[child + 1], data[child])) {
                child++;
            }
            if (comp(data[child], tmp)) {
                data[hole] = data[child];
            } else {
                break;
            }
        }
        data[hole] = tmp;
    }

public:
    BinaryHeap(Compare c = Compare()) : comp(c) {}

    bool empty() const { return data.empty(); }
    int size() const { return data.size(); }

    const T& top() const {
        if (empty()) throw std::out_of_range("Heap vacío");
        return data.front();
    }

    void push(const T& val) {
        data.push_back(val);
        percolateUp(data.size() - 1);
    }

    void pop() {
        if (empty()) throw std::out_of_range("Heap vacío");
        data[0] = data.back();
        data.pop_back();
        if (!empty()) {
            percolateDown(0);
        }
    }

    // Reto obligatorio: Mostrar el estado lógico del arreglo
    void printHeap() const {
        for(int i = 0; i < (int)data.size(); ++i) {
            std::cout << data[i] << (i + 1 == (int)data.size() ? "" : " ");
        }
        std::cout << "\n";
    }
};

#endif // BINARYHEAP_H