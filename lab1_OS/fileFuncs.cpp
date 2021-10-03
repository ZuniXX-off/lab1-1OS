#include <iostream>
#include <windows.h>
#include <conio.h>
#include "fileFuncs.h"

void NewFile() {
	TCHAR catalog_name[MAX_PATH];

	std::cout << "������� ��� ����� (������: c:\\folder\\text.txt): ";
	std::cin.getline(catalog_name, MAX_PATH);

	if (CreateFile(catalog_name, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr) != INVALID_HANDLE_VALUE) {
		std::cout << "���� ������ �������" << std::endl;
	}
	else {
		std::cout << "������ ��� �������� �����, ���: " << GetLastError() << std::endl;
	}
}

void CCopyFile() {
	TCHAR first_catalog_name[MAX_PATH];
	TCHAR second_catalog_name[MAX_PATH];

	std::cout << "������� ��� ����� - ���������(������: c:\\folder\\text.txt) : ";
	std::cin.getline(first_catalog_name, MAX_PATH);
	std::cout << "������� ��� �����-�����: ";
	std::cin.getline(second_catalog_name, MAX_PATH);

	if (CopyFile(first_catalog_name, second_catalog_name, false)) {
		std::cout << "���� ������� ����������" << std::endl;
	}
	else {
		std::cout << "������ ��� ����������� �����, ���: " << GetLastError() << std::endl;
	}
}

void CVopyFile() {
	TCHAR first_catalog_name[MAX_PATH];
	TCHAR second_catalog_name[MAX_PATH];

	std::cout << "������� ��� ����� (������: c:\\folder\\text.txt) : ";
	std::cin.getline(first_catalog_name, MAX_PATH);
	std::cout << "������� ������� ��� �����������: ";
	std::cin.getline(second_catalog_name, MAX_PATH);

	if (MoveFile(first_catalog_name, second_catalog_name)) {
		std::cout << "���� ������� ���������" << std::endl;
	}
	else {
		std::cout << "������ ��� ����������� �����, ���: " << GetLastError() << std::endl;
	}
}

int ChoiceMenu() {
	char choice;
	do {
		std::cout << "����� ���� ��� ����������, ������ ��� ��������?" << std::endl << "1. ��" << std::endl << "0. ���" << std::endl;
		choice = _getch();
		if (choice != '1' && choice != '0') {
			std::cout << "������ �������������� ����� ����, ���������� �����" << std::endl;
			system("pause");
		}
	} while (choice != '1' && choice != '0');
	return choice == '1' ? 1 : 0;
}

void CVopyFileEx() {
	TCHAR first_catalog_name[MAX_PATH];
	TCHAR second_catalog_name[MAX_PATH];
	int choice;

	std::cout << "������� ��� ����� (������: c:\\folder\\text.txt) : ";
	std::cin.getline(first_catalog_name, MAX_PATH);
	std::cout << "������� ������� ��� �����������: ";
	std::cin.getline(second_catalog_name, MAX_PATH);

	if (MoveFileEx(first_catalog_name, second_catalog_name, NULL)) {
		std::cout << "���� ��������� �������" << std::endl;
	}
	else if (GetLastError() == 183) {
		if (ChoiceMenu()) {
			if (MoveFileEx(first_catalog_name, second_catalog_name, MOVEFILE_REPLACE_EXISTING)) {
				std::cout << "���� ������� �������" << std::endl;
			}
			else {
				std::cout << "������ ��� ������ �����, ���: " << GetLastError() << std::endl;
			}
		}
	}
	else {
		std::cout << "������ ��� ����������� �����, ���: " << GetLastError() << std::endl;
	}
}

void PrintFileMenu() {
	std::cout << "1. ���������� ����" << std::endl << "2. ����������� ����" << std::endl << "3. ����������� ���� (� ���������)"
		<< std::endl << "0. �����" << std::endl;
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
			std::cout << "������ �������������� ����� ����, ���������� �����" << std::endl;
			system("pause");
			break;
		}
	} while (menu != '0');
}