// Fill out your copyright notice in the Description page of Project Settings.

using EpicGames.Core;
using UnrealBuildTool;

public class CIEContainerEditorTarget : TargetRules
{
	public CIEContainerEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		DefaultBuildSettings = BuildSettingsVersion.Latest;

		ExtraModuleNames.AddRange( new string[] { "CIEContainer" } );
	}
}
