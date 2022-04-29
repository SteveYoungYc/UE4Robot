// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "mycvDll.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/InterpToMovementComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "RealRobotControl.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Misc/FileHelper.h"
#include "Misc/MessageDialog.h"
#include "DelayAction.h"
#include "Kismet/GameplayStatics.h"

#include "ImageUtils.h"
#include "math.h"

#include "RobotCharacter.generated.h"

//#pragma comment(lib, "E:\\3D_R\\UE4Model\\Robot_old\\ThirdParty\\OpenCV\\Libraries\\Win64\\opencv_world3411.lib")

#define GoForward  1.f
#define GoBackward -1.f
#define TurnRight 1.f
#define TurnLeft -1.f
#define TurnUp 1.f
#define TurnDown -1.f
#define StopRobot 0.f

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCameraComponent* FirstPersonCameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* CameraStaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* GimbalStaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UInterpToMovementComponent* MovementComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneCaptureComponent2D* SceneCaptureComp;

	// �������˶�ѧ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Robot Info")
		float LineSpeed = 20.f;  // ��λ��cm / s
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Robot Info")
		float TurnSpeed = 10.f;  // ��λ��deg/ s


	// ��ʱ��Timer ��������˵��˿�
	FTimerHandle RobotTimerHandle;
	bool	  bRobotMotionFlag = TRUE;
	float     fTimerPeriod = 0.01; // ��λ: ��
	UPROPERTY(BlueprintReadOnly)
		FVector   Direction;
	UPROPERTY(BlueprintReadWrite)
		FVector   ChassisPosition;
	UPROPERTY(BlueprintReadWrite)
		FRotator  ChassisAngle;
	UPROPERTY(BlueprintReadWrite)
		FRotator  PTZPose;
	UPROPERTY(BlueprintReadWrite)
		float cameraFOV = 54.733;
	UPROPERTY(BlueprintReadWrite)
		float TurnAngle = 0.f;
	UPROPERTY(BlueprintReadWrite)
		float TurnTime = 0.f;
	UPROPERTY(BlueprintReadWrite)
		float GoTime = 0.f;

	bool	bManualFlag = FALSE;
	float	fGoDirection;
	float	fTurnDirection;

	// ���̺���̨��Ҫ��������Ŀ��λ�˱���
	float	  fTargetChassisGo = 0;
	float     fTargetChassisYaw = 0;
	FRotator  FTargetPTZAngle = FRotator(0, 0, 0);

	// ���û����˵������λ�úͳ���Ƕȡ���̨�Ƕ�
	UFUNCTION(BlueprintCallable, Category = "BuiltByMyself|PoseRelocation")
		void SetRobotPositionAndPose();
	/*********************
	λ���ض�λ�㷨��ر���
	***********************/
	cv::Mat Homo = cv::Mat::zeros(3, 3, CV_64F);
	cv::Point2d PixelDev;
	cv::Point3d RotAngle;
	cv::Point3d Tc;
	UPROPERTY(BlueprintReadWrite)
		float Zc = 2596.5535;
	UPROPERTY(BlueprintReadWrite)
		float Fu = 2596.5535;
	UPROPERTY(BlueprintReadWrite)
		float Fv = 2596.5535;
	UPROPERTY(BlueprintReadOnly)
		float PRPostionError;
	UPROPERTY(BlueprintReadWrite)
		FVector2D PixelDeviation;
	UPROPERTY(BlueprintReadWrite)
		FRotator RotationDeviationAngle;
	UPROPERTY(BlueprintReadWrite)
		FVector CameraTranslationVector; // �������ϵ��ƽ������
	UPROPERTY(BlueprintReadWrite)
		FVector ChassisTranslationVector;
	UPROPERTY(BlueprintReadWrite)
		float RunTime;

	cv::Mat CalibrationImage;
	cv::Mat InitialImage;
	cv::Mat RealTimeImage;
	int16 IterationOfMethod = 0;
	// CRP�㷨ר�õĵ�һ֡��궨֡�ĳ�ʼλ����
	cv::Mat Rotation10;
	cv::Mat Translation10;
	double ImgDepth10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateSettings")
		FString CalibrationImgPath1x = TEXT("E:\\3D_R\\UE4Model\\Robot_old\\PythonScripts\\CalibrationImage.png");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateSettings")
		FString CalibrationImgPath10x = TEXT("E:\\3D_R\\UE4Model\\Robot_old\\PythonScripts\\CalibrationImage_10x.png");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateSettings")
		FString InitialImgPath = TEXT("E:\\3D_R\\UE4Model\\Robot_old\\PythonScripts\\InitialImage.png");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="StateSettings")
		FVector InitialPosErr; //����ͼ->BP_Character��->�Ҳ����Բ˵�->StateSettingsѡ��������õ��̳�ʼ��λ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateSettings")
		FVector CalibrationPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateSettings")
		FRotator CalibrationChassisAngle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateSettings")
		FRotator CalibrationPTZAngle;

	/*********************
	λ���ض�λ�㷨ʵ�ֺ�����
	***********************/
	// �ú���������APR��ACR�㷨��Ҫ��λ����
	UFUNCTION(BlueprintCallable, Category = "BuiltByMyself|PoseRelocation")
		void PoseErrorDecomposition();
	UFUNCTION(BlueprintCallable, Category = "BuiltByMyself|RobotMotionControl")
		void RobotTurnThenGoVector(FVector2D TurnXZVector, float GoDistance);
	UFUNCTION(BlueprintCallable, Category = "BuiltByMyself|RobotMotionControl")
		void RobotTurnThenGo(float Angle, float GoDistance);
	UFUNCTION(BlueprintCallable, Category = "BuiltByMyself|PoseRelocation")
		void GetCalibrationRobotPose();
	UFUNCTION(BlueprintCallable, Category = "BuiltByMyself|PoseRelocation")
		void PositionErrorComputation();
	UFUNCTION(BlueprintCallable, Category = "BuiltByMyself|PoseRelocation")
		void RobotPoseInitialize();
	// �ú���������CRP�㷨��Ҫ��λ����
	UFUNCTION(BlueprintCallable, Category = "BuiltByMyself|PoseRelocation")
		void CRPPoseErrorDecompostion(bool bIsFirstFrame);

	// ���ã�λ���ض�λ��������ȫ����ͼʵ��
	void PoseRelocalization();

	// ��ȡ������λ����Ϣ����ʼ�������˱궨λ�ˡ����λ�ˣ��������Ӧ�ı궨ͼƬ�ͳ�ʼͼƬ
	void PrintRobotPoseOnScreen();
	void InitialRobotPose();

	// �������ƻ������˶�
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void PitchCamera(float AxisValue);
	void YawCamera(float AxisValue);
	void RobotMotionTimer();
	void robotManualMode();
	void robotEmergency();
	void SetFOV();

	/****************
	�������ܺ�����
	*****************/ 
	// ��ͼ�꣬��ͼ�ű�����ʹ�øú���
	UFUNCTION(BlueprintCallable, Category = "BuiltByMyself|UnusedFunctions")
		void testEveryThing();
	// ����ȾĿ��д���ļ�
	UFUNCTION(BlueprintCallable, Category = "BuiltByMyself|RenderTarget")
		void SaveRenderTargetToFile(const FString& fileDestination);
	// ����ȾĿ���� cv::Mat ����
	UFUNCTION(BlueprintCallable, Category = "BuiltByMyself|RenderTarget")
		void ReadRenderTargetToMat();
	// ��ѧ��ķ��ź���
	UFUNCTION(BlueprintPure, Category = "BuiltByMyself|MyMathFunctions")
		float Sign(float number);
	// ������̬�ֲ�N~(mean,std)�������
	UFUNCTION(BlueprintPure, Category = "BuiltByMyself|MyMathFunctions")
		float GaussianRandomNumber(float mean, float std);
	// ������Ϣ����ʾ�ַ������ı�
	UFUNCTION(BlueprintCallable, Category = "BuiltByMyself|UnusedFunctions")
		void PrintTextInDialog(FString DialogTitle, FString DialogMessage);

	// ��ʱ���������ã�����Timer+����������ʱ����
	void MyDelay(UObject* WorldContextObject, float Duration);
	UFUNCTION(BlueprintCallable, Category = "BuiltByMyself|UnusedFunctions")
		void DelayFinished();

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
