// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class EAIbot : ModuleRules
{
	private string ThirdPartyPath {
		get { return Path.GetFullPath("D:\\SJTU\\thesis\\Robot\\Plugins\\EAIbot\\ThirdParty"); }
	}

	public EAIbot(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
				Path.Combine(ThirdPartyPath, "EAIbot", "include"),
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
				Path.Combine(ThirdPartyPath, "EAIbot", "include"),
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"EAIbotLibrary",
				"Projects"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add private dependencies that you statically link with here ...	
				"Projects"
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
		string EAIbotPath = Path.Combine(ThirdPartyPath, "EAIbot");
		string EAIbotIncludePath = Path.Combine(EAIbotPath, "include");
		string EAIbotLibPath = Path.Combine(EAIbotPath, "lib");
		PublicIncludePaths.Add(EAIbotIncludePath);
		PublicLibraryPaths.Add(EAIbotLibPath);
		PublicAdditionalLibraries.Add("EAIDll.lib");
	}
}
