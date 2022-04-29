// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class Robot : ModuleRules
{
    string OPENCV_VERSION = "3411";

    private string ThirdPartyPath
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/"));
        }
    }

	public bool LoadOpenCV(ReadOnlyTargetRules Target)
	{
		// Start OpenCV linking
		bool isLibrarySupported = false;// Create OpenCV Path
		string OpenCVPath = Path.Combine(ThirdPartyPath, "OpenCV");// Get Library Path
		string LibPath = "";
		bool isdebug = Target.Configuration == UnrealTargetConfiguration.Debug;
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			LibPath = Path.Combine(OpenCVPath, "Libraries", "Win64");
			isLibrarySupported = true;
		}
		else
		{
			string Err = string.Format("{0} dedicated server is made to depend on {1}. We want to avoid this, please correct module dependencies.", Target.Platform.ToString(), this.ToString());
			System.Console.WriteLine(Err);
		}
		if (isLibrarySupported)
		{
			//Add Include path
			PublicIncludePaths.AddRange(new string[] { Path.Combine(OpenCVPath, "Includes") });
			//Add Static Libraries
			PublicAdditionalLibraries.Add(Path.Combine(LibPath, "opencv_world" + OPENCV_VERSION + ".lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibPath, "mycvDll" + ".lib"));
			//Add Dynamic Libraries
			PublicDelayLoadDLLs.Add("opencv_world" + OPENCV_VERSION + ".dll");
			PublicDelayLoadDLLs.Add("opencv_ffmpeg" + OPENCV_VERSION + "_64.dll");
			PublicDelayLoadDLLs.Add("mycvDll" + ".dll");
		}
		PublicDefinitions.Add(string.Format("WITH_OPENCV_BINDING={0}", isLibrarySupported ? 1 : 0));
		return isLibrarySupported;
	}

    public Robot(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "RHI", "RenderCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { });

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

		LoadOpenCV(Target);
    }
}
