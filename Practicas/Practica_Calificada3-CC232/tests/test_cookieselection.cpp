#include <iostream>
#include <cassert>
#include "CookieMedian.h"

void test1_basic() {
    CookieMedian cm;
    cm.addCookie(1); cm.addCookie(2); cm.addCookie(3);
    assert(cm.getMedianAndRemove() == 2);
    assert(cm.getMedianAndRemove() == 3);
    assert(cm.getMedianAndRemove() == 1);
    std::cout << "Test 1 (Basico impar) exitoso.\n";
}

void test2_even_number() {
    CookieMedian cm;
    cm.addCookie(1); cm.addCookie(2); cm.addCookie(3); cm.addCookie(4);
    assert(cm.getMedianAndRemove() == 3);
    assert(cm.getMedianAndRemove() == 2);
    std::cout << "Test 2 (Paridad Par) exitoso.\n";
}

void test3_duplicates() {
    CookieMedian cm;
    cm.addCookie(5); cm.addCookie(5); cm.addCookie(5);
    assert(cm.getMedianAndRemove() == 5);
    assert(cm.getMedianAndRemove() == 5);
    std::cout << "Test 3 (Duplicados) exitoso.\n";
}

void test4_empty_exception() {
    CookieMedian cm;
    bool caught = false;
    try { cm.getMedianAndRemove(); } catch (const std::out_of_range&) { caught = true; }
    assert(caught);
    std::cout << "Test 4 (Excepcion estructura vacia) exitoso.\n";
}

int main() {
    test1_basic();
    test2_even_number();
    test3_duplicates();
    test4_empty_exception();
    std::cout << "Todos los asserts (pruebas) pasaron correctamente.\n";
    return 0;
}