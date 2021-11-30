// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef ROBOT_RobotPawn_generated_h
#error "RobotPawn.generated.h already included, missing '#pragma once' in RobotPawn.h"
#endif
#define ROBOT_RobotPawn_generated_h

#define Robot_Source_Robot_RobotPawn_h_14_SPARSE_DATA
#define Robot_Source_Robot_RobotPawn_h_14_RPC_WRAPPERS
#define Robot_Source_Robot_RobotPawn_h_14_RPC_WRAPPERS_NO_PURE_DECLS
#define Robot_Source_Robot_RobotPawn_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesARobotPawn(); \
	friend struct Z_Construct_UClass_ARobotPawn_Statics; \
public: \
	DECLARE_CLASS(ARobotPawn, APawn, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Robot"), NO_API) \
	DECLARE_SERIALIZER(ARobotPawn)


#define Robot_Source_Robot_RobotPawn_h_14_INCLASS \
private: \
	static void StaticRegisterNativesARobotPawn(); \
	friend struct Z_Construct_UClass_ARobotPawn_Statics; \
public: \
	DECLARE_CLASS(ARobotPawn, APawn, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Robot"), NO_API) \
	DECLARE_SERIALIZER(ARobotPawn)


#define Robot_Source_Robot_RobotPawn_h_14_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ARobotPawn(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ARobotPawn) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ARobotPawn); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ARobotPawn); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ARobotPawn(ARobotPawn&&); \
	NO_API ARobotPawn(const ARobotPawn&); \
public:


#define Robot_Source_Robot_RobotPawn_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ARobotPawn(ARobotPawn&&); \
	NO_API ARobotPawn(const ARobotPawn&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ARobotPawn); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ARobotPawn); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ARobotPawn)


#define Robot_Source_Robot_RobotPawn_h_14_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__SpringArmComp() { return STRUCT_OFFSET(ARobotPawn, SpringArmComp); } \
	FORCEINLINE static uint32 __PPO__CameraComp() { return STRUCT_OFFSET(ARobotPawn, CameraComp); } \
	FORCEINLINE static uint32 __PPO__StaticMeshComp() { return STRUCT_OFFSET(ARobotPawn, StaticMeshComp); }


#define Robot_Source_Robot_RobotPawn_h_11_PROLOG
#define Robot_Source_Robot_RobotPawn_h_14_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Robot_Source_Robot_RobotPawn_h_14_PRIVATE_PROPERTY_OFFSET \
	Robot_Source_Robot_RobotPawn_h_14_SPARSE_DATA \
	Robot_Source_Robot_RobotPawn_h_14_RPC_WRAPPERS \
	Robot_Source_Robot_RobotPawn_h_14_INCLASS \
	Robot_Source_Robot_RobotPawn_h_14_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Robot_Source_Robot_RobotPawn_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Robot_Source_Robot_RobotPawn_h_14_PRIVATE_PROPERTY_OFFSET \
	Robot_Source_Robot_RobotPawn_h_14_SPARSE_DATA \
	Robot_Source_Robot_RobotPawn_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	Robot_Source_Robot_RobotPawn_h_14_INCLASS_NO_PURE_DECLS \
	Robot_Source_Robot_RobotPawn_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> ROBOT_API UClass* StaticClass<class ARobotPawn>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Robot_Source_Robot_RobotPawn_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
