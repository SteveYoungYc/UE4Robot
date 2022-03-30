// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <windows.h>
#include <string>
#include "SharedMemory.h"


/**
 * 
 */
class ROBOT_API RealRobotControl
{
private:
	float _linearVelocity = 0;
	float _angularVelocity = 0;
	FString path;
	SharedMemory shared_memory;

public:
	RealRobotControl();
	RealRobotControl(float linearVelocity, float angularVelocity) {
		_linearVelocity = linearVelocity;
		_angularVelocity = angularVelocity;
	}
	void move(float* linearVelocity, float* angularVelocity);
	~RealRobotControl();
};
