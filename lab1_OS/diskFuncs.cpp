#include <Windows.h>
#include <iostream>
#define BUFF 256


void ListOfAvailableDisks() {
	std::cout << "������ ��������� ������:" << std::endl;

	int temp = GetLogicalDrives();
	for (int i = 0; i < 26; i++) {
		if ((temp >> i) & 1) std::cout << "- " << (char)(65 + i) << ":\\" << std::endl;
	}
}

std::string GetType(UINT dType) {
	switch (dType)
	{
	case DRIVE_UNKNOWN: return "- UNKNOWN (����������� ���)";
	case DRIVE_NO_ROOT_DIR: return "- DRIVE NO ROOT DIR (������������ ����)";
	case DRIVE_REMOVABLE: return "- REMOVABLE (������� ����)";
	case DRIVE_FIXED: return "- FIXED (������������� ����)";
	case DRIVE_REMOTE: return "- REMOTE (�������� ����)";
	case DRIVE_CDROM: return "- CDROM (CD-ROM ����)";
	case DRIVE_RAMDISK: return "- RAMDISK (RAM ����)";
	}
}

std::string GetOption(DWORD optionFlag) {
	switch (optionFlag)
	{
	case FILE_CASE_PRESERVED_NAMES: return " - ��������� ��� ������������ ����������� ������� ���� ������, ����� �� �������� ��� �� ����";
	case FILE_CASE_SENSITIVE_SEARCH: return " - ��������� ��� ������������ ����� ������ � ������ ��������";
	case FILE_DAX_VOLUME: return " - ��������� ��� �������� ����� ������� ������� (DAX)";
	case FILE_FILE_COMPRESSION: return " - ��������� ��� ������������ ������ ������";
	case FILE_NAMED_STREAMS: return " - ��������� ��� ������������ ����������� ������";
	case FILE_PERSISTENT_ACLS: return " - ��������� ��� ��������� � ��������� ������ ���������� �������� (ACL)";
	case FILE_READ_ONLY_VOLUME: return " - ��������� ��� �������� ������ ��� ������";
	case FILE_SEQUENTIAL_WRITE_ONCE: return " - ��������� ��� ������������ ���� ���������������� ������";
	case FILE_SUPPORTS_ENCRYPTION: return " - ��������� ��� ������������ ������������� �������� ������� (EFS)";
	case FILE_SUPPORTS_EXTENDED_ATTRIBUTES: return " - ��������� ��� ������������ ����������� ��������";
	case FILE_SUPPORTS_HARD_LINKS: return " - ��������� ��� ������������ ������� ������";
	case FILE_SUPPORTS_OBJECT_IDS: return " - ��������� ��� ������������ �������������� ��������";
	case FILE_SUPPORTS_OPEN_BY_FILE_ID: return " - �������� ������� ������������ �������� �� FileID";
	case FILE_SUPPORTS_REPARSE_POINTS: return " - ��������� ��� ������������ ����� ���������� �������";
	case FILE_SUPPORTS_SPARSE_FILES: return " - ��������� ��� ������������ ����������� �����";
	case FILE_SUPPORTS_TRANSACTIONS: return " - ��������� ��� ������������ ����������";
	case FILE_SUPPORTS_USN_JOURNAL: return " - ��������� ��� ������������ ������� ���������� ���������� ������� (USN)";
	case FILE_UNICODE_ON_DISK: return " - ��������� ��� ������������ Unicode � ������ ������ �� ���� �� ��������� �� �����";
	case FILE_VOLUME_IS_COMPRESSED: return " - ��������� ��� �������� ������ �����";
	case FILE_VOLUME_QUOTAS: return " - ��������� ��� ������������ �������� �����";
	case FILE_SUPPORTS_BLOCK_REFCOUNTING: return " - ��������� ��� ������������ ���������� ������������� ���������� ��������� ����� ������� �� ����� ����";
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

	std::cout << "������� �������� �����(������: c:\\) : ";
	std::cin.getline(disk_name, MAX_PATH);

	dType = GetDriveType(disk_name);

	std::cout << GetType(dType) << std::endl;

	if (!GetVolumeInformation(disk_name, lpVolumeNameBuffer, BUFF, &lpVolumeSerialNumber,
		&lpMaximumComponentLength, &lpFileSystemFlags, lpFileSystemNameBuffer, BUFF)) {
		std::cout << "������ ��� ��������� �������, ���: " << GetLastError() << std::endl;
	}
	else {
		std::wcout << "�������� �����: " << lpVolumeNameBuffer << std::endl << "�������� �����: " << std::hex << lpVolumeSerialNumber
			<< std::endl << "������������ ����� �����: " << std::dec << lpMaximumComponentLength << std::endl << "��� �������� �������: "
			<< lpFileSystemNameBuffer << std::endl << "����� �������� �������: " << std::endl;
		for (int i = 0; i < 21; i++) {
			if (lpFileSystemFlags & flags[i]) std::cout << GetOption(flags[i]) << std::endl;
		}
	}

	if (GetDiskFreeSpace(disk_name, &sectorsPerCluster, &bytesPerSector, &numberOfFreeClusters, &totalNumberOfClusters)) {
		std::cout << "����� �������� � ��������: " << sectorsPerCluster << std::endl << "����� ���� � ��������: " << bytesPerSector
			<< std::endl << "����� ��������� ���������: " << numberOfFreeClusters << std::endl << "����� ����� ���������: "
			<< totalNumberOfClusters << std::endl;
	}
}