#ifndef LUTGENERATORS_H
#define LUTGENERATORS_H
#include <vector>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <iterator>

namespace lutGenerators {
    std::vector<std::vector<uint32_t>> generateMXOverCos(uint16_t m, uint8_t maxX, uint8_t maxTheta);
    std::vector<std::vector<uint32_t>> generateMXOverSin(uint16_t m, uint8_t maxX, uint8_t maxTheta);
    std::vector<uint32_t> generateMCos(uint16_t m, uint8_t maxTheta);
    std::vector<uint32_t> generateMSin(uint16_t m, uint8_t maxTheta);

    template <class T>
    void print2DVect(const std::vector<std::vector<T>> &v) {
        for (const auto &row: v) {
            std::copy(begin(row), end(row), std::ostream_iterator<int>(std::cout, " "));
            std::cout << std::endl;
        }
    }
    template <class T>
    void print1DVect(const std::vector<T> &v) {
        std::copy(begin(v), end(v), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }
}


#endif
