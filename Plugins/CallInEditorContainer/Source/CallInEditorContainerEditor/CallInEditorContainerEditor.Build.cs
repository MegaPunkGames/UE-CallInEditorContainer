// Copyright 2023-2026 - MegaPunk Games Inc. - All Rights Reserved

using System.IO;
using UnrealBuildTool;

public class CallInEditorContainerEditor : ModuleRules
{
    public CallInEditorContainerEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "BlueprintGraph",
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
