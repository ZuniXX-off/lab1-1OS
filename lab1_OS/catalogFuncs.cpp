#include "catalogFuncs.h"
#include <iostream>
#include <windows.h>
#include <conio.h>


void NewCatalog() {
	TCHAR catalog_name[MAX_PATH];

	std::cout << "Введите имя каталога (пример: c:\\folder): ";
	std::cin.getline(catalog_name, MAX_PATH);

	if (CreateDirectory(catalog_name, nullptr)) {
		std::cout << "Каталог создан" << std::endl;
	}
	else {
		std::cout << "Ошибка при создании каталога" << std::endl;
	}
}

void DelCatalog() {
	TCHAR catalog_name[MAX_PATH];

	std::cout << "Введите имя каталога (пример: c:\\folder): ";
	std::cin.getline(catalog_name, MAX_PATH);

	if (RemoveDirectory(catalog_name)) {
		std::cout << "Каталог удален" << std::endl;
	}
	else {
		std::cout << "Ошибка при удалении каталога" << std::endl;
	}
}

void PrintCatalogMenu() {
	std::cout << "1. Создать каталог" << std::endl << "2. Удалить каталог" << std::endl << "0. Назад" << std::endl;
}

void CatalogMenu() {
	char menu;
	
	do {
		system("cls");
		PrintCatalogMenu();

		menu = _getch();
		switch (menu)
		{
		case '1':
			NewCatalog();
			system("pause");
			break;
		case '2':
			DelCatalog();
			system("pause");
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