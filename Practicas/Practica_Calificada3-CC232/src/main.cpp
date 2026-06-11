#include <iostream>
#include <string>
#include "CookieMedian.h"

int main() {
    // Optimización vital para Kattis
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    CookieMedian cm;
    std::string line;

    while (std::cin >> line) {
        if (line == "#") {
            try {
                std::cout << cm.getMedianAndRemove() << "\n";
            } catch(...) {
                // Ignore silent failures if input has invalid #
            }
        } else {
            cm.addCookie(std::stoi(line));
        }
    }

    return 0;
}