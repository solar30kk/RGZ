#include <iostream>
#include <stdint.h>
#include <limits>
#include <string>
#include "menuAtbash.h"

#ifdef _WIN32
    #define NOMINMAX
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

typedef void (*Atbash_FileFunc)(const char*, const char*);
typedef void (*Atbash_TextFunc)(const char*, char*);

void menuAtbash(){

    int input = -1;
    std::string inFile, outFile;

    while (input != MenuAtbash::ATBASH_EXIT){

    std::cout << std::endl << "Шифр Атбаш " << std::endl;
    std::cout << "1. Шифрование файла "<< std::endl;
    std::cout << "2. Расшифрование файла "<< std::endl;
    std::cout << "3. Шифрование текста "<< std::endl;
    std::cout << "4. Расшифрование текста"<< std::endl;
    std::cout << "0. Выйти в меню" << std::endl;
    std::cout << ">> ";
   

    std::cin >> input;

    switch (input){

        case MenuAtbash::EncryptionFile: {
            std::cout << "Введите имя исходного файла: ";
            std::cin >> inFile;
            std::cout << "Введите имя для зашифрованного файла: ";
            std::cin >> outFile;

            #ifdef _WIN32
                HINSTANCE hLib = LoadLibraryA("Atbash.dll"); 
            #else
                void* hLib = dlopen("./libAtbash.so", RTLD_LAZY);
            #endif

            if (!hLib) {
                std::cout << "Ошибка! Не удалось найти или загрузить библиотеку Atbash." << std::endl;
                break;
            }

            #ifdef _WIN32
                Atbash_FileFunc encrypt = (Atbash_FileFunc)GetProcAddress(hLib, "encryptFile");
            #else
                Atbash_FileFunc encrypt = (Atbash_FileFunc)dlsym(hLib, "encryptFile");
            #endif

            if (encrypt) {
                encrypt(inFile.c_str(), outFile.c_str()); 
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

        case MenuAtbash::DecryptionFile: {
            std::cout << "Введите имя зашифрованного файла: ";
            std::cin >> inFile;
            std::cout << "Введите имя для расшифрованного файла: ";
            std::cin >> outFile;
                
            #ifdef _WIN32
                HINSTANCE hLib = LoadLibraryA("Atbash.dll"); 
            #else
                void* hLib = dlopen("./libAtbash.so", RTLD_LAZY);
            #endif

            if (!hLib) {
                std::cout << "Ошибка! Не удалось найти или загрузить библиотеку Atbash." << std::endl;
                break;
            }

            #ifdef _WIN32
                Atbash_FileFunc decrypt = (Atbash_FileFunc)GetProcAddress(hLib, "decryptFile");
            #else
                Atbash_FileFunc decrypt = (Atbash_FileFunc)dlsym(hLib, "decryptFile");
            #endif

            if (decrypt) {
                decrypt(inFile.c_str(), outFile.c_str());
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

        case MenuAtbash::EncryptionText: {
            std::cout << "Введите текст для шифрования: ";
            std::string inputText;
            std::cin.ignore();
            std::getline(std::cin, inputText);

            char outputText[4096] = {0};

            #ifdef _WIN32
                HINSTANCE hLib = LoadLibraryA("Atbash.dll"); 
            #else
                void* hLib = dlopen("./libAtbash.so", RTLD_LAZY);
            #endif

            if (!hLib) {
                std::cout << "Ошибка! Не удалось найти или загрузить библиотеку Atbash." << std::endl;
                break;
            }

            #ifdef _WIN32
                Atbash_TextFunc encryptText = (Atbash_TextFunc)GetProcAddress(hLib, "encryptText");
            #else
                Atbash_TextFunc encryptText = (Atbash_TextFunc)dlsym(hLib, "encryptText");
            #endif

            if (encryptText) {
                encryptText(inputText.c_str(), outputText);
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
        
        case MenuAtbash::DecryptionText: {
            std::cout << "Введите зашифрованный текст (hex): ";
            std::string inputText;
            std::cin.ignore();
            std::getline(std::cin, inputText);

            char outputText[4096] = {0};

            #ifdef _WIN32
                HINSTANCE hLib = LoadLibraryA("Atbash.dll"); 
            #else
                void* hLib = dlopen("./libAtbash.so", RTLD_LAZY);
            #endif

            if (!hLib) {
                std::cout << "Ошибка! Не удалось найти или загрузить библиотеку Atbash." << std::endl;
                break;
            }

            #ifdef _WIN32
                Atbash_TextFunc decryptText = (Atbash_TextFunc)GetProcAddress(hLib, "decryptText");
            #else
                Atbash_TextFunc decryptText = (Atbash_TextFunc)dlsym(hLib, "decryptText");
            #endif

            if (decryptText) {
                decryptText(inputText.c_str(), outputText);
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

        case MenuAtbash::ATBASH_EXIT:
            break;
            
        default:
            std::cout << "Ошибка! Такого действия нет" << std::endl;
        
    }
}
}