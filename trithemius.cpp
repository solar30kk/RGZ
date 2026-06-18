#include "trithemius.h"

std::vector<uint8_t> encryptTrithemius(const std::vector<uint8_t>& data, int a, int b) {
    std::vector<uint8_t> result(data.size());
    for (size_t p = 0; p < data.size(); ++p) {
        int k = a * p + b;
        result[p] = static_cast<uint8_t>((data[p] + k) % 256);
    }
    return result;
}

std::vector<uint8_t> decryptTrithemius(const std::vector<uint8_t>& data, int a, int b) {
    std::vector<uint8_t> result(data.size());
    for (size_t p = 0; p < data.size(); ++p) {
        int k = a * p + b;
        result[p] = static_cast<uint8_t>((data[p] - (k % 256) + 256) % 256);
    }
    return result;
}
