// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Robot/RobotCharacter.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRobotCharacter() {}
// Cross Module References
	ROBOT_API UClass* Z_Construct_UClass_ARobotCharacter_NoRegister();
	ROBOT_API UClass* Z_Construct_UClass_ARobotCharacter();
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	UPackage* Z_Construct_UPackage__Script_Robot();
	ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
// End Cross Module References
	void ARobotCharacter::StaticRegisterNativesARobotCharacter()
	{
	}
	UClass* Z_Construct_UClass_ARobotCharacter_NoRegister()
	{
		return ARobotCharacter::StaticClass();
	}
	struct Z_Construct_UClass_ARobotCharacter_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SpringArmComp_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_SpringArmComp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CameraComp_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_CameraComp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FirstPersonCameraComp_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_FirstPersonCameraComp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_StaticMeshComp_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_StaticMeshComp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_positonOutput_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_positonOutput;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_positonInput_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_positonInput;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ARobotCharacter_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_Robot,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARobotCharacter_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "RobotCharacter.h" },
		{ "ModuleRelativePath", "RobotCharacter.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARobotCharacter_Statics::NewProp_SpringArmComp_MetaData[] = {
		{ "Category", "RobotCharacter" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "RobotCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARobotCharacter_Statics::NewProp_SpringArmComp = { "SpringArmComp", nullptr, (EPropertyFlags)0x0020080000080009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ARobotCharacter, SpringArmComp), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ARobotCharacter_Statics::NewProp_SpringArmComp_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARobotCharacter_Statics::NewProp_SpringArmComp_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARobotCharacter_Statics::NewProp_CameraComp_MetaData[] = {
		{ "Category", "RobotCharacter" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "RobotCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARobotCharacter_Statics::NewProp_CameraComp = { "CameraComp", nullptr, (EPropertyFlags)0x0020080000080009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ARobotCharacter, CameraComp), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ARobotCharacter_Statics::NewProp_CameraComp_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARobotCharacter_Statics::NewProp_CameraComp_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARobotCharacter_Statics::NewProp_FirstPersonCameraComp_MetaData[] = {
		{ "Category", "RobotCharacter" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "RobotCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARobotCharacter_Statics::NewProp_FirstPersonCameraComp = { "FirstPersonCameraComp", nullptr, (EPropertyFlags)0x0020080000080009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ARobotCharacter, FirstPersonCameraComp), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ARobotCharacter_Statics::NewProp_FirstPersonCameraComp_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARobotCharacter_Statics::NewProp_FirstPersonCameraComp_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARobotCharacter_Statics::NewProp_StaticMeshComp_MetaData[] = {
		{ "Category", "RobotCharacter" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "RobotCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARobotCharacter_Statics::NewProp_StaticMeshComp = { "StaticMeshComp", nullptr, (EPropertyFlags)0x0020080000080009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ARobotCharacter, StaticMeshComp), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ARobotCharacter_Statics::NewProp_StaticMeshComp_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARobotCharacter_Statics::NewProp_StaticMeshComp_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARobotCharacter_Statics::NewProp_positonOutput_MetaData[] = {
		{ "Category", "Robot Info" },
		{ "ModuleRelativePath", "RobotCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ARobotCharacter_Statics::NewProp_positonOutput = { "positonOutput", nullptr, (EPropertyFlags)0x0010000000022015, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ARobotCharacter, positonOutput), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UClass_ARobotCharacter_Statics::NewProp_positonOutput_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARobotCharacter_Statics::NewProp_positonOutput_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARobotCharacter_Statics::NewProp_positonInput_MetaData[] = {
		{ "Category", "Robot Info" },
		{ "ModuleRelativePath", "RobotCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ARobotCharacter_Statics::NewProp_positonInput = { "positonInput", nullptr, (EPropertyFlags)0x0010000000022015, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ARobotCharacter, positonInput), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UClass_ARobotCharacter_Statics::NewProp_positonInput_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARobotCharacter_Statics::NewProp_positonInput_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ARobotCharacter_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARobotCharacter_Statics::NewProp_SpringArmComp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARobotCharacter_Statics::NewProp_CameraComp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARobotCharacter_Statics::NewProp_FirstPersonCameraComp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARobotCharacter_Statics::NewProp_StaticMeshComp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARobotCharacter_Statics::NewProp_positonOutput,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARobotCharacter_Statics::NewProp_positonInput,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ARobotCharacter_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ARobotCharacter>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ARobotCharacter_Statics::ClassParams = {
		&ARobotCharacter::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ARobotCharacter_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ARobotCharacter_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ARobotCharacter_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ARobotCharacter_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ARobotCharacter()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ARobotCharacter_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ARobotCharacter, 4112782282);
	template<> ROBOT_API UClass* StaticClass<ARobotCharacter>()
	{
		return ARobotCharacter::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ARobotCharacter(Z_Construct_UClass_ARobotCharacter, &ARobotCharacter::StaticClass, TEXT("/Script/Robot"), TEXT("ARobotCharacter"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ARobotCharacter);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
