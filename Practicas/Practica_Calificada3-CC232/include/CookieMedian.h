#ifndef COOKIEMEDIAN_H
#define COOKIEMEDIAN_H

#include "BinaryHeap.h"

// Functores que dictan la forma del Heap
struct LessComp {
    bool operator()(int a, int b) const { return a < b; } // Crea un Min-Heap
};

struct GreaterComp {
    bool operator()(int a, int b) const { return a > b; } // Crea un Max-Heap
};

class CookieMedian {
private:
    BinaryHeap<int, LessComp> min_heap;    // Mitad superior (el menor de ellos es la mediana)
    BinaryHeap<int, GreaterComp> max_heap; // Mitad inferior (el mayor es el tope)

    // Invariante: min_heap.size() == max_heap.size()  Ó  min_heap.size() == max_heap.size() + 1
    void balance() {
        if (max_heap.size() > min_heap.size()) {
            min_heap.push(max_heap.top());
            max_heap.pop();
        } else if (min_heap.size() > max_heap.size() + 1) {
            max_heap.push(min_heap.top());
            min_heap.pop();
        }
    }

public:
    void addCookie(int diameter) {
        if (min_heap.empty() || diameter >= min_heap.top()) {
            min_heap.push(diameter);
        } else {
            max_heap.push(diameter);
        }
        balance();
    }

    int getMedianAndRemove() {
        if (min_heap.empty()) {
            throw std::out_of_range("No hay galletas en el holding area");
        }
        int median = min_heap.top();
        min_heap.pop();
        balance(); // Restaurar invariante
        return median;
    }

    // Funcionalidad extra para el Reto en video
    void debugHeaps() const {
        std::cout << "Max-Heap (Mitad Inferior): [ ";
        max_heap.printHeap();
        std::cout << "Min-Heap (Mitad Superior): [ ";
        min_heap.printHeap();
    }
};

#endif // COOKIEMEDIAN_H