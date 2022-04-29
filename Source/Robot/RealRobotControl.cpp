// Fill out your copyright notice in the Description page of Project Settings.


#include "RealRobotControl.h"

typedef void(*DirectionControl)(float linearVelocity, float angularVelocity);


RealRobotControl::RealRobotControl()
{
	// shared_memory.create(L"UnrealRobotAsServer");
}

void RealRobotControl::move(float* linearVelocity, float* angularVelocity)
{
	FString string = FString::SanitizeFloat(*linearVelocity) + " " + FString::SanitizeFloat(*angularVelocity);
	Msg msg;
	msg.linear_velocity = *linearVelocity;
	msg.angular_velocity = *angularVelocity;
	shared_memory.write(&msg);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, string);
}

Msg RealRobotControl::getMsg() {
	shared_memory.open(L"RealRobotAsServer");
	Msg msg;
	shared_memory.read(&msg);
	shared_memory.close();
	return msg;
}

RealRobotControl::~RealRobotControl()
{
	// shared_memory.close();
}


