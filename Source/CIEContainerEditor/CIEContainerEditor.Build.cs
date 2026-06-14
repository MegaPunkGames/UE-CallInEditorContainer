// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class CIEContainerEditor : ModuleRules
{
	public CIEContainerEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "UnrealEd",
                "EditorSubsystem",
                "PropertyEditor",
                "SlateCore",
                "Slate"
            });

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "InputCore",
                "MessageLog",
                "ToolWidgets",
            }
        );
	}
}
