#include <iostream>
#include <vector>
#include <string>
#include "trithemius.h"

int main() {
    std::string password;
    std::cout << "Введите пароль: ";
    std::cin >> password;

    if (password != "admin") {
        std::cout << "Неверный пароль!" << std::endl;
        return 0;
    }

    int input = -1;
    while (input != 0) {
        std::cout << "\n\t Меню \n";
        std::cout << "1. Шифрование текста (Тритемиус)\n";
        std::cout << "2. Дешифрование текста (Тритемиус)\n";
        std::cout << "0. Выход\n>> ";
        std::cin >> input;

        if (input == 1 || input == 2) {
            int a, b;
            std::cout << "Введите коэффициенты ключа A и B: ";
            std::cin >> a >> b;

            std::cin.ignore();
            if (input == 1) {
                std::cout << "Введите текст для шифрования: ";
                std::string text;
                std::getline(std::cin, text);

                std::vector<uint8_t> data(text.begin(), text.end());
                auto encrypted = encryptTrithemius(data, a, b);

                std::cout << "Зашифрованный текст (в HEX): ";
                for (uint8_t byte : encrypted) {
                    std::cout << std::hex << (int)byte << " ";
                }
                std::cout << std::dec << std::endl;
            } else {
                std::cout << "Введите количество байт для расшифрования: ";
                int size;
                std::cin >> size;
                std::vector<uint8_t> data(size);
                std::cout << "Введите байты (числа через пробел): ";
                for (int i = 0; i < size; ++i) {
                    int byteVal;
                    std::cin >> byteVal;
                    data[i] = static_cast<uint8_t>(byteVal);
                }

                auto decrypted = decryptTrithemius(data, a, b);
                std::string resStr(decrypted.begin(), decrypted.end());
                std::cout << "Расшифрованный текст: " << resStr << std::endl;
            }
        }
    }
    return 0;
}
