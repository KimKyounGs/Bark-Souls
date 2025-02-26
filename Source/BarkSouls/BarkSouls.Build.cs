// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BarkSouls : ModuleRules
{
	public BarkSouls(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayTasks", "Niagara", "Slate", "SlateCore" });
	}
}
