#include <iostream>
#include <windows.h>
#include <conio.h>
#include "diskFuncs.h"
#include "catalogFuncs.h"
#include "fileFuncs.h"
#include "attributeFuncs.h"

void PrintMainMenu() {
    std::cout << "1. Вывод списка дисков" << std::endl << "2. Вывод информации о диске" << std::endl 
        << "3. Создание и удаление каталогов" << std::endl << "4. Создание файла" << std::endl << "5. Копирование и перемещение файла"
        << std::endl << "6. Работа с атрибутами файла" << std::endl << "0. Выход" << std::endl;
}

int main()
{
    char menu;
    system("chcp 1251");
    do {
        system("cls");
        PrintMainMenu();

        menu = _getch();
        switch (menu)
        {
        case '1':
            ListOfAvailableDisks();
            system("pause");
            break;
        case '2':
            GetInfoAboutDisk();
            system("pause");
            break;
        case '3':
            CatalogMenu();
            break;
        case '4':
            NewFile();
            system("pause");
            break;
        case '5':
            FileMenu();
            break;
        case '6':
            AttributeMenu();
            break;
        case '0':
            break;
        default:
            std::cout << "Выбран несуществующий пункт меню, попробуйте снова" << std::endl;
            system("pause");
            break;
        }
    } while (menu != '0');

}

