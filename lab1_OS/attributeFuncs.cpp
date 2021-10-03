#include <iostream>
#include <windows.h>
#include <iomanip>
#include <conio.h>
#include "attributeFuncs.h"

std::string GetDescriptionOfAttr(DWORD attr) {
	switch (attr)
	{
	case FILE_ATTRIBUTE_ARCHIVE: return "- архивный";
	case FILE_ATTRIBUTE_COMPRESSED: return "- сжатый";
	case FILE_ATTRIBUTE_DIRECTORY: return "- каталог";
	case FILE_ATTRIBUTE_HIDDEN: return "- скрытый";
	case FILE_ATTRIBUTE_NORMAL: return "- не имеет атрибутов";
	case FILE_ATTRIBUTE_READONLY: return "- только для чтения";
	case FILE_ATTRIBUTE_SYSTEM: return "- системный";
	}
}

void GetAttributes() {
	TCHAR catalog_name[MAX_PATH];
	DWORD attr;
	DWORD attrs[7] = { FILE_ATTRIBUTE_ARCHIVE, FILE_ATTRIBUTE_COMPRESSED, FILE_ATTRIBUTE_DIRECTORY, FILE_ATTRIBUTE_HIDDEN,
		FILE_ATTRIBUTE_NORMAL, FILE_ATTRIBUTE_READONLY, FILE_ATTRIBUTE_SYSTEM };

	std::cout << "Введите имя файла (пример: c:\\folder\\text.txt): ";
	std::cin.getline(catalog_name, MAX_PATH);

	attr = GetFileAttributes(catalog_name);

	if (attr == -1) {
		std::cout << "Файл не найден";
	} 
	else if (attr == 0) {
		std::cout << "Ошибка при получении атрибутов";
	}
	else {
		std::cout << "Атрибуты файла (" << attr << "):" << std::endl;
		for (int i = 0; i < 7; i++) {
			if (attrs[i] & attr) std::cout << GetDescriptionOfAttr(attrs[i]) << std::endl;
		}
	}
}

int ChoiceAttr() {
	char choice;
	std::string vars = "12345";
	do {
		std::cout << "Изменить атрибут файла на: " << std::endl << "1. Архив" << std::endl << "2. Скрытый" << std::endl << "3. Без атрибутов"
			<< std::endl << "4. Только для чтения" << std::endl << "5. Системный" << std::endl;
		choice = _getch();
		if (vars.find(choice) == -1) {
			std::cout << "Выбран несуществующий пункт меню, попробуйте снова" << std::endl;
			system("pause");
		}
	} while (vars.find(choice) == -1);
	return choice - 49;
}

void SetAttributes() {
	TCHAR catalog_name[MAX_PATH];
	DWORD attrs[5] = { FILE_ATTRIBUTE_ARCHIVE, FILE_ATTRIBUTE_HIDDEN, FILE_ATTRIBUTE_NORMAL, FILE_ATTRIBUTE_READONLY, FILE_ATTRIBUTE_SYSTEM };

	std::cout << "Введите имя файла (пример: c:\\folder\\text.txt): ";
	std::cin.getline(catalog_name, MAX_PATH);

	if (SetFileAttributes(catalog_name, attrs[ChoiceAttr()])) {
		std::cout << "Атрибут был изменен успешно" << std::endl;
	}
	else {
		std::cout << "Ошибка при изменении атрибута, код: " << GetLastError() << std::endl;
	}
}

void GetInfoByHandle() {
	long handle_info, file_attributes;
	BY_HANDLE_FILE_INFORMATION info_file;
	HANDLE handle_file;
	TCHAR catalog_name[MAX_PATH];
	DWORD attrs[7] = { FILE_ATTRIBUTE_ARCHIVE, FILE_ATTRIBUTE_COMPRESSED, FILE_ATTRIBUTE_DIRECTORY, FILE_ATTRIBUTE_HIDDEN,
		FILE_ATTRIBUTE_NORMAL, FILE_ATTRIBUTE_READONLY, FILE_ATTRIBUTE_SYSTEM };

	std::cout << "Введите имя файла (пример: c:\\folder\\text.txt): ";
	std::cin.getline(catalog_name, MAX_PATH);

	handle_file = CreateFileA(catalog_name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	handle_info = GetFileInformationByHandle(handle_file, &info_file);
	if (!handle_info) {
		std::cout << "Произошла ошибка, код: " << GetLastError() << std::endl;
	}
	else {
		file_attributes = info_file.dwFileAttributes;
		if (file_attributes == -1) {
			std::cout << "Файл не найден" << std::endl;
		}
		else if (file_attributes == 0){
			std::cout << "Произошла ошибка, код: " << GetLastError() << std::endl;
		}
		else {
			std::cout << "Информация по дескриптору:" << std::endl;
			for (int i = 0; i < 7; i++) {
				if (attrs[i] & file_attributes) std::cout << GetDescriptionOfAttr(attrs[i]) << std::endl;
			}
			std::cout << "Уникальный идентификатор связи с файлом: " << ((long long)info_file.nFileIndexHigh << 32) + info_file.nFileIndexLow
				<< std::endl << "Порядковый номер тома, который содержит файл: " << info_file.dwVolumeSerialNumber << std::endl
				<< "Размер файла: " << ((long long)info_file.nFileSizeHigh << 32) + info_file.nFileSizeLow << " Байт" << std::endl
				<< "Число связей с этим файлом: " << info_file.nNumberOfLinks << std::endl;
		}
		
	}
	handle_info = CloseHandle(handle_file);
}

void GetTime() {
	TCHAR catalog_name[MAX_PATH];
	HANDLE file_time;
	FILETIME time_create, time_last_access, time_last_write;
	SYSTEMTIME time;

	std::cout << "Введите имя файла (пример: c:\\folder\\text.txt): ";
	std::cin.getline(catalog_name, MAX_PATH);

	file_time = CreateFileA(catalog_name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (GetFileTime(file_time, &time_create, &time_last_access, &time_last_write)) {
		FileTimeToSystemTime(&time_create, &time);
		std::cout << "Дата и время создания файла: " << std::setfill('0') << std::setw(2) << time.wDay << "." << std::setfill('0') << std::setw(2) << time.wMonth << "." << time.wYear << "  "
			<< std::setfill('0') << std::setw(2) << time.wHour + 3 << ":" << std::setfill('0') << std::setw(2) << time.wMinute << ":" << std::setfill('0') << std::setw(2) << time.wSecond << std::endl;
		FileTimeToSystemTime(&time_last_access, &time);
		std::cout << "Дата и время последнего обращенгия к файлу: " << std::setfill('0') << std::setw(2) << time.wDay << "." << std::setfill('0') << std::setw(2) << time.wMonth << "." << time.wYear << "  "
			<< std::setfill('0') << std::setw(2) << time.wHour + 3 << ":" << std::setfill('0') << std::setw(2) << time.wMinute << ":" << std::setfill('0') << std::setw(2) << time.wSecond << std::endl;
		FileTimeToSystemTime(&time_last_write, &time);
		std::cout << "Дата и время последнего изменения файла: " << std::setfill('0') << std::setw(2) << time.wDay << "." << std::setfill('0') << std::setw(2) << time.wMonth << "." << time.wYear << "  "
			<< std::setfill('0') << std::setw(2) << time.wHour + 3 << ":" << std::setfill('0') << std::setw(2) << time.wMinute <<  ":" << std::setfill('0') << std::setw(2) << time.wSecond << std::endl;
	}
	else {
		std::cout << "Ошибка при получении информации, код: " << GetLastError() << std::endl;
	}
}

void SetTime() {
	TCHAR catalog_name[MAX_PATH];
	HANDLE file_time;
	FILETIME new_file_time;
	SYSTEMTIME system_time;

	std::cout << "Введите имя файла (пример: c:\\folder\\text.txt): ";
	std::cin.getline(catalog_name, MAX_PATH);

	file_time = CreateFileA(catalog_name, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	GetSystemTime(&system_time);
	SystemTimeToFileTime(&system_time, &new_file_time);
	if (SetFileTime(file_time, &new_file_time, &new_file_time, &new_file_time)) {
		std::cout << "Время заменено успешно" << std::endl;
	}
	else {
		std::cout << "Ошибка при замене данных, код: " << GetLastError() << std::endl;
	}
}

void PrintAttributeMenu() {
	std::cout << "1. Получить атрибуты файла" << std::endl << "2. Изменить атрибуты файла" << std::endl << "3. Получить информацию по дескриптору" << std::endl << "4. Получить данные о системном времени файла"
		<< std::endl << "5. Изменить системное время файла" << std::endl << "0. Назад" << std::endl;
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
			std::cout << "Выбран несуществующий пункт меню, попробуйте снова" << std::endl;
			system("pause");
			break;
		}
	} while (menu != '0');
}