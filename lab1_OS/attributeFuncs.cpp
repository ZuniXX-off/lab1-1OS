#include <iostream>
#include <windows.h>
#include <iomanip>
#include <conio.h>
#include "attributeFuncs.h"

std::string GetDescriptionOfAttr(DWORD attr) {
	switch (attr)
	{
	case FILE_ATTRIBUTE_ARCHIVE: return "- ��������";
	case FILE_ATTRIBUTE_COMPRESSED: return "- ������";
	case FILE_ATTRIBUTE_DIRECTORY: return "- �������";
	case FILE_ATTRIBUTE_HIDDEN: return "- �������";
	case FILE_ATTRIBUTE_NORMAL: return "- �� ����� ���������";
	case FILE_ATTRIBUTE_READONLY: return "- ������ ��� ������";
	case FILE_ATTRIBUTE_SYSTEM: return "- ���������";
	}
}

void GetAttributes() {
	TCHAR catalog_name[MAX_PATH];
	DWORD attr;
	DWORD attrs[7] = { FILE_ATTRIBUTE_ARCHIVE, FILE_ATTRIBUTE_COMPRESSED, FILE_ATTRIBUTE_DIRECTORY, FILE_ATTRIBUTE_HIDDEN,
		FILE_ATTRIBUTE_NORMAL, FILE_ATTRIBUTE_READONLY, FILE_ATTRIBUTE_SYSTEM };

	std::cout << "������� ��� ����� (������: c:\\folder\\text.txt): ";
	std::cin.getline(catalog_name, MAX_PATH);

	attr = GetFileAttributes(catalog_name);

	if (attr == -1) {
		std::cout << "���� �� ������";
	} 
	else if (attr == 0) {
		std::cout << "������ ��� ��������� ���������";
	}
	else {
		std::cout << "�������� ����� (" << attr << "):" << std::endl;
		for (int i = 0; i < 7; i++) {
			if (attrs[i] & attr) std::cout << GetDescriptionOfAttr(attrs[i]) << std::endl;
		}
	}
}

int ChoiceAttr() {
	char choice;
	std::string vars = "12345";
	do {
		std::cout << "�������� ������� ����� ��: " << std::endl << "1. �����" << std::endl << "2. �������" << std::endl << "3. ��� ���������"
			<< std::endl << "4. ������ ��� ������" << std::endl << "5. ���������" << std::endl;
		choice = _getch();
		if (vars.find(choice) == -1) {
			std::cout << "������ �������������� ����� ����, ���������� �����" << std::endl;
			system("pause");
		}
	} while (vars.find(choice) == -1);
	return choice - 49;
}

void SetAttributes() {
	TCHAR catalog_name[MAX_PATH];
	DWORD attrs[5] = { FILE_ATTRIBUTE_ARCHIVE, FILE_ATTRIBUTE_HIDDEN, FILE_ATTRIBUTE_NORMAL, FILE_ATTRIBUTE_READONLY, FILE_ATTRIBUTE_SYSTEM };

	std::cout << "������� ��� ����� (������: c:\\folder\\text.txt): ";
	std::cin.getline(catalog_name, MAX_PATH);

	if (SetFileAttributes(catalog_name, attrs[ChoiceAttr()])) {
		std::cout << "������� ��� ������� �������" << std::endl;
	}
	else {
		std::cout << "������ ��� ��������� ��������, ���: " << GetLastError() << std::endl;
	}
}

void GetInfoByHandle() {
	long handle_info, file_attributes;
	BY_HANDLE_FILE_INFORMATION info_file;
	HANDLE handle_file;
	TCHAR catalog_name[MAX_PATH];
	DWORD attrs[7] = { FILE_ATTRIBUTE_ARCHIVE, FILE_ATTRIBUTE_COMPRESSED, FILE_ATTRIBUTE_DIRECTORY, FILE_ATTRIBUTE_HIDDEN,
		FILE_ATTRIBUTE_NORMAL, FILE_ATTRIBUTE_READONLY, FILE_ATTRIBUTE_SYSTEM };

	std::cout << "������� ��� ����� (������: c:\\folder\\text.txt): ";
	std::cin.getline(catalog_name, MAX_PATH);

	handle_file = CreateFileA(catalog_name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	handle_info = GetFileInformationByHandle(handle_file, &info_file);
	if (!handle_info) {
		std::cout << "��������� ������, ���: " << GetLastError() << std::endl;
	}
	else {
		file_attributes = info_file.dwFileAttributes;
		if (file_attributes == -1) {
			std::cout << "���� �� ������" << std::endl;
		}
		else if (file_attributes == 0){
			std::cout << "��������� ������, ���: " << GetLastError() << std::endl;
		}
		else {
			std::cout << "���������� �� �����������:" << std::endl;
			for (int i = 0; i < 7; i++) {
				if (attrs[i] & file_attributes) std::cout << GetDescriptionOfAttr(attrs[i]) << std::endl;
			}
			std::cout << "���������� ������������� ����� � ������: " << ((long long)info_file.nFileIndexHigh << 32) + info_file.nFileIndexLow
				<< std::endl << "���������� ����� ����, ������� �������� ����: " << info_file.dwVolumeSerialNumber << std::endl
				<< "������ �����: " << ((long long)info_file.nFileSizeHigh << 32) + info_file.nFileSizeLow << " ����" << std::endl
				<< "����� ������ � ���� ������: " << info_file.nNumberOfLinks << std::endl;
		}
		
	}
	handle_info = CloseHandle(handle_file);
}

void GetTime() {
	TCHAR catalog_name[MAX_PATH];
	HANDLE file_time;
	FILETIME time_create, time_last_access, time_last_write;
	SYSTEMTIME time;

	std::cout << "������� ��� ����� (������: c:\\folder\\text.txt): ";
	std::cin.getline(catalog_name, MAX_PATH);

	file_time = CreateFileA(catalog_name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (GetFileTime(file_time, &time_create, &time_last_access, &time_last_write)) {
		FileTimeToSystemTime(&time_create, &time);
		std::cout << "���� � ����� �������� �����: " << std::setfill('0') << std::setw(2) << time.wDay << "." << std::setfill('0') << std::setw(2) << time.wMonth << "." << time.wYear << "  "
			<< std::setfill('0') << std::setw(2) << time.wHour + 3 << ":" << std::setfill('0') << std::setw(2) << time.wMinute << ":" << std::setfill('0') << std::setw(2) << time.wSecond << std::endl;
		FileTimeToSystemTime(&time_last_access, &time);
		std::cout << "���� � ����� ���������� ���������� � �����: " << std::setfill('0') << std::setw(2) << time.wDay << "." << std::setfill('0') << std::setw(2) << time.wMonth << "." << time.wYear << "  "
			<< std::setfill('0') << std::setw(2) << time.wHour + 3 << ":" << std::setfill('0') << std::setw(2) << time.wMinute << ":" << std::setfill('0') << std::setw(2) << time.wSecond << std::endl;
		FileTimeToSystemTime(&time_last_write, &time);
		std::cout << "���� � ����� ���������� ��������� �����: " << std::setfill('0') << std::setw(2) << time.wDay << "." << std::setfill('0') << std::setw(2) << time.wMonth << "." << time.wYear << "  "
			<< std::setfill('0') << std::setw(2) << time.wHour + 3 << ":" << std::setfill('0') << std::setw(2) << time.wMinute <<  ":" << std::setfill('0') << std::setw(2) << time.wSecond << std::endl;
	}
	else {
		std::cout << "������ ��� ��������� ����������, ���: " << GetLastError() << std::endl;
	}
}

void SetTime() {
	TCHAR catalog_name[MAX_PATH];
	HANDLE file_time;
	FILETIME new_file_time;
	SYSTEMTIME system_time;

	std::cout << "������� ��� ����� (������: c:\\folder\\text.txt): ";
	std::cin.getline(catalog_name, MAX_PATH);

	file_time = CreateFileA(catalog_name, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	GetSystemTime(&system_time);
	SystemTimeToFileTime(&system_time, &new_file_time);
	if (SetFileTime(file_time, &new_file_time, &new_file_time, &new_file_time)) {
		std::cout << "����� �������� �������" << std::endl;
	}
	else {
		std::cout << "������ ��� ������ ������, ���: " << GetLastError() << std::endl;
	}
}

void PrintAttributeMenu() {
	std::cout << "1. �������� �������� �����" << std::endl << "2. �������� �������� �����" << std::endl << "3. �������� ���������� �� �����������" << std::endl << "4. �������� ������ � ��������� ������� �����"
		<< std::endl << "5. �������� ��������� ����� �����" << std::endl << "0. �����" << std::endl;
}

void AttributeMenu() {
	char menu;

	do {
		system("cls");
		PrintAttributeMenu();

		menu = _getch();
		switch (menu)
		{
		case '1':
			GetAttributes();
			system("pause");
			break;
		case '2':
			SetAttributes();
			system("pause");
			break;
		case '3':
			GetInfoByHandle();
			system("pause");
			break;
		case '4':
			GetTime();
			system("pause");
			break;
		case '5':
			SetTime();
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