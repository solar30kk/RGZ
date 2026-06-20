#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstring>

#ifdef _WIN32
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT
#endif


extern "C" {

    EXPORT void encryptFile(const char* inputPath, const char* outputPath, int key) { 
        std::ifstream inFile(inputPath, std::ios::binary);
        std::ofstream outFile(outputPath, std::ios::binary);

        if (!inFile.is_open() || !outFile.is_open()) {
            std::cout << "Ошибка! Не удалось открыть файлы для обработки." << std::endl;
            return;
        }

        char ch;
        while (inFile.get(ch)) {
            unsigned char byte = static_cast<unsigned char>(ch);
            unsigned char encrypted = static_cast<unsigned char>((byte + key) % 256);
            outFile.put(static_cast<char>(encrypted));
        }

        std::cout << "Успешно! Результат сохранен в файл: " << outputPath << std::endl;
        
        inFile.close();
        outFile.close();
    }

    EXPORT void decryptFile(const char* inputPath, const char* outputPath, int key) {
        std::ifstream inFile(inputPath, std::ios::binary);
        std::ofstream outFile(outputPath, std::ios::binary);

        if (!inFile.is_open() || !outFile.is_open()) {
            std::cout << "Ошибка! Не удалось открыть файлы для обработки." << std::endl;
            return;
        }

        char ch;
        while (inFile.get(ch)) {
            unsigned char byte = static_cast<unsigned char>(ch);
            unsigned char decrypted = static_cast<unsigned char>((byte - key + 256) % 256);
            outFile.put(static_cast<char>(decrypted));
        }

        std::cout << "Успешно! Результат сохранен в файл: " << outputPath << std::endl;
        
        inFile.close();
        outFile.close();
    }

    EXPORT void encryptText(const char* inputText, char* outputText, int key) {
        if (!inputText || !outputText) return;

        std::stringstream hexStream;
        
        while (*inputText) {
            unsigned char byte = static_cast<unsigned char>(*inputText);
            unsigned char encrypted = static_cast<unsigned char>((byte + key) % 256);
            
            hexStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(encrypted);
            inputText++;
        }

        std::string res = hexStream.str();
        for (size_t i = 0; i < res.length(); ++i) {
            outputText[i] = res[i];
        }
        outputText[res.length()] = '\0';
    }

    EXPORT void decryptText(const char* inputText, char* outputText, int key) {
        if (!inputText || !outputText) return;

        std::string outStr;
        size_t len = strlen(inputText);
        
        for (size_t i = 0; i < len; i += 2) {
            std::string byteString(inputText + i, 2);
            unsigned char byte = static_cast<unsigned char>(strtol(byteString.c_str(), NULL, 16));
            unsigned char decrypted = static_cast<unsigned char>((byte - key + 256) % 256);
            outStr += static_cast<char>(decrypted);
        }

        for (size_t i = 0; i < outStr.length(); ++i) {
            outputText[i] = outStr[i];
        }
        outputText[outStr.length()] = '\0';
    }

}