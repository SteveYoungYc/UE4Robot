// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotCharacter.h"

// Sets default values
ARobotCharacter::ARobotCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// 创建组件
	RootComponent = CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent());
	StaticMeshComp = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	FirstPersonCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCameraComponent"));

	// 绑定组件
	StaticMeshComp->SetupAttachment(RootComponent);
	SpringArmComp->SetupAttachment(StaticMeshComp);
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	FirstPersonCameraComp->SetupAttachment(StaticMeshComp);

	// 为SpringArm类的变量赋值

	// SpringArmComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 90.0f));
	SpringArmComp->TargetArmLength = 200.f;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 10.0f;

	// CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), StartingWidgetClass);
	// CurrentWidget->AddToViewport();

	// AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ARobotCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr);

	// Display a debug message for five seconds. 
	// The -1 "Key" value argument prevents the message from being updated or refreshed.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));
	// control.LoadDll();
}

// Called every frame
void ARobotCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += CameraInput.X;
	SetActorRotation(NewRotation);
	NewRotation = SpringArmComp->GetComponentRotation();
	NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -80.0f, 15.0f);
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
	// positonOutput = GetActorTransform().GetLocation() / 100.0f;
	positonOutput = positonInput;
	*/
	frameCount = (frameCount + 1) % 5;
	if (frameCount == 0)
		control.move(&linearVelocity, &angularVelocity);

	moveTo(DeltaTime, 0, 0);
	//linearVelocity += 0.01;
	//angularVelocity += 0.01;
}

// Called to bind functionality to input
void ARobotCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ARobotCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARobotCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARobotCharacter::MoveRight);
	PlayerInputComponent->BindAxis("CameraPitch", this, &ARobotCharacter::PitchCamera);
	// PlayerInputComponent->BindAxis("CameraYaw", this, &ARobotCharacter::AddControllerYawInput);
	// PlayerInputComponent->BindAxis("CameraYaw", this, &ARobotCharacter::YawCamera);
}

// 输入函数
void ARobotCharacter::MoveForward(float AxisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, AxisValue / 3);
	linearVelocity = AxisValue;
}

void ARobotCharacter::MoveRight(float AxisValue)
{
	// FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	// AddMovementInput(Direction, AxisValue / 3);
	// CameraInput.X = AxisValue;
	angularVelocity = AxisValue;
}

void ARobotCharacter::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void ARobotCharacter::YawCamera(float AxisValue)
{
	angularVelocity = AxisValue;
}

void ARobotCharacter::moveTo(float DeltaTime, float x, float y)
{
	FVector NewLoacation = GetActorLocation();
	// 防止浮点无限大导致不精确,每2*PI一个循环
	if (RunningTime >= 2 * PI)
	{
		RunningTime = 0;
	}
	// 获取高度变化曲线
	float DeltaHeight = FMath::Sin(RunningTime);
	// DeltaTime是上一帧和下一帧之间使用的时间
	RunningTime += DeltaTime;

	// 20是沿着Z轴的伸缩变化值
	NewLoacation.Z += DeltaHeight /** 20.f*/;
	SetActorLocation(NewLoacation);
}
