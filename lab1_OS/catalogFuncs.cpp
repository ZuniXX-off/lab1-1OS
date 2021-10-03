#include "catalogFuncs.h"
#include <iostream>
#include <windows.h>
#include <conio.h>


void NewCatalog() {
	TCHAR catalog_name[MAX_PATH];

	std::cout << "������� ��� �������� (������: c:\\folder): ";
	std::cin.getline(catalog_name, MAX_PATH);

	if (CreateDirectory(catalog_name, nullptr)) {
		std::cout << "������� ������" << std::endl;
	}
	else {
		std::cout << "������ ��� �������� ��������" << std::endl;
	}
}

void DelCatalog() {
	TCHAR catalog_name[MAX_PATH];

	std::cout << "������� ��� �������� (������: c:\\folder): ";
	std::cin.getline(catalog_name, MAX_PATH);

	if (RemoveDirectory(catalog_name)) {
		std::cout << "������� ������" << std::endl;
	}
	else {
		std::cout << "������ ��� �������� ��������" << std::endl;
	}
}

void PrintCatalogMenu() {
	std::cout << "1. ������� �������" << std::endl << "2. ������� �������" << std::endl << "0. �����" << std::endl;
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
			std::cout << "������ �������������� ����� ����, ���������� �����" << std::endl;
			system("pause");
			break;
		}
	} while (menu != '0');
}