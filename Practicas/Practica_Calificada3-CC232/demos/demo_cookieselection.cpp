#include <iostream>
#include "CookieMedian.h"

int main() {
    std::cout << "=== Reto Obligatorio: Trazado de Heaps - Cookie Selection ===\n\n";
    CookieMedian cm;
    
    std::cout << "--> Insertando: 10, 20, 5, 15\n";
    cm.addCookie(10);
    cm.addCookie(20);
    cm.addCookie(5);
    cm.addCookie(15);
    cm.debugHeaps();

    std::cout << "\n--> Extrayendo Mediana (" << cm.getMedianAndRemove() << ")...\n";
    cm.debugHeaps();

    std::cout << "\n--> Extrayendo Mediana (" << cm.getMedianAndRemove() << ")...\n";
    cm.debugHeaps();

    std::cout << "\n--> Insertando: 2, 25\n";
    cm.addCookie(2);
    cm.addCookie(25);
    cm.debugHeaps();

    std::cout << "\n--> Extrayendo Mediana final (" << cm.getMedianAndRemove() << ")...\n";
    cm.debugHeaps();

    return 0;
}