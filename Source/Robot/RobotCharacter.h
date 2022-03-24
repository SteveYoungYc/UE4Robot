// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/InterpToMovementComponent.h"
#include "RealRobotControl.h"

#include "RobotCharacter.generated.h"

UCLASS()
class ROBOT_API ARobotCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARobotCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		class USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere)
		class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere)
		class UCameraComponent* FirstPersonCameraComp;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* CameraStaticMeshComp;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* GimbalStaticMeshComp;

	UPROPERTY(EditAnywhere)
		UInterpToMovementComponent* MovementComp;

	// 输入变量
	FVector2D MovementInput;
	FVector2D CameraInput;
	FVector2D GimbalYawInput;
	FVector2D GimbalPitchInput;
	float ZoomFactor;
	bool bZoomingIn;

	RealRobotControl control;
	float linearVelocity = 0;
	float angularVelocity = 0;
	int frameCount = 0;
	float RunningTime = 0;
	float speed = 20;


	// 输入函数
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void PitchCamera(float AxisValue);
	void YawCamera(float AxisValue);
	void GimbalYaw(float AxisValue);
	void GimbalPitch(float AxisValue);

	void MoveTo(float DeltaTime, FVector pos);

public:	
	UPROPERTY(VisibleAnywhere, Transient, Category = "Robot Info")
		FVector positonOutput;

	UPROPERTY(VisibleAnywhere, Transient, Category = "Robot Info")
		FVector positonInput;

	UPROPERTY(VisibleAnywhere, Transient, Category = "Robot Info")
		FRotator rotationOutput;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
