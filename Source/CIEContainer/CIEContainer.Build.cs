// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class CIEContainer : ModuleRules
{
	public CIEContainer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.AddRange(new string[] { "CallInEditorContainerEditor" });
		}
	}
}
