// Fill out your copyright notice in the Description page of Project Settings.


#include "RealRobotControl.h"

typedef void(*DirectionControl)(float linearVelocity, float angularVelocity);


RealRobotControl::RealRobotControl()
{
	hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,   // 物理文件句柄
		NULL,   // 默认安全级别
		PAGE_READWRITE,   // 可读可写
		0,   // 高位文件大小
		BUF_SIZE,   // 地位文件大小
		L"ShareMemory"   // 共享内存名称
	);

	lpBase = MapViewOfFile(
		hMapFile,            // 共享内存的句柄
		FILE_MAP_ALL_ACCESS, // 可读写许可
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
	// 将数据拷贝到共享内存
	// robotMsg.linearVelocity = *linearVelocity;
	// robotMsg.angularVelocity = *angularVelocity;
	strcpy((char*)lpBase, str.data());

}

RealRobotControl::~RealRobotControl()
{
	// 解除文件映射
	UnmapViewOfFile(lpBase);
	// 关闭内存映射文件对象句柄
	CloseHandle(hMapFile);
}


