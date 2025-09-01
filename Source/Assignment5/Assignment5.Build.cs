// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Assignment5 : ModuleRules
{
	public Assignment5(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
