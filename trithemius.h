#pragma once
#include <vector>
#include <cstdint>

std::vector<uint8_t> encryptTrithemius(const std::vector<uint8_t>& data, int a, int b);
std::vector<uint8_t> decryptTrithemius(const std::vector<uint8_t>& data, int a, int b);
