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
// End Cross Module References
	DEFINE_FUNCTION(ARobotCharacter::execMoveRight)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->MoveRight(Z_Param_Value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ARobotCharacter::execMoveForward)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->MoveForward(Z_Param_Value);
		P_NATIVE_END;
	}
	void ARobotCharacter::StaticRegisterNativesARobotCharacter()
	{
		UClass* Class = ARobotCharacter::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "MoveForward", &ARobotCharacter::execMoveForward },
			{ "MoveRight", &ARobotCharacter::execMoveRight },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ARobotCharacter_MoveForward_Statics
	{
		struct RobotCharacter_eventMoveForward_Parms
		{
			float Value;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ARobotCharacter_MoveForward_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(RobotCharacter_eventMoveForward_Parms, Value), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ARobotCharacter_MoveForward_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ARobotCharacter_MoveForward_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ARobotCharacter_MoveForward_Statics::Function_MetaDataParams[] = {
		{ "Comment", "// Handles input for moving forward and backward.\n" },
		{ "ModuleRelativePath", "RobotCharacter.h" },
		{ "ToolTip", "Handles input for moving forward and backward." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ARobotCharacter_MoveForward_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ARobotCharacter, nullptr, "MoveForward", nullptr, nullptr, sizeof(RobotCharacter_eventMoveForward_Parms), Z_Construct_UFunction_ARobotCharacter_MoveForward_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ARobotCharacter_MoveForward_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ARobotCharacter_MoveForward_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ARobotCharacter_MoveForward_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ARobotCharacter_MoveForward()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ARobotCharacter_MoveForward_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ARobotCharacter_MoveRight_Statics
	{
		struct RobotCharacter_eventMoveRight_Parms
		{
			float Value;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ARobotCharacter_MoveRight_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(RobotCharacter_eventMoveRight_Parms, Value), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ARobotCharacter_MoveRight_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ARobotCharacter_MoveRight_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ARobotCharacter_MoveRight_Statics::Function_MetaDataParams[] = {
		{ "Comment", "// Handles input for moving right and left.\n" },
		{ "ModuleRelativePath", "RobotCharacter.h" },
		{ "ToolTip", "Handles input for moving right and left." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ARobotCharacter_MoveRight_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ARobotCharacter, nullptr, "MoveRight", nullptr, nullptr, sizeof(RobotCharacter_eventMoveRight_Parms), Z_Construct_UFunction_ARobotCharacter_MoveRight_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ARobotCharacter_MoveRight_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ARobotCharacter_MoveRight_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ARobotCharacter_MoveRight_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ARobotCharacter_MoveRight()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ARobotCharacter_MoveRight_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ARobotCharacter_NoRegister()
	{
		return ARobotCharacter::StaticClass();
	}
	struct Z_Construct_UClass_ARobotCharacter_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ARobotCharacter_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_Robot,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ARobotCharacter_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ARobotCharacter_MoveForward, "MoveForward" }, // 2120891811
		{ &Z_Construct_UFunction_ARobotCharacter_MoveRight, "MoveRight" }, // 3475379962
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARobotCharacter_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "RobotCharacter.h" },
		{ "ModuleRelativePath", "RobotCharacter.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ARobotCharacter_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ARobotCharacter>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ARobotCharacter_Statics::ClassParams = {
		&ARobotCharacter::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
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
	IMPLEMENT_CLASS(ARobotCharacter, 1470467065);
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
