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
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"HeadToSpace",
			"HeadToSpace/Variant_Platforming",
			"HeadToSpace/Variant_Combat",
			"HeadToSpace/Variant_Combat/AI",
			"HeadToSpace/Variant_SideScrolling",
			"HeadToSpace/Variant_SideScrolling/Gameplay",
			"HeadToSpace/Variant_SideScrolling/AI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
