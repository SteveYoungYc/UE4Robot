// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <windows.h>
#include <string>

#define BUF_SIZE 4096

struct RobotMsg {
	float linearVelocity;
	float angularVelocity;
};

/**
 * 
 */
class ROBOT_API RealRobotControl
{
private:
	float _linearVelocity = 0;
	float _angularVelocity = 0;
	FString path;
	HANDLE hMapFile;
	LPVOID lpBase;
	struct RobotMsg robotMsg;

public:
	RealRobotControl();
	RealRobotControl(float linearVelocity, float angularVelocity) {
		_linearVelocity = linearVelocity;
		_angularVelocity = angularVelocity;
	}
	void move(float* linearVelocity, float* angularVelocity);
	~RealRobotControl();
};
