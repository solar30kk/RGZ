#include "menuCaesar.h"
#include "menuAtbash.h"
#include "menuTrithemius.h"
#include <iostream>
#include <string>
#include <limits>
#include "menu.h"

#ifdef _WIN32
    #define NOMINMAX
    #include <windows.h>
#endif



bool login(std::string& password){ 

    if ( password == "admin"){
        std::cout << "Авторизация успешна!" << std::endl;
        return true;
    } else {
        std::cout << "Неверный пароль!" << std::endl;
        return false;
    }
}

int main() {
    #ifdef _WIN32
        SetConsoleCP(65001);
        SetConsoleOutputCP(65001);
    #endif

    std::cout << "Введите пароль: ";
    std::string password;
    std::cin >> password;

    if (!login(password)) {
        return 0;
    }

    int input = -1;
    std::string inFile, outFile;

    while (input != Menu::EXIT) {

    std::cout << std::endl <<  "\t Меню " << std::endl;
    std::cout << "Выберите какой шифр хотите использовать: " << std::endl;
    std::cout << "1. Шифр Цезаря "<< std::endl;
    std::cout << "2. Шифр Атбаш "<< std::endl;
    std::cout << "3. Шифр Тритемиуса "<< std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << ">> ";

    if (!(std::cin >> input)) {
        std::cout << "Ошибка! Введите числовое значение" << std::endl;
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        input = -1;
        continue;
    }

    switch (input) {
        case Menu::CAESAR:
            menuCaesar();
            break;

        case Menu::ATBASH:
            menuAtbash();
            break;

        case Menu::TRITHEMIUS:
            menuTrithemius();
            break;

        case Menu::EXIT:
            break;

        default:
            std::cout << "Ошибка! Такого действия нет" << std::endl;

    }
}

    return 0;
}