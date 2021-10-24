#include <iostream>
#include <windows.h>
#include <conio.h>
#include "fileFuncs.h"

void NewFile() {
	TCHAR catalog_name[MAX_PATH];

	std::cout << "Введите имя файла (пример: c:\\folder\\text.txt): ";
	std::cin.getline(catalog_name, MAX_PATH);

	if (CreateFile(catalog_name, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr) != INVALID_HANDLE_VALUE) {
		std::cout << "Файл создан успешно" << std::endl;
	}
	else {
		std::cout << "Ошибка при создании файла, код: " << GetLastError() << std::endl;
	}
}

void CCopyFile() {
	TCHAR first_catalog_name[MAX_PATH];
	TCHAR second_catalog_name[MAX_PATH];

	std::cout << "Введите имя файла - источника(пример: c:\\folder\\text.txt) : ";
	std::cin.getline(first_catalog_name, MAX_PATH);
	std::cout << "Введите имя файла-копии: ";
	std::cin.getline(second_catalog_name, MAX_PATH);

	if (CopyFile(first_catalog_name, second_catalog_name, false)) {
		std::cout << "Файл успешно скопирован" << std::endl;
	}
	else {
		std::cout << "Ошибка при копировании файла, код: " << GetLastError() << std::endl;
	}
}

void CVopyFile() {
	TCHAR first_catalog_name[MAX_PATH];
	TCHAR second_catalog_name[MAX_PATH];

	std::cout << "Введите имя файла (пример: c:\\folder\\text.txt) : ";
	std::cin.getline(first_catalog_name, MAX_PATH);
	std::cout << "Введите каталог для перемещения: ";
	std::cin.getline(second_catalog_name, MAX_PATH);

	if (MoveFile(first_catalog_name, second_catalog_name)) {
		std::cout << "Файл успешно перемещен" << std::endl;
	}
	else {
		std::cout << "Ошибка при перемещении файла, код: " << GetLastError() << std::endl;
	}
}

int ChoiceMenu() {
	char choice;
	do {
		std::cout << "Такой файл уже существует, хотите его заменить?" << std::endl << "1. Да" << std::endl << "0. Нет" << std::endl;
		choice = _getch();
		if (choice != '1' && choice != '0') {
			std::cout << "Выбран несуществующий пункт меню, попробуйте снова" << std::endl;
			system("pause");
		}
	} while (choice != '1' && choice != '0');
	return choice == '1' ? 1 : 0;
}

void CVopyFileEx() {
	TCHAR first_catalog_name[MAX_PATH];
	TCHAR second_catalog_name[MAX_PATH];
	int choice;

	std::cout << "Введите имя файла (пример: c:\\folder\\text.txt) : ";
	std::cin.getline(first_catalog_name, MAX_PATH);
	std::cout << "Введите каталог для перемещения: ";
	std::cin.getline(second_catalog_name, MAX_PATH);

	if (MoveFileEx(first_catalog_name, second_catalog_name, NULL)) {
		std::cout << "Файл перемещен успешно" << std::endl;
	}
	else if (GetLastError() == 183) {
		if (ChoiceMenu()) {
			if (MoveFileEx(first_catalog_name, second_catalog_name, MOVEFILE_REPLACE_EXISTING)) {
				std::cout << "Файл успешно заменен" << std::endl;
			}
			else {
				std::cout << "Ошибка при замене файла, код: " << GetLastError() << std::endl;
			}
		}
	}
	else {
		std::cout << "Ошибка при перемещении файла, код: " << GetLastError() << std::endl;
	}
}

void PrintFileMenu() {
	std::cout << "1. Копировать файл" << std::endl << "2. Переместить файл" << std::endl << "3. Переместить файл (с проверкой)"
		<< std::endl << "0. Назад" << std::endl;
}

void FileMenu() {
	char menu;

	do {
		system("cls");
		PrintFileMenu();

		menu = _getch();
		switch (menu)
		{
		case '1':
			CCopyFile();
			system("pause");
			break;
		case '2':
			CVopyFile();
			system("pause");
			break;
		case '3':
			CVopyFileEx();
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