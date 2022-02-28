// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// #include "LoadEAIDll.h"


/**
 * 
 */
class ROBOT_API RealRobotControl
{
private:
	float _linearVelocity = 0;
	float _angularVelocity = 0;
	FString path;

public:
	RealRobotControl();
	RealRobotControl(float linearVelocity, float angularVelocity) {
		_linearVelocity = linearVelocity;
		_angularVelocity = angularVelocity;
	}
	void LoadDll();
	void VC_DirectionControl(float linearVelocity, float angularVelocity);
	void move(float linearVelocity, float angularVelocity);
	~RealRobotControl();

	void ReadTexFile(const FString& relativePath, FString& outString);

	void SaveTexFile(const FString& relativePath, const FString& inString);
};
