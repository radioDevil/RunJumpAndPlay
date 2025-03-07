// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RunJumpAndPlay : ModuleRules
{
	public RunJumpAndPlay(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		//PrivateIncludePaths.Add("CableComponent/Private");
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject", 
			"Engine",
			"InputCore", 
			"CableComponent", 
			"UMG",
			"HeadMountedDisplay"});

		PrivateDependencyModuleNames.AddRange(new string[] { 
					"Slate",
					"SlateCore",
					"CableComponent"});

		

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
