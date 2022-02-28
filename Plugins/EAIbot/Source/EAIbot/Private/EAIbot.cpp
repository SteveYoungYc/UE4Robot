// Copyright Epic Games, Inc. All Rights Reserved.

#include "EAIbot.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "EAIbotLibrary/ExampleLibrary.h"

#define LOCTEXT_NAMESPACE "FEAIbotModule"

void FEAIbotModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("EAIbot")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	FString LibraryPath;
#if PLATFORM_WINDOWS
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/EAIbotLibrary/Win64/ExampleLibrary.dll"));
#elif PLATFORM_MAC
    LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/EAIbotLibrary/Mac/Release/libExampleLibrary.dylib"));
#endif // PLATFORM_WINDOWS

	ExampleLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (ExampleLibraryHandle)
	{
		// Call the test function in the third party library that opens a message box
		ExampleLibraryFunction();
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load example third party library"));
	}

#if PLATFORM_64BITS
	FString platform = TEXT("win64.dll");
#else
	FString platform = TEXT("win32.dll");
#endif
	FString path = IPluginManager::Get().FindPlugin("EAIbot")->GetBaseDir();
	FString dllpath = path + "/ThirdParty/EAIbot/lib/EAIDll.dll";
	ExampleLibraryHandle = FPlatformProcess::GetDllHandle(*dllpath);
	if (!ExampleLibraryHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load EAIbot library."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Loaded EAIbot library."));
	}
}

void FEAIbotModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	FPlatformProcess::FreeDllHandle(ExampleLibraryHandle);
	ExampleLibraryHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEAIbotModule, EAIbot)
