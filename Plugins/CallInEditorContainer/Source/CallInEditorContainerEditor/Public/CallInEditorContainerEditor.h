// Copyright 2023-2026 - MegaPunk Games Inc. - All Rights Reserved


#pragma once

#include "CoreMinimal.h"


class FCallInEditorContainerEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    void OnPostEngineInit();

private:
    void RegisterCustomPropertyTypeLayout(FName PropertyTypeName, const FOnGetPropertyTypeCustomizationInstance& PropertyTypeLayoutDelegate);

    TSet<FName> RegisteredPropertyTypes;
};
