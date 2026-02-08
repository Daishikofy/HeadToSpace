// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HeadToSpace : ModuleRules
{
	public HeadToSpace(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"ImGui"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"HeadToSpace",
			"HeadToSpace/UnrealExample/Variant_Platforming",
			"HeadToSpace/UnrealExample/Variant_Combat",
			"HeadToSpace/UnrealExample/Variant_Combat/AI",
			"HeadToSpace/UnrealExample/Variant_SideScrolling",
			"HeadToSpace/UnrealExample/Variant_SideScrolling/Gameplay",
			"HeadToSpace/UnrealExample/Variant_SideScrolling/AI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
