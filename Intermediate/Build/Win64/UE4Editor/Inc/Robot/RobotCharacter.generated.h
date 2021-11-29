// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef ROBOT_RobotCharacter_generated_h
#error "RobotCharacter.generated.h already included, missing '#pragma once' in RobotCharacter.h"
#endif
#define ROBOT_RobotCharacter_generated_h

#define Robot_Source_Robot_RobotCharacter_h_12_SPARSE_DATA
#define Robot_Source_Robot_RobotCharacter_h_12_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execMoveRight); \
	DECLARE_FUNCTION(execMoveForward);


#define Robot_Source_Robot_RobotCharacter_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execMoveRight); \
	DECLARE_FUNCTION(execMoveForward);


#define Robot_Source_Robot_RobotCharacter_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesARobotCharacter(); \
	friend struct Z_Construct_UClass_ARobotCharacter_Statics; \
public: \
	DECLARE_CLASS(ARobotCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Robot"), NO_API) \
	DECLARE_SERIALIZER(ARobotCharacter)


#define Robot_Source_Robot_RobotCharacter_h_12_INCLASS \
private: \
	static void StaticRegisterNativesARobotCharacter(); \
	friend struct Z_Construct_UClass_ARobotCharacter_Statics; \
public: \
	DECLARE_CLASS(ARobotCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Robot"), NO_API) \
	DECLARE_SERIALIZER(ARobotCharacter)


#define Robot_Source_Robot_RobotCharacter_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ARobotCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ARobotCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ARobotCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ARobotCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ARobotCharacter(ARobotCharacter&&); \
	NO_API ARobotCharacter(const ARobotCharacter&); \
public:


#define Robot_Source_Robot_RobotCharacter_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ARobotCharacter(ARobotCharacter&&); \
	NO_API ARobotCharacter(const ARobotCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ARobotCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ARobotCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ARobotCharacter)


#define Robot_Source_Robot_RobotCharacter_h_12_PRIVATE_PROPERTY_OFFSET
#define Robot_Source_Robot_RobotCharacter_h_9_PROLOG
#define Robot_Source_Robot_RobotCharacter_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Robot_Source_Robot_RobotCharacter_h_12_PRIVATE_PROPERTY_OFFSET \
	Robot_Source_Robot_RobotCharacter_h_12_SPARSE_DATA \
	Robot_Source_Robot_RobotCharacter_h_12_RPC_WRAPPERS \
	Robot_Source_Robot_RobotCharacter_h_12_INCLASS \
	Robot_Source_Robot_RobotCharacter_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Robot_Source_Robot_RobotCharacter_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Robot_Source_Robot_RobotCharacter_h_12_PRIVATE_PROPERTY_OFFSET \
	Robot_Source_Robot_RobotCharacter_h_12_SPARSE_DATA \
	Robot_Source_Robot_RobotCharacter_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	Robot_Source_Robot_RobotCharacter_h_12_INCLASS_NO_PURE_DECLS \
	Robot_Source_Robot_RobotCharacter_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> ROBOT_API UClass* StaticClass<class ARobotCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Robot_Source_Robot_RobotCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
