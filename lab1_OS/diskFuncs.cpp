#include <Windows.h>
#include <iostream>
#define BUFF 256


void ListOfAvailableDisks() {
	std::cout << "Список доступных дисков:" << std::endl;

	int temp = GetLogicalDrives();
	for (int i = 0; i < 26; i++) {
		if ((temp >> i) & 1) std::cout << "- " << (char)(65 + i) << ":\\" << std::endl;
	}
}

std::string GetType(UINT dType) {
	switch (dType)
	{
	case DRIVE_UNKNOWN: return "- UNKNOWN (Неизвестный тип)";
	case DRIVE_NO_ROOT_DIR: return "- DRIVE NO ROOT DIR (Неправильный путь)";
	case DRIVE_REMOVABLE: return "- REMOVABLE (Съёмный диск)";
	case DRIVE_FIXED: return "- FIXED (Фиксированный диск)";
	case DRIVE_REMOTE: return "- REMOTE (Удалённый диск)";
	case DRIVE_CDROM: return "- CDROM (CD-ROM диск)";
	case DRIVE_RAMDISK: return "- RAMDISK (RAM диск)";
	}
}

std::string GetOption(DWORD optionFlag) {
	switch (optionFlag)
	{
	case FILE_CASE_PRESERVED_NAMES: return " - Указанный том поддерживает сохраненный регистр имен файлов, когда он помещает имя на диск";
	case FILE_CASE_SENSITIVE_SEARCH: return " - Указанный том поддерживает имена файлов с учетом регистра";
	case FILE_DAX_VOLUME: return " - Указанный том является томом прямого доступа (DAX)";
	case FILE_FILE_COMPRESSION: return " - Указанный том поддерживает сжатие файлов";
	case FILE_NAMED_STREAMS: return " - Указанный том поддерживает именованные потоки";
	case FILE_PERSISTENT_ACLS: return " - Указанный том сохраняет и применяет списки управления доступом (ACL)";
	case FILE_READ_ONLY_VOLUME: return " - Указанный том доступен только для чтения";
	case FILE_SEQUENTIAL_WRITE_ONCE: return " - Указанный том поддерживает одну последовательную запись";
	case FILE_SUPPORTS_ENCRYPTION: return " - Указанный том поддерживает зашифрованную файловую систему (EFS)";
	case FILE_SUPPORTS_EXTENDED_ATTRIBUTES: return " - Указанный том поддерживает расширенные атрибуты";
	case FILE_SUPPORTS_HARD_LINKS: return " - Указанный том поддерживает жесткие ссылки";
	case FILE_SUPPORTS_OBJECT_IDS: return " - Указанный том поддерживает идентификаторы объектов";
	case FILE_SUPPORTS_OPEN_BY_FILE_ID: return " - Файловая система поддерживает открытие по FileID";
	case FILE_SUPPORTS_REPARSE_POINTS: return " - Указанный том поддерживает точки повторного разбора";
	case FILE_SUPPORTS_SPARSE_FILES: return " - Указанный том поддерживает разреженные файлы";
	case FILE_SUPPORTS_TRANSACTIONS: return " - Указанный том поддерживает транзакции";
	case FILE_SUPPORTS_USN_JOURNAL: return " - Указанный том поддерживает журналы обновления порядковых номеров (USN)";
	case FILE_UNICODE_ON_DISK: return " - Указанный том поддерживает Unicode в именах файлов по мере их появления на диске";
	case FILE_VOLUME_IS_COMPRESSED: return " - Указанный том является сжатым томом";
	case FILE_VOLUME_QUOTAS: return " - Указанный том поддерживает дисковые квоты";
	case FILE_SUPPORTS_BLOCK_REFCOUNTING: return " - Указанный том поддерживает совместное использование логических кластеров между файлами на одном томе";
	}
}

void GetInfoAboutDisk() {
	TCHAR disk_name[MAX_PATH];
	UINT dType;
	TCHAR lpVolumeNameBuffer[BUFF];
	DWORD lpVolumeSerialNumber = 0;
	DWORD lpMaximumComponentLength = 0;
	DWORD lpFileSystemFlags = 0;
	TCHAR lpFileSystemNameBuffer[BUFF];
	DWORD flags[21] = { FILE_CASE_PRESERVED_NAMES, FILE_CASE_SENSITIVE_SEARCH, FILE_DAX_VOLUME, FILE_FILE_COMPRESSION, FILE_NAMED_STREAMS,
	FILE_PERSISTENT_ACLS, FILE_READ_ONLY_VOLUME, FILE_SEQUENTIAL_WRITE_ONCE, FILE_SUPPORTS_ENCRYPTION, FILE_SUPPORTS_EXTENDED_ATTRIBUTES, 
	FILE_SUPPORTS_HARD_LINKS, FILE_SUPPORTS_OBJECT_IDS, FILE_SUPPORTS_OPEN_BY_FILE_ID, FILE_SUPPORTS_REPARSE_POINTS, FILE_SUPPORTS_SPARSE_FILES,
	FILE_SUPPORTS_TRANSACTIONS, FILE_SUPPORTS_USN_JOURNAL, FILE_UNICODE_ON_DISK, FILE_VOLUME_IS_COMPRESSED, FILE_VOLUME_QUOTAS, 
	FILE_SUPPORTS_BLOCK_REFCOUNTING };
	DWORD sectorsPerCluster;
	DWORD bytesPerSector;
	DWORD numberOfFreeClusters;
	DWORD totalNumberOfClusters;

	std::cout << "Введите название диска(пример: c:\\) : ";
	std::cin.getline(disk_name, MAX_PATH);

	dType = GetDriveType(disk_name);

	std::cout << GetType(dType) << std::endl;

	if (!GetVolumeInformation(disk_name, lpVolumeNameBuffer, BUFF, &lpVolumeSerialNumber,
		&lpMaximumComponentLength, &lpFileSystemFlags, lpFileSystemNameBuffer, BUFF)) {
		std::cout << "Ошибка при обработке запроса, код: " << GetLastError() << std::endl;
	}
	else {
		std::wcout << "Название диска: " << lpVolumeNameBuffer << std::endl << "Серийный номер: " << std::hex << lpVolumeSerialNumber
			<< std::endl << "Максимальная длина файла: " << std::dec << lpMaximumComponentLength << std::endl << "Имя файловой системы: "
			<< lpFileSystemNameBuffer << std::endl << "Опции файловой системы: " << std::endl;
		for (int i = 0; i < 21; i++) {
			if (lpFileSystemFlags & flags[i]) std::cout << GetOption(flags[i]) << std::endl;
		}
	}

	if (GetDiskFreeSpace(disk_name, &sectorsPerCluster, &bytesPerSector, &numberOfFreeClusters, &totalNumberOfClusters)) {
		std::cout << "Число секторов в кластере: " << sectorsPerCluster << std::endl << "Число байт в кластере: " << bytesPerSector
			<< std::endl << "Число свободных кластеров: " << numberOfFreeClusters << std::endl << "Общее число кластеров: "
			<< totalNumberOfClusters << std::endl;
	}
}