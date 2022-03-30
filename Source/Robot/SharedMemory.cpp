// Fill out your copyright notice in the Description page of Project Settings.


#include "SharedMemory.h"

int SharedMemory::create(LPCWSTR name) {
	map_file = CreateFileMapping(
		INVALID_HANDLE_VALUE,   // �����ļ����
		NULL,   // Ĭ�ϰ�ȫ����
		PAGE_READWRITE,   // �ɶ���д
		0,   // ��λ�ļ���С
		BUF_SIZE,   // ��λ�ļ���С
		name   // �����ڴ�����
	);

	if (map_file == NULL) {
		cerr << "Creating map_file failed!" << endl;
		return -1;
	}

	lp_base = MapViewOfFile(
		map_file,            // �����ڴ�ľ��
		FILE_MAP_ALL_ACCESS, // �ɶ�д���
		0,
		0,
		BUF_SIZE
	);
	return 0;
}

int SharedMemory::open(LPCWSTR name) {
	map_file = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, name);
	if (map_file == NULL) {
		cerr << "Opening map_file failed!" << endl;
		return -1;
	}
	lp_base = MapViewOfFile(map_file, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (lp_base == NULL) {
		cerr << "Opening map_file failed!" << endl;
		return -1;
	}
	return 0;
}

int SharedMemory::close() {
	if (lp_base == NULL || map_file == NULL) {
		cerr << "Closing failed!" << endl;
		return -1;
	}
	UnmapViewOfFile(lp_base);
	CloseHandle(map_file);
	return 0;
}

int SharedMemory::read(Msg* msg) {
	if (lp_base == NULL) {
		cerr << "Reading failed!" << endl;
		return -1;
	}
	memcpy(buffer, lp_base, BUF_SIZE);
	memcpy(msg, buffer, sizeof(Msg));
	return 0;
}

int SharedMemory::read_string(Msg* msg) {
	memset(buffer, 0, BUF_SIZE);
	strcpy_s(buffer, (char*)lp_base);
	string linear_str = (char*)buffer;
	string angular_str;
	for (int i = 0; i < 20; i++) {
		if (buffer[i] == ' ') {
			angular_str = (char*)(buffer + i + 1);
		}
	}
	msg->linear_velocity = std::stof(linear_str);
	msg->angular_velocity = std::stof(angular_str);
	return 0;
}

int SharedMemory::write(Msg* msg) {
	if (lp_base == NULL) {
		cerr << "Reading failed!" << endl;
		return -1;
	}
	memset(buffer, 0, BUF_SIZE);
	memcpy(buffer, msg, sizeof(Msg));
	memcpy(lp_base, buffer, BUF_SIZE);
	return 0;
}
