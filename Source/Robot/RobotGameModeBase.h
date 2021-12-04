// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "RobotGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ROBOT_API ARobotGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	virtual void StartPlay() override;

public:
    /** �Ƴ���ǰ�˵��ؼ�������ָ���ࣨ���У����½��ؼ���*/
    UFUNCTION(BlueprintCallable, Category = "UMG Game")
        void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:

    /** ��Ϸ��ʼʱ�������˵��Ŀؼ��ࡣ*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
        TSubclassOf<UUserWidget> StartingWidgetClass;

    /** �����˵��Ŀؼ�ʵ����*/
    UPROPERTY()
        UUserWidget* CurrentWidget;
};
