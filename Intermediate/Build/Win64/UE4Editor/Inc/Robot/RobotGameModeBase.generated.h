// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef ROBOT_RobotGameModeBase_generated_h
#error "RobotGameModeBase.generated.h already included, missing '#pragma once' in RobotGameModeBase.h"
#endif
#define ROBOT_RobotGameModeBase_generated_h

#define Robot_Source_Robot_RobotGameModeBase_h_15_SPARSE_DATA
#define Robot_Source_Robot_RobotGameModeBase_h_15_RPC_WRAPPERS
#define Robot_Source_Robot_RobotGameModeBase_h_15_RPC_WRAPPERS_NO_PURE_DECLS
#define Robot_Source_Robot_RobotGameModeBase_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesARobotGameModeBase(); \
	friend struct Z_Construct_UClass_ARobotGameModeBase_Statics; \
public: \
	DECLARE_CLASS(ARobotGameModeBase, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/Robot"), NO_API) \
	DECLARE_SERIALIZER(ARobotGameModeBase)


#define Robot_Source_Robot_RobotGameModeBase_h_15_INCLASS \
private: \
	static void StaticRegisterNativesARobotGameModeBase(); \
	friend struct Z_Construct_UClass_ARobotGameModeBase_Statics; \
public: \
	DECLARE_CLASS(ARobotGameModeBase, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/Robot"), NO_API) \
	DECLARE_SERIALIZER(ARobotGameModeBase)


#define Robot_Source_Robot_RobotGameModeBase_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ARobotGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ARobotGameModeBase) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ARobotGameModeBase); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ARobotGameModeBase); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ARobotGameModeBase(ARobotGameModeBase&&); \
	NO_API ARobotGameModeBase(const ARobotGameModeBase&); \
public:


#define Robot_Source_Robot_RobotGameModeBase_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ARobotGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ARobotGameModeBase(ARobotGameModeBase&&); \
	NO_API ARobotGameModeBase(const ARobotGameModeBase&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ARobotGameModeBase); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ARobotGameModeBase); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ARobotGameModeBase)


#define Robot_Source_Robot_RobotGameModeBase_h_15_PRIVATE_PROPERTY_OFFSET
#define Robot_Source_Robot_RobotGameModeBase_h_12_PROLOG
#define Robot_Source_Robot_RobotGameModeBase_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Robot_Source_Robot_RobotGameModeBase_h_15_PRIVATE_PROPERTY_OFFSET \
	Robot_Source_Robot_RobotGameModeBase_h_15_SPARSE_DATA \
	Robot_Source_Robot_RobotGameModeBase_h_15_RPC_WRAPPERS \
	Robot_Source_Robot_RobotGameModeBase_h_15_INCLASS \
	Robot_Source_Robot_RobotGameModeBase_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Robot_Source_Robot_RobotGameModeBase_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Robot_Source_Robot_RobotGameModeBase_h_15_PRIVATE_PROPERTY_OFFSET \
	Robot_Source_Robot_RobotGameModeBase_h_15_SPARSE_DATA \
	Robot_Source_Robot_RobotGameModeBase_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	Robot_Source_Robot_RobotGameModeBase_h_15_INCLASS_NO_PURE_DECLS \
	Robot_Source_Robot_RobotGameModeBase_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> ROBOT_API UClass* StaticClass<class ARobotGameModeBase>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Robot_Source_Robot_RobotGameModeBase_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
