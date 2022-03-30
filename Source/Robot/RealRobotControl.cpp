// Fill out your copyright notice in the Description page of Project Settings.


#include "RealRobotControl.h"

typedef void(*DirectionControl)(float linearVelocity, float angularVelocity);


RealRobotControl::RealRobotControl()
{
	shared_memory.create(L"UnrealRobotAsServer");
}

void RealRobotControl::move(float* linearVelocity, float* angularVelocity)
{
	FString string = FString::SanitizeFloat(*linearVelocity) + " " + FString::SanitizeFloat(*angularVelocity);
	// std::string str = std::to_string(*linearVelocity) + " " + std::to_string(*angularVelocity);
	// strcpy((char*)lpBase, str.data());
	Msg msg;
	msg.linear_velocity = *linearVelocity;
	msg.angular_velocity = *angularVelocity;
	shared_memory.open(L"UnrealRobotAsServer");
	shared_memory.write(&msg);
	shared_memory.close();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, string);
}

RealRobotControl::~RealRobotControl()
{
	// shared_memory.close();
}


