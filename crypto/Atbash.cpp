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

    EXPORT void encryptFile(const char* inputPath, const char* outputPath) { 
        std::ifstream inFile(inputPath, std::ios::binary);
        std::ofstream outFile(outputPath, std::ios::binary);

        if (!inFile.is_open() || !outFile.is_open()) {
            std::cout << "Ошибка! Не удалось открыть файлы для обработки." << std::endl;
            return;
        }

        char ch;
        while (inFile.get(ch)) {
            unsigned char byte = static_cast<unsigned char>(ch);
            unsigned char transformed = static_cast<unsigned char>(255 - byte);
            outFile.put(static_cast<char>(transformed));
        }

        std::cout << "Успешно! Результат сохранен в файл: " << outputPath << std::endl;
        
        inFile.close();
        outFile.close();
    }

    EXPORT void decryptFile(const char* inputPath, const char* outputPath) {
        encryptFile(inputPath, outputPath);
    }

    EXPORT void encryptText(const char* inputText, char* outputText) {
        if (!inputText || !outputText) return;

        std::stringstream hexStream;
        
        while (*inputText) {
            unsigned char byte = static_cast<unsigned char>(*inputText);
            unsigned char transformed = static_cast<unsigned char>(255 - byte);
            
            hexStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(transformed);
            inputText++;
        }

        std::string res = hexStream.str();
        for (size_t i = 0; i < res.length(); ++i) {
            outputText[i] = res[i];
        }
        outputText[res.length()] = '\0';
    }

    EXPORT void decryptText(const char* inputText, char* outputText) {
        if (!inputText || !outputText) return;

        size_t len = std::strlen(inputText);
        size_t outIdx = 0;

    
        for (size_t i = 0; i + 1 < len; i += 2) {
            char hexByte[3] = { inputText[i], inputText[i+1], '\0' };
        
        
            unsigned int byteVal = 0;
            std::stringstream ss;
            ss << std::hex << hexByte;
            ss >> byteVal;

        
            unsigned char transformed = static_cast<unsigned char>(255 - byteVal);
        
        
            outputText[outIdx++] = static_cast<char>(transformed);
        }
        outputText[outIdx] = '\0';
    }

}