// Fill out your copyright notice in the Description page of Project Settings.


#include "RealRobotControl.h"

typedef void(*DirectionControl)(float linearVelocity, float angularVelocity);


RealRobotControl::RealRobotControl()
{
	hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,   // �����ļ����
		NULL,   // Ĭ�ϰ�ȫ����
		PAGE_READWRITE,   // �ɶ���д
		0,   // ��λ�ļ���С
		BUF_SIZE,   // ��λ�ļ���С
		L"ShareMemory"   // �����ڴ�����
	);

	lpBase = MapViewOfFile(
		hMapFile,            // �����ڴ�ľ��
		FILE_MAP_ALL_ACCESS, // �ɶ�д���
		0,
		0,
		BUF_SIZE
	);
}

void RealRobotControl::move(float* linearVelocity, float* angularVelocity)
{
	FString string = FString::SanitizeFloat(*linearVelocity) + " " + FString::SanitizeFloat(*angularVelocity);
	// SaveTexFile(path, str);
	std::string str = std::to_string(*linearVelocity) + " " + std::to_string(*angularVelocity);
	// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, string);
	// char str[BUF_SIZE];
	//strncpy(str, (char*)linearVelocity, sizeof(float));
	//strncpy(str + 8, (char*)angularVelocity, sizeof(float));
	// �����ݿ����������ڴ�
	// robotMsg.linearVelocity = *linearVelocity;
	// robotMsg.angularVelocity = *angularVelocity;
	strcpy((char*)lpBase, str.data());

}

RealRobotControl::~RealRobotControl()
{
	// ����ļ�ӳ��
	UnmapViewOfFile(lpBase);
	// �ر��ڴ�ӳ���ļ�������
	CloseHandle(hMapFile);
}


