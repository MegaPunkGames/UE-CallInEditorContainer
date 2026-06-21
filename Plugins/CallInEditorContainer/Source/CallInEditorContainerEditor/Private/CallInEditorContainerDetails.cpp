// Copyright 2023-2026 - MegaPunk Games Inc. - All Rights Reserved


#include "CallInEditorContainerDetails.h"

#include "DetailWidgetRow.h"
#include "PropertyCustomizationHelpers.h"
#include "Widgets/Layout/SWrapBox.h"

#if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 5)
#include "ObjectTools.h"
#else
#include "K2Node_CallFunction.h"
#endif

DEFINE_LOG_CATEGORY(LogCallInEditorContainer);

TSharedRef<IPropertyTypeCustomization> FCallInEditorContainerDetails::MakeInstance()
{
    return MakeShareable(new FCallInEditorContainerDetails);
}

void FCallInEditorContainerDetails::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
    TArray<UObject*> OuterObjects;
    PropertyHandle->GetOuterObjects(OuterObjects);

    if (OuterObjects.Num() == 0)
        return;

    const FString ThisPropertyName = PropertyHandle->GetProperty()->GetNameCPP();
    const UClass* CurrentClass = PropertyHandle->GetOuterBaseClass();
    TSharedRef<SWrapBox> ButtonBox = SNew(SWrapBox).UseAllottedSize(true);
    
    // Validate and warn if EditCondition is not supported for button disabling. See https://github.com/MegaPunkGames/UE-CallInEditorContainer/issues/3
    bool bNegateTemp;
    const FBoolProperty* EditConditionPropertyTemp = PropertyCustomizationHelpers::GetEditConditionProperty(PropertyHandle->GetProperty(), bNegateTemp);
    const FString& EditCondition = PropertyHandle->GetMetaData(TEXT("EditCondition"));
    const bool EditConditionHides = PropertyHandle->GetBoolMetaData(TEXT("EditConditionHides"));
    if (!EditCondition.IsEmpty() && !EditConditionHides && EditConditionPropertyTemp == nullptr)
    {
        UE_LOG(LogCallInEditorContainer, Warning, TEXT("Invalid EditCondition. CallInEditorContainer only supports basic bool type edit conditions. Button will always be enable, you should use EditConditionHides to hide it instead."));
    }

    while(CurrentClass != UObject::StaticClass())
    {
        TArray<FName> FunctionNames;

        CurrentClass->GenerateFunctionList(FunctionNames);
        for (const FName& FunctionName : FunctionNames)
        {
            UFunction* Function = CurrentClass->FindFunctionByName(FunctionName, EIncludeSuperFlag::ExcludeSuper);

            if (Function == nullptr || Function->NumParms > 0 || Function->GetMetaData(TEXT("CallInEditorContainer")) != ThisPropertyName ||
                Function->ReturnValueOffset != MAX_uint16 || Function->HasAnyFunctionFlags(FUNC_Static))
            {
                continue;
            }

            static const FName CallInEditorMeta(TEXT("CallInEditor"));
    #if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 5)
            FText ButtonLabel = ObjectTools::GetUserFacingFunctionName(Function);
    #else
            FText ButtonLabel = UK2Node_CallFunction::GetUserFacingFunctionName(Function);
    #endif
            FText ButtonToolTip = Function->GetToolTipText();
            if (ButtonToolTip.IsEmpty())
            {
                ButtonToolTip = ButtonLabel;
            }

            ButtonBox->AddSlot()
                .Padding(0.0f, 0.0f, 5.0f, 3.0f)
                [
                    SNew(SButton)
                        .Text(FText::FromName(FunctionName))
                        .ToolTipText(ButtonToolTip)
                        .HAlign(HAlign_Center)
                        .VAlign(VAlign_Center)
                        .IsEnabled_Lambda([OuterObjects, PropertyHandle] ()
                            {
                                bool bEditable = true; // Default
                                bool bNegate;
                                FBoolProperty* EditConditionProperty = PropertyCustomizationHelpers::GetEditConditionProperty(PropertyHandle->GetProperty(), bNegate);
                                if (EditConditionProperty)
                                {
                                    const void* ValuePtr = EditConditionProperty->ContainerPtrToValuePtr<uint8>(OuterObjects[0]);
                                    bEditable = EditConditionProperty->GetPropertyValue(ValuePtr);
                                    if (bNegate)
                                        bEditable = !bEditable;
                                }

                                return bEditable;
                            })
                        .OnClicked_Lambda([OuterObjects, Function] ()
                            {
                                // We need to make the function CallInEditor if it's not or else we can't call it. It's crazy we can do this at runtime!
                                const bool bWasCallable = Function->GetBoolMetaData(CallInEditorMeta);

                                if (!bWasCallable)
                                    Function->SetMetaData(CallInEditorMeta, TEXT("true"));

                                // Call on all selected objects
                                for (UObject* Owner : OuterObjects)
                                {
                                    Owner->ProcessEvent(Function, nullptr);
                                }

                                if (!bWasCallable)
                                    Function->SetMetaData(CallInEditorMeta, TEXT("false"));

                                return FReply::Handled();

                            })
                ];
        }

        CurrentClass = CurrentClass->GetSuperClass();
    }

    HeaderRow
    [
        ButtonBox
    ];
}

void FCallInEditorContainerDetails::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
}
