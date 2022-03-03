// Fill out your copyright notice in the Description page of Project Settings.


#include "RealRobotControl.h"

typedef void(*DirectionControl)(float linearVelocity, float angularVelocity);


RealRobotControl::RealRobotControl()
{
	path = TEXT("D:\\SJTU\\thesis\\Robot\\Source\\Robot\\Cmd\\cmd.txt");
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

void RealRobotControl::LoadDll()
{

}

void RealRobotControl::VC_DirectionControl(float linearVelocity, float angularVelocity)
{
	FString filePath = "D:/SJTU/thesis/Robot/Plugins/EAIbot/ThirdParty/EAIbot/lib/EAIDll.dll";
	// FString filePath = "D:/SJTU/thesis/Robot/Binaries/Win64/UE4Editor-Robot-0001.dll";
	if (FPaths::FileExists(filePath))		//Can the file be found?
	{

		void* DLLHandle;

		DLLHandle = FPlatformProcess::GetDllHandle(*filePath);
		if (DLLHandle != NULL)
		{
			DirectionControl VC_DirectionControl = NULL;
			FString procName = "VC_DirectionControl";					 //The name of the function defined in the DLL
			VC_DirectionControl = (DirectionControl)FPlatformProcess::GetDllExport(DLLHandle, *procName); // Export the DLL function.
			if (VC_DirectionControl != NULL)
			{
				VC_DirectionControl(linearVelocity, angularVelocity); // Call the DLL function, with arguments corresponding to the signature and return type of the function.
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Dll file is loaded"));
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("DLLHandle failed"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Dll file not found !!!"));
	}
}

void RealRobotControl::move(float* linearVelocity, float* angularVelocity)
{
	FString string = FString::SanitizeFloat(*linearVelocity) + " " + FString::SanitizeFloat(*angularVelocity);
	// SaveTexFile(path, str);
	std::string str = std::to_string(*linearVelocity) + " " + std::to_string(*angularVelocity);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, string);
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


void RealRobotControl::ReadTexFile(const FString& relativePath, FString& outString)
{
	if (relativePath.IsEmpty() == false)
	{
		FString absolutePath = FPaths::ProjectContentDir() + relativePath;
		//absolutePath = absolutePath.Replace(TEXT("/"), TEXT("\\"));
		FFileHelper::LoadFileToString(outString, absolutePath.GetCharArray().GetData());
	}
}

void RealRobotControl::SaveTexFile(const FString& absolutePath, const FString& inString)
{
	if (absolutePath.IsEmpty() == false)
	{
		// absolutePath = absolutePath.Replace(TEXT("/"), TEXT("\\"));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, inString);
		if (FFileHelper::SaveStringToFile(inString, absolutePath.GetCharArray().GetData()) == false) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Write file failed!"));
		}
	}
}

