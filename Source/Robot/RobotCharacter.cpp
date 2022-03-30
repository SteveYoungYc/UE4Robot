// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotCharacter.h"

// Sets default values
ARobotCharacter::ARobotCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MovementComp = CreateDefaultSubobject<UInterpToMovementComponent>(TEXT("UInterpToMovementComponent"));
	AddInstanceComponent(MovementComp);
	// 创建组件
	RootComponent = CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent());
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChassisStaticMeshComponent"));
	CameraStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CameraStaticMeshComponent"));
	GimbalStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GimbalStaticMeshComponent"));
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	FirstPersonCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCameraComponent"));

	// 绑定组件
	StaticMeshComp->SetupAttachment(RootComponent);
	GimbalStaticMeshComp->SetupAttachment(RootComponent);
	CameraStaticMeshComp->SetupAttachment(GimbalStaticMeshComp);
	SpringArmComp->SetupAttachment(StaticMeshComp);
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	FirstPersonCameraComp->SetupAttachment(CameraStaticMeshComp);
	// MovementComp->SetupAttachment(RootComponent)

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
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using RobotCharacter."));
	positonInput = FVector::ZeroVector;
	/*
	MovementComp->SetUpdatedComponent(RootComponent);
	MovementComp->AddControlPointPosition(FVector::ZeroVector);
	MovementComp->AddControlPointPosition(FVector(100, 0, -1.82));
	MovementComp->BehaviourType = EInterpToBehaviourType::PingPong;
	MovementComp->FinaliseControlPoints();*/
}

// Called every frame
void ARobotCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

	FRotator GimbalYawRotation = GimbalStaticMeshComp->GetRelativeRotation();
	GimbalYawRotation.Yaw += GimbalYawInput.X;
	GimbalStaticMeshComp->SetRelativeRotation(GimbalYawRotation);

	FRotator GimbalPitchRotation = CameraStaticMeshComp->GetRelativeRotation();
	if (GimbalPitchRotation.Pitch + GimbalPitchInput.Y < 80 && GimbalPitchRotation.Pitch + GimbalPitchInput.Y > -80) {
		GimbalPitchRotation.Pitch += GimbalPitchInput.Y;
		CameraStaticMeshComp->SetRelativeRotation(GimbalPitchRotation);
	}

	positonOutput = RootComponent->GetComponentLocation() / 100.0f;
	rotationOutput = RootComponent->GetComponentRotation();
	frameCount = (frameCount + 1) % 60;
	if (frameCount % 5 == 0)
		control.move(&linearVelocity, &angularVelocity);

	FVector pos(100, 200, RootComponent->GetComponentLocation().Z);

	MoveTo(DeltaTime, pos);

}

// Called to bind functionality to input
void ARobotCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ARobotCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARobotCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARobotCharacter::MoveRight);
	PlayerInputComponent->BindAxis("CameraPitch", this, &ARobotCharacter::PitchCamera);
	PlayerInputComponent->BindAxis("GimbalYaw", this, &ARobotCharacter::GimbalYaw);
	PlayerInputComponent->BindAxis("GimbalPitch", this, &ARobotCharacter::GimbalPitch);
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

void ARobotCharacter::GimbalYaw(float AxisValue)
{
	GimbalYawInput.X = AxisValue;
}

void ARobotCharacter::GimbalPitch(float AxisValue)
{
	GimbalPitchInput.Y = AxisValue;
}

void ARobotCharacter::MoveTo(float DeltaTime, FVector pos)
{
	/*
	MovementComp->SetUpdatedComponent(StaticMeshComp);
	// MovementComp->ControlPoints.Empty();
	MovementComp->AddControlPointPosition(StaticMeshComp->GetComponentLocation(), false);
	MovementComp->AddControlPointPosition(pos, true);
	MovementComp->FinaliseControlPoints();*/
	// MovementComp->RestartMovement();

	FVector currPos = RootComponent->GetComponentLocation();
	float dis = FVector::Distance(pos, currPos);
	if (dis > 0.5) {
		float distanceSingle = speed * DeltaTime;
		float cos = (pos.X - currPos.X) / dis;
		float sin = (pos.Y - currPos.Y) / dis;
		FVector nextPos(currPos.X + distanceSingle * cos, currPos.Y + distanceSingle * sin, currPos.Z);
		RootComponent->SetWorldLocation(nextPos);
	}
}
