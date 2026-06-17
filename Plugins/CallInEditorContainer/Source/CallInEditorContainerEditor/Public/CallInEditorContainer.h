// Copyright 2023-2026 - MegaPunk Games Inc. - All Rights Reserved

#pragma once

#include "CallInEditorContainer.generated.h"

/**
 * This class is just a details panel placeholder to overcome an Unreal bug where you cannot add action buttons
 * in a sub/nested category. Unreal has the unfortunate bug that it will create a new root category and duplicate all
 * properties in the details panel. This circumvents that bug by using a custom details panel in which we add the
 * desired UFUNCTION buttons.
 */
USTRUCT(BlueprintType)
struct FCallInEditorContainer
{
    GENERATED_BODY()
};
