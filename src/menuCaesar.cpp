#include <iostream>
#include <stdint.h>
#include <limits>
#include <string>
#include "menuCaesar.h"

#ifdef _WIN32
    #define NOMINMAX
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

typedef void (*Caesar_FileFunc)(const char*, const char*, int);
typedef void (*Caesar_TextFunc)(const char*, char*, int);

void menuCaesar(){

    int input = -1;
    std::string inFile, outFile;
    int key;

    while (input != MenuCaesar::CAESAR_EXIT){

    std::cout << std::endl << "Шифр Цезаря " << std::endl;
    std::cout << "1. Шифрование файла "<< std::endl;
    std::cout << "2. Расшифрование файла "<< std::endl;
    std::cout << "3. Шифрование текста "<< std::endl;
    std::cout << "4. Расшифрование текста"<< std::endl;
    std::cout << "0. Выйти в меню" << std::endl;
    std::cout << ">> ";
   

    std::cin >> input;

    switch (input){

        case MenuCaesar::EncryptionFile: {
            std::cout << "Введите имя исходного файла: ";
            std::cin >> inFile;
            std::cout << "Введите имя для зашифрованного файла: ";
            std::cin >> outFile;
            std::cout << "Введите ключ для шифрования (число): ";
            
            if (!(std::cin >> key)) {
                std::cout << std::endl << "Ошибка! Введите числовое значение" << std::endl;
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                input = -1;
                continue;
            }

            #ifdef _WIN32
                HINSTANCE hLib = LoadLibraryA("Caesar.dll"); 
            #else
                void* hLib = dlopen("./libCaesar.so", RTLD_LAZY);
            #endif

            if (!hLib) {
                std::cout << "Ошибка! Не удалось найти или загрузить библиотеку Caesar." << std::endl;
                break;
            }

            #ifdef _WIN32
                Caesar_FileFunc encrypt = (Caesar_FileFunc)GetProcAddress(hLib, "encryptFile");
            #else
                Caesar_FileFunc encrypt = (Caesar_FileFunc)dlsym(hLib, "encryptFile");
            #endif

            if (encrypt) {
                encrypt(inFile.c_str(), outFile.c_str(), key); 
            } else {
                std::cout << "Ошибка! Функция encryptFile не найдена в библиотеке." << std::endl;
            }

            #ifdef _WIN32
                FreeLibrary(hLib);
            #else
                dlclose(hLib);
            #endif

            break;
        }

        case MenuCaesar::DecryptionFile: {
            std::cout << "Введите имя зашифрованного файла: ";
            std::cin >> inFile;
            std::cout << "Введите имя для расшифрованного файла: ";
            std::cin >> outFile;
            std::cout << "Введите ключ для расшифрования (число): ";

            if (!(std::cin >> key)) {
                std::cout << std::endl << "Ошибка! Введите числовое значение" << std::endl;
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                input = -1;
                continue;
            }
                
            #ifdef _WIN32
                HINSTANCE hLib = LoadLibraryA("Caesar.dll"); 
            #else
                void* hLib = dlopen("./libCaesar.so", RTLD_LAZY);
            #endif

            if (!hLib) {
                std::cout << "Ошибка! Не удалось найти или загрузить библиотеку Caesar." << std::endl;
                break;
            }

            #ifdef _WIN32
                Caesar_FileFunc decrypt = (Caesar_FileFunc)GetProcAddress(hLib, "decryptFile");
            #else
                Caesar_FileFunc decrypt = (Caesar_FileFunc)dlsym(hLib, "decryptFile");
            #endif

            if (decrypt) {
                decrypt(inFile.c_str(), outFile.c_str(), key);
            } else {
                std::cout << "Ошибка! Функция decryptFile не найдена в библиотеке." << std::endl;
            }
        
            #ifdef _WIN32
                FreeLibrary(hLib);
            #else
                dlclose(hLib);
            #endif
            
            break;
        }

        case MenuCaesar::EncryptionText: {
            std::cout << "Введите текст для шифрования: ";
            std::string inputText;
            std::cin.ignore();
            std::getline(std::cin, inputText);
            std::cout << "Введите ключ шифрования (число): ";

            if (!(std::cin >> key)) {
                std::cout << std::endl << "Ошибка! Введите числовое значение" << std::endl;
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                input = -1;
                continue;
            }

            char outputText[4096] = {0}; 

            #ifdef _WIN32
                HINSTANCE hLib = LoadLibraryA("Caesar.dll"); 
            #else
                void* hLib = dlopen("./libCaesar.so", RTLD_LAZY);
            #endif

            if (!hLib) {
                std::cout << "Ошибка! Не удалось найти или загрузить библиотеку Caesar." << std::endl;
                break;
            }

            #ifdef _WIN32
                Caesar_TextFunc encryptText = (Caesar_TextFunc)GetProcAddress(hLib, "encryptText");
            #else
                Caesar_TextFunc encryptText = (Caesar_TextFunc)dlsym(hLib, "encryptText");
            #endif

            if (encryptText) {
                encryptText(inputText.c_str(), outputText, key);
                std::cout << "Зашифрованный текст (в hex): " << outputText << std::endl;
            } else {
                std::cout << "Ошибка! Функция encryptText не найдена в библиотеке." << std::endl;
            }

            #ifdef _WIN32
                FreeLibrary(hLib);
            #else
                dlclose(hLib);
            #endif
                
            break;
        }
        
        case MenuCaesar::DecryptionText: {
            std::cout << "Введите зашифрованный текст (hex): ";
            std::string inputText;
            std::cin.ignore();
            std::getline(std::cin, inputText);
            std::cout << "Введите ключ для расшифрования (число): ";

            if (!(std::cin >> key)) {
                std::cout << std::endl << "Ошибка! Введите числовое значение" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                input = -1;
                continue;
            }

            char outputText[4096] = {0};

            #ifdef _WIN32
                HINSTANCE hLib = LoadLibraryA("Caesar.dll"); 
            #else
                void* hLib = dlopen("./libCaesar.so", RTLD_LAZY);
            #endif

            if (!hLib) {
                std::cout << "Ошибка! Не удалось найти или загрузить библиотеку Caesar." << std::endl;
                break;
            }

            #ifdef _WIN32
                Caesar_TextFunc decryptText = (Caesar_TextFunc)GetProcAddress(hLib, "decryptText");
            #else
                Caesar_TextFunc decryptText = (Caesar_TextFunc)dlsym(hLib, "decryptText");
            #endif

            if (decryptText) {
                decryptText(inputText.c_str(), outputText, key);
                std::cout << "Расшифрованный текст: " << outputText << std::endl;
            } else {
                std::cout << "Ошибка! Функция decryptText не найдена в библиотеке." << std::endl;
            }

            #ifdef _WIN32
                FreeLibrary(hLib);
            #else
                dlclose(hLib);
            #endif

            break;
        }

        case MenuCaesar::CAESAR_EXIT:
            break;
            
        default:
            std::cout << "Ошибка! Такого действия нет" << std::endl;
        
    }
}
}