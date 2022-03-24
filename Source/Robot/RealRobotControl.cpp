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
		L"UnrealRobotAsServer"   // 共享内存名称
	);

	lpBase = MapViewOfFile(
		hMapFile,            // 共享内存的句柄
		FILE_MAP_ALL_ACCESS, // 可读写许可
		0,
		0,
		BUF_SIZE
	);

	hMapFile1 = CreateFileMapping(
		INVALID_HANDLE_VALUE,   // 物理文件句柄
		NULL,   // 默认安全级别
		PAGE_READWRITE,   // 可读可写
		0,   // 高位文件大小
		BUF_SIZE,   // 地位文件大小
		L"RealRobotAsServer"   // 共享内存名称
	);

	lpBase1 = MapViewOfFile(
		hMapFile1,            // 共享内存的句柄
		FILE_MAP_ALL_ACCESS, // 可读写许可
		0,
		0,
		BUF_SIZE
	);
}

void RealRobotControl::move(float* linearVelocity, float* angularVelocity)
{
	FString string = FString::SanitizeFloat(*linearVelocity) + " " + FString::SanitizeFloat(*angularVelocity);
	std::string str = std::to_string(*linearVelocity) + " " + std::to_string(*angularVelocity);
	strcpy((char*)lpBase, str.data());
}

RealRobotControl::~RealRobotControl()
{
	// 解除文件映射
	UnmapViewOfFile(lpBase);
	// 关闭内存映射文件对象句柄
	CloseHandle(hMapFile);
	// 解除文件映射
	UnmapViewOfFile(lpBase1);
	// 关闭内存映射文件对象句柄
	CloseHandle(hMapFile1);
}


