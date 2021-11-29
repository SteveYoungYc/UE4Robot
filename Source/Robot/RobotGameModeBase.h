// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RobotGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ROBOT_API ARobotGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	virtual void StartPlay() override;
};
