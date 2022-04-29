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

	// 机器人运动学参数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Robot Info")
		float LineSpeed = 20.f;  // 单位：cm / s
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Robot Info")
		float TurnSpeed = 10.f;  // 单位：deg/ s


	// 定时器Timer 仿真机器人的运控
	FTimerHandle RobotTimerHandle;
	bool	  bRobotMotionFlag = TRUE;
	float     fTimerPeriod = 0.01; // 单位: 秒
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

	// 底盘和云台需要动作到的目标位姿变量
	float	  fTargetChassisGo = 0;
	float     fTargetChassisYaw = 0;
	FRotator  FTargetPTZAngle = FRotator(0, 0, 0);

	// 设置机器人到输入的位置和朝向角度、云台角度
	UFUNCTION(BlueprintCallable, Category = "BuiltByMyself|PoseRelocation")
		void SetRobotPositionAndPose();
	/*********************
	位姿重定位算法相关变量
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
		FVector CameraTranslationVector; // 相机坐标系的平移向量
	UPROPERTY(BlueprintReadWrite)
		FVector ChassisTranslationVector;
	UPROPERTY(BlueprintReadWrite)
		float RunTime;

	cv::Mat CalibrationImage;
	cv::Mat InitialImage;
	cv::Mat RealTimeImage;
	int16 IterationOfMethod = 0;
	// CRP算法专用的第一帧与标定帧的初始位姿量
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
		FVector InitialPosErr; //打开蓝图->BP_Character类->右侧属性菜单->StateSettings选项卡可以设置底盘初始定位误差
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateSettings")
		FVector CalibrationPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateSettings")
		FRotator CalibrationChassisAngle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateSettings")
		FRotator CalibrationPTZAngle;

	/*********************
	位姿重定位算法实现函数段
	***********************/
	// 该函数用来求APR、ACR算法需要的位姿量
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
	// 该函数用来求CRP算法需要的位姿量
	UFUNCTION(BlueprintCallable, Category = "BuiltByMyself|PoseRelocation")
		void CRPPoseErrorDecompostion(bool bIsFirstFrame);

	// 弃用，位姿重定位整个过程全用蓝图实现
	void PoseRelocalization();

	// 获取机器人位姿信息、初始化机器人标定位姿、误差位姿，并捕获对应的标定图片和初始图片
	void PrintRobotPoseOnScreen();
	void InitialRobotPose();

	// 按键控制机器人运动
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void PitchCamera(float AxisValue);
	void YawCamera(float AxisValue);
	void RobotMotionTimer();
	void robotManualMode();
	void robotEmergency();
	void SetFOV();

	/****************
	辅助功能函数段
	*****************/ 
	// 蓝图宏，蓝图脚本可以使用该函数
	UFUNCTION(BlueprintCallable, Category = "BuiltByMyself|UnusedFunctions")
		void testEveryThing();
	// 将渲染目标写入文件
	UFUNCTION(BlueprintCallable, Category = "BuiltByMyself|RenderTarget")
		void SaveRenderTargetToFile(const FString& fileDestination);
	// 将渲染目标存进 cv::Mat 对象
	UFUNCTION(BlueprintCallable, Category = "BuiltByMyself|RenderTarget")
		void ReadRenderTargetToMat();
	// 数学里的符号函数
	UFUNCTION(BlueprintPure, Category = "BuiltByMyself|MyMathFunctions")
		float Sign(float number);
	// 服从正态分布N~(mean,std)的随机数
	UFUNCTION(BlueprintPure, Category = "BuiltByMyself|MyMathFunctions")
		float GaussianRandomNumber(float mean, float std);
	// 利用消息框显示字符或者文本
	UFUNCTION(BlueprintCallable, Category = "BuiltByMyself|UnusedFunctions")
		void PrintTextInDialog(FString DialogTitle, FString DialogMessage);

	// 延时函数，弃用，不如Timer+匿名函数延时好用
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
