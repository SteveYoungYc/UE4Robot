// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotCharacter.h"

using namespace cv;
// Sets default values
ARobotCharacter::ARobotCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MovementComp = CreateDefaultSubobject<UInterpToMovementComponent>(TEXT("UInterpToMovementComponent"));
	AddInstanceComponent(MovementComp);

	RootComponent = CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent());
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChassisStaticMeshComponent"));
	CameraStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CameraStaticMeshComponent"));
	GimbalStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GimbalStaticMeshComponent"));
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	FirstPersonCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCameraComponent"));
	SceneCaptureComp = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent"));

	StaticMeshComp->SetupAttachment(RootComponent);
	GimbalStaticMeshComp->SetupAttachment(RootComponent);
	CameraStaticMeshComp->SetupAttachment(GimbalStaticMeshComp);
	SpringArmComp->SetupAttachment(StaticMeshComp);
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	FirstPersonCameraComp->SetupAttachment(CameraStaticMeshComp);
	SceneCaptureComp->SetupAttachment(FirstPersonCameraComp);
	// MovementComp->SetupAttachment(RootComponent)

	// SpringArmComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 90.0f));
	SpringArmComp->TargetArmLength = 200.f;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 10.0f;

	// SceneCaptureComp->TextureTarget = 
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
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Information: Simulation Begin!."));
	positonInput = FVector::ZeroVector;

	//设置机器人运动Timer
	GetWorldTimerManager().SetTimer(RobotTimerHandle, this, &ARobotCharacter::RobotMotionTimer, fTimerPeriod, true);

	APlayerController* PlayerController1 = UGameplayStatics::GetPlayerController(GWorld, 0);
	PlayerController1->InputYawScale = 1.0;
}

// Called every frame
// 机器人运动一直待命
void ARobotCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	SetFOV();
}

void ARobotCharacter::RobotMotionTimer()
{
	//ReadRenderTargetToMat(RealTimeImage);
	if (bRobotMotionFlag) {
		// 控制底盘前进和后退
		Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
		//AddMovementInput(Direction, Sign(fTargetChassisGo) * fTimerPeriod * LineSpeed);
		//这个AddMovementInput(,X)实际移动的距离不是X，所以弃用这个函数，改用绝对坐标相加
		//因此机器人单次前进的运动精度为 TimerPeriod秒*LineSpeed厘米=0.01*20=0.2厘米，下文角速度精度同理
		FVector Cpos = RootComponent->GetComponentLocation();
		FVector Dpos = Direction * Sign(fTargetChassisGo) * fTimerPeriod * LineSpeed;
		RootComponent->SetWorldLocation(
			FVector(Cpos.X + Dpos.X, Cpos.Y + Dpos.Y, Cpos.Z + Dpos.Z));
		//底盘转动精度为0.01*10 = 0.1度
		AddControllerYawInput(Sign(fTargetChassisYaw) * fTimerPeriod * TurnSpeed);
		//云台旋转和俯仰转动精度为0.01*10 = 0.1度
		FRotator tempPTZPose = GimbalStaticMeshComp->GetRelativeRotation();
		tempPTZPose.Yaw += Sign(FTargetPTZAngle.Yaw) * fTimerPeriod * TurnSpeed;
		GimbalStaticMeshComp->SetRelativeRotation(tempPTZPose);

		tempPTZPose = CameraStaticMeshComp->GetRelativeRotation();
		tempPTZPose.Pitch += Sign(FTargetPTZAngle.Pitch) * fTimerPeriod * TurnSpeed;
		CameraStaticMeshComp->SetRelativeRotation(tempPTZPose);
		
		ChassisPosition = RootComponent->GetComponentLocation();
		PTZPose.Pitch = CameraStaticMeshComp->GetRelativeRotation().Pitch;
		PTZPose.Yaw = GimbalStaticMeshComp->GetRelativeRotation().Yaw;
		ChassisAngle = Controller->GetControlRotation();
	}
}

// Called to bind functionality to input
void ARobotCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// 轴映射
	PlayerInputComponent->BindAxis("MoveForward", this, &ARobotCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARobotCharacter::MoveRight);
	PlayerInputComponent->BindAxis("PTZPitch", this, &ARobotCharacter::PitchCamera);
	PlayerInputComponent->BindAxis("PTZYaw", this, &ARobotCharacter::YawCamera);
	// 操作映射
	PlayerInputComponent->BindAction("ManualMode", IE_Pressed, this, &ARobotCharacter::robotManualMode);
	PlayerInputComponent->BindAction("Stop", IE_Pressed, this, &ARobotCharacter::robotEmergency);
	PlayerInputComponent->BindAction("Test", IE_Pressed, this, &ARobotCharacter::testEveryThing);
	PlayerInputComponent->BindAction("PoseRe", IE_Pressed, this, &ARobotCharacter::PoseRelocalization);
	PlayerInputComponent->BindAction("GetPose", IE_Pressed, this, &ARobotCharacter::PrintRobotPoseOnScreen);
	PlayerInputComponent->BindAction("SetPose", IE_Pressed, this, &ARobotCharacter::InitialRobotPose);
}

// 机器人手动控制模式使能，bRobotManualFlag=1 可手动控制
void ARobotCharacter::robotManualMode()
{
	bManualFlag = !bManualFlag;
	bRobotMotionFlag = bManualFlag;
	if (bManualFlag) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Manual Mode On"));
	else GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Manual Mode Off"));
}

// 机器人急停和置零
void ARobotCharacter::robotEmergency()
{
	bRobotMotionFlag = FALSE;
	bManualFlag = FALSE;
	fTargetChassisGo = 0;
	fTargetChassisYaw = 0;
	FTargetPTZAngle = FRotator(0, 0, 0);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Robot Stop!"));
}


// 按键处于按下状态时 axisValue 的 正负值 决定机器人 运行方向
void ARobotCharacter::MoveForward(float AxisValue)
{
	if (bManualFlag) { // 备用
		fTargetChassisGo = AxisValue;
		ChassisPosition = RootComponent->GetComponentLocation();
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("x:%.1f y:%.1f\n Pitch=%.1f Yaw=%.1f"), 
			//ChassisPosition.X, ChassisPosition.Y, PTZPose.Pitch,PTZPose.Yaw));
	}
}

void ARobotCharacter::MoveRight(float AxisValue)
{
	if (bManualFlag) { // 备用
		fTargetChassisYaw = AxisValue;
	}
}

void ARobotCharacter::PitchCamera(float AxisValue)
{
	if (bManualFlag) { // 备用
		FTargetPTZAngle.Pitch = AxisValue;
	}
}

void ARobotCharacter::YawCamera(float AxisValue)
{
	if (bManualFlag) { // 备用
		FTargetPTZAngle.Yaw = AxisValue;
	}
}


/* 放置一些备用代码用来复制粘贴

void  ARobotCharacter::()
{
	FString str = FString::Printf(TEXT("%.3f"), double);
}

FTimerHandle TimerHandle;
GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
{
	
}, 3, false);

char [] = { "" };
FString  = TEXT("");

rtResource->ReadPixels(outBMP, readPixelFlags);

Mat tempImage(rt->GetSurfaceHeight(), rt->GetSurfaceWidth(), CV_8UC4, outBMP.GetData());
tempImage.copyTo(outImage);
char* result = TCHAR_TO_ANSI(*myFString);
*/

void ARobotCharacter::testEveryThing()
{
	if (cameraFOV > 10) {
		cameraFOV = 5.988;
	}
	else {
		cameraFOV = 54.733;
	}
}

// 获取机器人当前位姿并以消息框展示
void ARobotCharacter::PrintRobotPoseOnScreen()
{
	FString RobotPoseInfo;
	ChassisPosition = RootComponent->GetComponentLocation();
	RobotPoseInfo += FString::Printf(TEXT("x=%.3f \t y=%.3f \t z=%.3f\n"), ChassisPosition.X, ChassisPosition.Y, ChassisPosition.Z);

	FRotator tempPTZPose3 = Controller->GetControlRotation();
	RobotPoseInfo += FString::Printf(TEXT("Chassis(Yaw)=%.3f\n"), tempPTZPose3.Yaw);

	tempPTZPose3 = GimbalStaticMeshComp->GetRelativeRotation();
	RobotPoseInfo += FString::Printf(TEXT("Ry(Yaw)=%.3f\t"), tempPTZPose3.Yaw);

	tempPTZPose3 = CameraStaticMeshComp->GetRelativeRotation();
	RobotPoseInfo += FString::Printf(TEXT("Rx(Pitch)=%.3f\t"), tempPTZPose3.Pitch);


	FText const DialogTitle = FText::FromString("Robot Current Pose");
	FText const DialogText = FText::FromString(RobotPoseInfo);
	FMessageDialog::Open(EAppMsgType::Ok, DialogText, &DialogTitle);
}

// 设置机器人标定、初始误差位姿，弃用
void ARobotCharacter::InitialRobotPose()
{
	// 获取机器人当前的位姿为标定位姿
	// 初始位姿误差在 项目蓝图类BP_Character的属性里设置，默认为0，0，0
	cameraFOV = 54.733;
	FTimerHandle TimerHandle1;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle1, [&]()
		{
			FString imgPath = TEXT("E:\\3D_R\\UE4Model\\Robot_old\\PythonScripts\\CalibrationImage.png");
			SaveRenderTargetToFile(imgPath); // 存标定图像
			cameraFOV = 5.988;
			FTimerHandle TimerHandle2;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle2, [&]()
				{
					FString imgPath = TEXT("E:\\3D_R\\UE4Model\\Robot_old\\PythonScripts\\CalibrationImage_10x.png");
					SaveRenderTargetToFile(imgPath); // 存10倍焦距下的标定图像
					cameraFOV = 54.733;
					// 初始误差位姿，算法中的(x,y,z)= UE中的 (y,-z,x)
					ChassisPosition = RootComponent->GetComponentLocation();
					RootComponent->SetWorldLocation(
						FVector(ChassisPosition.X + InitialPosErr.X,
							ChassisPosition.Y + InitialPosErr.Y,
							ChassisPosition.Z + InitialPosErr.Z));
					FTimerHandle TimerHandle3;
					GetWorld()->GetTimerManager().SetTimer(TimerHandle3, [&]()
						{
							FString imgPath = TEXT("E:\\3D_R\\UE4Model\\Robot_old\\PythonScripts\\InitialImage.png");
							SaveRenderTargetToFile(imgPath); // 存初始误差图像
						}, 0.5, false);
				}, 0.5, false);
		}, 0.5, false);
}

// 弃用，机器人位姿重定位
void ARobotCharacter::PoseRelocalization()
{
	// APR重定位参数
	double PI_kp = 0.4, PI_ki = 0.04, EpsilonUV = 1.0;
	char CalibrationName[] = "E:\\3D_R\\UE4Model\\Robot_old\\PythonScripts\\CalibrationImage.png";
	char InitialName[] = "E:\\3D_R\\UE4Model\\Robot_old\\PythonScripts\\InitialImage.png";

	CalibrationImage = imread(CalibrationName);
	InitialImage = imread(InitialName);

	mycvObject testobject(CalibrationImage, InitialImage);
	testobject.PoseEstimation(Homo, RotAngle, Tc, PixelDev);

	/*IterationOfMethod = 0;

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("image registrating...")));
	testobject.PoseEstimation(Homo, delta_R, delta_t, PixelDev);
	if (CalibrationImage.size > 0) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue,
		FString::Printf(TEXT("Rx:%.3f Ry:%.3f Rz:%.3f Du: %.2f Dv: %.2f"),
			delta_R.x, delta_R.y, delta_R.z,PixelDev.x, PixelDev.y));
	double transTime = 5.f;
	fTargetChassisGo = 1;
	bRobotMotionFlag = TRUE;
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
			FString imgPath = TEXT("E:\\3D_R\\UE4Model\\Robot_old\\PythonScripts\\ZoomImage.png");
			SaveRenderTargetToFile(imgPath);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Delay Finished Called"));
			fTargetChassisGo = 0;
		}, 3, false);*/

}

void ARobotCharacter::SetFOV()
{
	FMinimalViewInfo cameraInfo;
	SceneCaptureComp->GetCameraView(1.f, cameraInfo);
	cameraInfo.FOV = cameraFOV;
	SceneCaptureComp->SetCameraView(cameraInfo);
}

void ARobotCharacter::MyDelay(UObject* WorldContextObject, float Duration)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject,
		EGetWorldErrorMode::LogAndReturnNull)) {
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = WorldContextObject;
		LatentInfo.ExecutionFunction = TEXT("DelayFinished");
		LatentInfo.Linkage = 0;
		LatentInfo.UUID = FMath::Rand();
		LatentActionManager.AddNewAction(WorldContextObject, LatentInfo.UUID,
			new FDelayAction(Duration, LatentInfo));
	}
}

void ARobotCharacter::DelayFinished()
{
	FString imgPath = TEXT("E:\\3D_R\\UE4Model\\Robot_old\\PythonScripts\\ZoomImage.png");
	SaveRenderTargetToFile(imgPath);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Delay Finished Called"));
	fTargetChassisGo = 0;
}


/**************************************************
// 以下函数专门提供给蓝图类调用
// Author: JQ
// Date: 2022/04/23
*****************************************************/
// 蓝图用函数：读实时图片到RealTimeImage (cv::Mat)
void ARobotCharacter::ReadRenderTargetToMat()
{
	UTextureRenderTarget2D* rt = SceneCaptureComp->TextureTarget;
	FTextureRenderTargetResource* rtResource = rt->GameThread_GetRenderTargetResource();
	FReadSurfaceDataFlags readPixelFlags(RCM_UNorm);
	TArray<FColor> outBMP;

	rtResource->ReadPixels(outBMP, readPixelFlags);

	Mat tempImage(rt->GetSurfaceHeight(), rt->GetSurfaceWidth(), CV_8UC4, outBMP.GetData());
	tempImage.copyTo(RealTimeImage);
}

// 蓝图用函数：保存图片到输入路径
void ARobotCharacter::SaveRenderTargetToFile(const FString& fileDestination)
{
	UTextureRenderTarget2D* rt = SceneCaptureComp->TextureTarget;
	FTextureRenderTargetResource* rtResource = rt->GameThread_GetRenderTargetResource();
	FReadSurfaceDataFlags readPixelFlags(RCM_UNorm);
	TArray<FColor> outBMP;

	for (FColor& color : outBMP)
	{
		color.A = 255;
	}
	outBMP.AddUninitialized(rt->GetSurfaceWidth() * rt->GetSurfaceHeight());
	rtResource->ReadPixels(outBMP, readPixelFlags);

	FIntPoint destSize(rt->GetSurfaceWidth(), rt->GetSurfaceHeight());
	TArray<uint8> CompressedBitmap;
	FImageUtils::CompressImageArray(destSize.X, destSize.Y, outBMP, CompressedBitmap);
	bool imageSavedOk = FFileHelper::SaveArrayToFile(CompressedBitmap, *fileDestination);
	if (imageSavedOk) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Image Saved"));
}

// 蓝图用函数：APR & ACR位姿误差分解
void ARobotCharacter::PoseErrorDecomposition()
{
	//迭代次数+1
	IterationOfMethod++;
	char* result = TCHAR_TO_ANSI(*CalibrationImgPath1x);
	CalibrationImage = imread(result);
	mycvObject testobject(CalibrationImage, RealTimeImage);
	testobject.PoseEstimation(Homo, RotAngle, Tc, PixelDev);
	PixelDeviation.X = PixelDev.x;
	PixelDeviation.Y = PixelDev.y;
	RotationDeviationAngle.Roll = RotAngle.x;
	RotationDeviationAngle.Pitch = RotAngle.y;
	RotationDeviationAngle.Yaw = RotAngle.z;
	// 相机坐标系的平移向量，坐标系系统是论文规定的方向，与虚幻的坐标系规定是不同的！
	CameraTranslationVector.X = Tc.x; 
	CameraTranslationVector.Y = Tc.y;
	CameraTranslationVector.Z = Tc.z;
	// 底盘坐标系的平移向量，坐标系系统是论文规定的方向，与虚幻的坐标系规定是不同的！Yaw是theta y, Pitch是theta x
	ChassisTranslationVector.X = Tc.x * cos(PTZPose.Yaw) + Tc.y * sin(PTZPose.Pitch) * sin(PTZPose.Yaw) +
		Tc.z * cos(PTZPose.Pitch) * sin(PTZPose.Yaw);
	ChassisTranslationVector.Y = 0;
	ChassisTranslationVector.Z = -Tc.x * sin(PTZPose.Yaw) + Tc.y * sin(PTZPose.Pitch) * cos(PTZPose.Yaw) +
		Tc.z * cos(PTZPose.Pitch) * cos(PTZPose.Yaw);
}

// 蓝图用函数：计算CRP调节所需的位姿量
void ARobotCharacter::CRPPoseErrorDecompostion(bool bIsFirstFrame)
{
	IterationOfMethod++;
	if (bIsFirstFrame) {// 第一帧
		char* result1 = TCHAR_TO_ANSI(*CalibrationImgPath1x);
		CalibrationImage = imread(result1);
		char* result2 = TCHAR_TO_ANSI(*InitialImgPath);
		InitialImage = imread(result2);
		mycvObject testobject(CalibrationImage, InitialImage);
		testobject.PoseEstimationMatrix(Homo, Rotation10, Translation10, ImgDepth10);

		Point3d tempTc;
		tempTc.x = Translation10.at<double>(0, 0);
		tempTc.y = Translation10.at<double>(1, 0);
		tempTc.z = Translation10.at<double>(2, 0);
		// 底盘坐标系的平移向量，坐标系系统是论文规定的方向，与虚幻的坐标系规定是不同的！Yaw是theta y, Pitch是theta x
		ChassisTranslationVector.X = tempTc.x * cos(PTZPose.Yaw) + 
			tempTc.y * sin(PTZPose.Pitch) * sin(PTZPose.Yaw) +
			tempTc.z * cos(PTZPose.Pitch) * sin(PTZPose.Yaw);
		ChassisTranslationVector.Y = 0;
		ChassisTranslationVector.Z = -tempTc.x * sin(PTZPose.Yaw) + 
			tempTc.y * sin(PTZPose.Pitch) * cos(PTZPose.Yaw) +
			tempTc.z * cos(PTZPose.Pitch) * cos(PTZPose.Yaw);
	}
	else {
		Mat Rotation1n;
		Mat Translation1n;
		Mat Translation0n;
		double ImgDepth1n;
		mycvObject testobject(CalibrationImage, RealTimeImage);
		testobject.PoseEstimationMatrix(Homo, Rotation1n, Translation1n, ImgDepth1n);
		// CRP的平移向量计算方式，通过第一帧、当前帧、标定帧之间的图像深度来校正平移尺度的真实比例
		Translation0n = ImgDepth1n * Translation1n -
			ImgDepth10 * Rotation1n * Rotation10.inv() * Translation10;

		Point3d tempTc;
		tempTc.x = Translation0n.at<double>(0, 0);
		tempTc.y = Translation0n.at<double>(1, 0);
		tempTc.z = Translation0n.at<double>(2, 0);
		// 底盘坐标系的平移向量，坐标系系统是论文规定的方向，与虚幻的坐标系规定是不同的！Yaw是theta y, Pitch是theta x
		ChassisTranslationVector.X = tempTc.x * cos(PTZPose.Yaw) +
			tempTc.y * sin(PTZPose.Pitch) * sin(PTZPose.Yaw) +
			tempTc.z * cos(PTZPose.Pitch) * sin(PTZPose.Yaw);
		ChassisTranslationVector.Y = 0;
		ChassisTranslationVector.Z = -tempTc.x * sin(PTZPose.Yaw) +
			tempTc.y * sin(PTZPose.Pitch) * cos(PTZPose.Yaw) +
			tempTc.z * cos(PTZPose.Pitch) * cos(PTZPose.Yaw);
	}
}

// 蓝图用函数：机器人底盘先转动特定角度然后前进特定距离
void ARobotCharacter::RobotTurnThenGoVector(FVector2D TurnXZVector, float GoDistance)
{
	bRobotMotionFlag = TRUE;
	// 以下判定平移向量处于坐标轴上的情况
	if ( (TurnXZVector.X == 0) && (TurnXZVector.Y == 0)) {
		TurnAngle = 0;
		fTurnDirection = StopRobot;
		fGoDirection = Sign(GoDistance);
	}
	else if (TurnXZVector.Y == 0) {
		TurnAngle = 90.0;
		fGoDirection = GoForward;
		if (TurnXZVector.X > 0) fTurnDirection = TurnRight;
		else fTurnDirection = TurnLeft;
	}
	else if (TurnXZVector.X == 0) {
		TurnAngle = 0.0;
		fTurnDirection = StopRobot;
		if (TurnXZVector.Y > 0) fGoDirection = GoForward;
		else fGoDirection = GoBackward;
	}
	// 以下判定平移向量处于四个象限内的情况
	else {
		TurnAngle = 180 / PI * atan(TurnXZVector.X / TurnXZVector.Y);
		// 判断二维平移角度所在的象限，通过底盘前进或后退来减少底盘180度的反向旋转量
		if (Sign(TurnXZVector.X) * Sign(TurnXZVector.Y) > 0) fTurnDirection = TurnRight; //一三象限向右转
		else if (Sign(TurnXZVector.X) * Sign(TurnXZVector.Y) < 0) fTurnDirection = TurnLeft; //二、四象限向左转

		if (TurnXZVector.Y > 0) fGoDirection = GoForward; // 一、二象限前进
		else if (TurnXZVector.Y < 0) fGoDirection = GoBackward; // 三、四象限后退
	}
	TurnTime = abs(TurnAngle) / TurnSpeed;
	GoTime = abs(GoDistance) / LineSpeed;

	if (TurnTime >= 0.001) {// 如果转动角度不为0，则先转动后直走
		fTargetChassisYaw = fTurnDirection; // 开转
		FTargetPTZAngle.Yaw = 0 - fTurnDirection;//为保持相机视野不变，云台应该与底盘转动相反的方向
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
			{
				fTargetChassisYaw = StopRobot; // 停转
				FTargetPTZAngle.Yaw = StopRobot;;
				fTargetChassisGo = fGoDirection; // 开走
				FTimerHandle TimerHandle2;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle2, [&]()
					{
						fTargetChassisGo = StopRobot;//停走
					}, GoTime, false);
			}, TurnTime, false);
	}
	else {
			fTargetChassisGo = fGoDirection; // 开走
			FTimerHandle TimerHandle2;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle2, [&]()
				{
					fTargetChassisGo = StopRobot;//停走
				}, GoTime, false);

	}	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue,
		FString::Printf(TEXT("Iteration %d, Wait for :%.3f(s)\nTh_x=%.3f, Th_z=%.3f\nAngle=%.3f\tGoDistance=%.3f"),
			IterationOfMethod, TurnTime + GoTime, TurnXZVector.X, TurnXZVector.Y,
			TurnAngle, GoDistance));
}

// 蓝图用函数：机器人底盘转动特定角度
void ARobotCharacter::RobotTurnThenGo(float Angle, float GoDistance)
{
	bRobotMotionFlag = TRUE;
	TurnTime = abs(Angle) / TurnSpeed;
	GoTime = abs(GoDistance) / LineSpeed;
	fGoDirection = Sign(GoDistance);
	fTurnDirection = Sign(Angle);

	if (abs(Angle) >= 0.1) {// 如果转动角度不为0，则先转动后直走
		fTargetChassisYaw = fTurnDirection; // 开转
		FTargetPTZAngle.Yaw = 0 - fTurnDirection;

		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
			{
				fTargetChassisYaw = StopRobot; // 停转
				FTargetPTZAngle.Yaw = StopRobot;
				if (fGoDirection != 0) {
					fTargetChassisGo = fGoDirection; // 开走
					FTimerHandle TimerHandle2;
					GetWorld()->GetTimerManager().SetTimer(TimerHandle2, [&]()
						{
							fTargetChassisGo = StopRobot;//停走
						}, GoTime, false);
				}
			}, TurnTime, false);
	}
	else { // 否则直接开走
		fTargetChassisGo = fGoDirection; // 开走
		FTimerHandle TimerHandle2;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle2, [&]()
			{
				fTargetChassisGo = StopRobot;//停走
			}, GoTime, false);
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue,
		FString::Printf(TEXT("Iteration %d, Delta_U=%.3f, Delta_V=%.3f, Wait for :%.3f(s)\nAngle=%.3f\tGoDistance=%.3f"),
			IterationOfMethod, PixelDeviation.X, PixelDeviation.Y, TurnTime + GoTime,
			Angle, GoDistance));
}

// 蓝图用函数：设置机器人标定位姿
void ARobotCharacter::GetCalibrationRobotPose()
{
	CalibrationPosition = ChassisPosition;
	CalibrationPTZAngle = PTZPose;
	CalibrationChassisAngle = ChassisAngle;
}

// 蓝图用函数：重定位结束，显示重定位以后的位姿误差
void ARobotCharacter::PositionErrorComputation()
{
	float xError = CalibrationPosition.X - ChassisPosition.X;
	float yError = CalibrationPosition.Y - ChassisPosition.Y;
	float zError = CalibrationPosition.Z - ChassisPosition.Z;
	PRPostionError = sqrt(pow(xError, 2) + pow(yError, 2) + pow(zError, 2));
	//机器人底盘转回标定朝向角度
	float tempChassisAngle1 = fmod( CalibrationChassisAngle.Yaw >= 0 ? 
		CalibrationChassisAngle.Yaw : (360 + CalibrationChassisAngle.Yaw), 360.0);
	float tempChassisAngle2 = fmod( ChassisAngle.Yaw >= 0 ? ChassisAngle.Yaw : (360 + ChassisAngle.Yaw), 360.0);
	float DeltaChassisAngle = tempChassisAngle1 - tempChassisAngle2;

	float ResumeChassisAngle;
	if (DeltaChassisAngle <= 0) {
		ResumeChassisAngle = (abs(DeltaChassisAngle) >= 180 ? (360-abs(DeltaChassisAngle)):DeltaChassisAngle);
	}
	else {
		ResumeChassisAngle = (DeltaChassisAngle >= 180 ? (DeltaChassisAngle - 360) : DeltaChassisAngle);
	}
	//float cancelTime = abs(ResumeChassisAngle) / TurnSpeed;
	float cancelTime = 0;
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
	//	FString::Printf(TEXT("Cal.Yaw=%.3f Cur.Yaw=%.3f Del=%.3f Res=%.3f"),
	//		tempChassisAngle1, tempChassisAngle2, DeltaChassisAngle, ResumeChassisAngle));

	RobotTurnThenGo(ResumeChassisAngle, 0);
	FTimerHandle TimerHandle_Over;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Over, [&]()
		{// 注意！计时器的响应代码段不要有外部的局部变量，应该全设置为类成员变量，
		 // 因为计时器是单独的线程，外部的局部变量等到计时器触发响应时已经被销毁，
		 // 否则和你的期望效果不太一样
			FString PoseErrorInfo;
			PoseErrorInfo = FString::Printf(TEXT("Delta_Th = (%.3f, %.3f, %.3f)\nDistance Error = %.3f\nDelta_U=%.3f, Delta_V=%.3f\nIteration Number = %d\nRunTime=%.3f"),
				CalibrationPosition.X - ChassisPosition.X, CalibrationPosition.Y - ChassisPosition.Y,
				CalibrationPosition.Z - ChassisPosition.Z,
				PRPostionError, PixelDeviation.X, PixelDeviation.Y, IterationOfMethod,RunTime);

			FText const DialogTitle = FText::FromString("Pose Relocalization Completed");
			FText const DialogText = FText::FromString(PoseErrorInfo);
			FMessageDialog::Open(EAppMsgType::Ok, DialogText, &DialogTitle);
			IterationOfMethod = 0; // 迭代次数置零
		}, cancelTime + 0.5, false);
}

// 蓝图用函数：初始化机器人到初始误差位姿
void ARobotCharacter::RobotPoseInitialize()
{
	RootComponent->SetWorldLocation(
		FVector(CalibrationPosition.X + InitialPosErr.X,
			CalibrationPosition.Y + InitialPosErr.Y,
			CalibrationPosition.Z + InitialPosErr.Z));
	FRotator tempPTZPose = GimbalStaticMeshComp->GetRelativeRotation();
	tempPTZPose.Yaw = CalibrationPTZAngle.Yaw;
	GimbalStaticMeshComp->SetRelativeRotation(tempPTZPose);
	
	tempPTZPose = CameraStaticMeshComp->GetRelativeRotation();
	tempPTZPose.Pitch = CalibrationPTZAngle.Pitch;
	CameraStaticMeshComp->SetRelativeRotation(tempPTZPose);
	Controller->SetControlRotation(CalibrationChassisAngle);
	IterationOfMethod = 0;
}

// 蓝图用函数：生成正态分布随机数
float ARobotCharacter::GaussianRandomNumber(float mean, float std)
{
	static float V1, V2, S;
	static int phase = 0;
	float X;

	if (phase == 0) {
		do {
			float U1 = (float)rand() / RAND_MAX;
			float U2 = (float)rand() / RAND_MAX;

			V1 = 2 * U1 - 1;
			V2 = 2 * U2 - 1;
			S = V1 * V1 + V2 * V2;
		} while (S >= 1 || S == 0);

		X = V1 * sqrt(-2 * log(S) / S);
	}
	else
		X = V2 * sqrt(-2 * log(S) / S);

	phase = 1 - phase;

	return X * std + mean;
}

// 蓝图用函数：数学符号函数
float ARobotCharacter::Sign(float number)
{
	if (number > 0) return 1.f;
	else if (number < 0) return -1.f;
	else return 0;
}

// 蓝图用函数：对话框打印消息
void ARobotCharacter::PrintTextInDialog(FString DialogTitle, FString DialogMessage)
{
	FText const tempTitle = FText::FromString(DialogTitle);
	FText const tempText = FText::FromString(DialogMessage);
	FMessageDialog::Open(EAppMsgType::Ok, tempText, &tempTitle);
}

// 蓝图用函数：设置机器人到指定位置和朝向角度、云台角度
void ARobotCharacter::SetRobotPositionAndPose()
{
	bRobotMotionFlag = FALSE;
	RootComponent->SetWorldLocation(CalibrationPosition);
	FRotator tempPTZPose1 = GimbalStaticMeshComp->GetRelativeRotation();
	tempPTZPose1.Yaw = CalibrationPTZAngle.Yaw;
	GimbalStaticMeshComp->SetRelativeRotation(tempPTZPose1);
	tempPTZPose1 = CameraStaticMeshComp->GetRelativeRotation();
	tempPTZPose1.Pitch = CalibrationPTZAngle.Pitch;
	CameraStaticMeshComp->SetRelativeRotation(tempPTZPose1);
	Controller->SetControlRotation(CalibrationChassisAngle);
}