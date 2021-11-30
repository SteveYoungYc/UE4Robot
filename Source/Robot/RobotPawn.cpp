// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotPawn.h"

// Sets default values
ARobotPawn::ARobotPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    // 创建组件
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
    StaticMeshComp = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

    // 绑定组件
    StaticMeshComp->SetupAttachment(RootComponent);
    SpringArmComp->SetupAttachment(StaticMeshComp);
    CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

    // 为SpringArm类的变量赋值
    
    // SpringArmComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 90.0f));
    SpringArmComp->TargetArmLength = 200.f;
    SpringArmComp->bEnableCameraLag = true;
    SpringArmComp->CameraLagSpeed = 8.0f;

    // 控制默认玩家
    AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ARobotPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARobotPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    FRotator NewRotation = GetActorRotation();
    NewRotation.Yaw += CameraInput.X;
    SetActorRotation(NewRotation);
    NewRotation = SpringArmComp->GetComponentRotation();
    NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -80.0f, -15.0f);
    SpringArmComp->SetWorldRotation(NewRotation);
    if (!MovementInput.IsZero())
    {
        //Scale our movement input axis values by 100 units per second
        MovementInput = MovementInput.GetSafeNormal() * 200.0f;
        FVector NewLocation = GetActorLocation();
        NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
        NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
        SetActorLocation(NewLocation);
    }
}

// Called to bind functionality to input
void ARobotPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    InputComponent->BindAxis("MoveForward", this, &ARobotPawn::MoveForward);
    InputComponent->BindAxis("MoveRight", this, &ARobotPawn::MoveRight);
    InputComponent->BindAxis("CameraPitch", this, &ARobotPawn::PitchCamera);
    InputComponent->BindAxis("CameraYaw", this, &ARobotPawn::YawCamera);
}

// 输入函数
void ARobotPawn::MoveForward(float AxisValue)
{
    MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void ARobotPawn::MoveRight(float AxisValue)
{
    MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void ARobotPawn::PitchCamera(float AxisValue)
{
    CameraInput.Y = AxisValue;
}

void ARobotPawn::YawCamera(float AxisValue)
{
    CameraInput.X = AxisValue;
}

