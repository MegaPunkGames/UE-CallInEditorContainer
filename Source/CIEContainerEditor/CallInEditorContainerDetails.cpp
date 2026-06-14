// Copyright 2023-2026 - MegaPunk Games Inc. - All Rights Reserved


#include "CallInEditorContainerDetails.h"

#include "DetailWidgetRow.h"
#include "ObjectTools.h"
#include "Widgets/Layout/SWrapBox.h"

TSharedRef<IPropertyTypeCustomization> FCallInEditorContainerDetails::MakeInstance()
{
    return MakeShareable(new FCallInEditorContainerDetails);
}

void FCallInEditorContainerDetails::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
    TArray<UObject*> OuterObjects;
    PropertyHandle->GetOuterObjects(OuterObjects);

    if (OuterObjects.Num() != 1)
        return;

    UObject* Owner = OuterObjects[0];
    const FString ThisPropertyName = PropertyHandle->GetProperty()->GetNameCPP();
    const UClass* OwnerClass = PropertyHandle->GetProperty()->GetOwnerClass();
    TSharedRef<SWrapBox> ButtonBox = SNew(SWrapBox).UseAllottedSize(true);
    TArray<FName> FunctionNames;

    OwnerClass->GenerateFunctionList(FunctionNames);
    for (const FName& FunctionName : FunctionNames)
    {
        UFunction* Function = OwnerClass->FindFunctionByName(FunctionName, EIncludeSuperFlag::ExcludeSuper);

        if (Function == nullptr || Function->NumParms > 0 || Function->GetMetaData(TEXT("CallInEditorContainer")) != ThisPropertyName ||
            Function->ReturnValueOffset != MAX_uint16 || Function->HasAnyFunctionFlags(FUNC_Static))
        {
            continue;
        }

        static const FName CallInEditorMeta(TEXT("CallInEditor"));
        FText ButtonLabel = ObjectTools::GetUserFacingFunctionName(Function);
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
                    .OnClicked_Lambda([Owner, Function] ()
                        {
                            // We need to make the function CallInEditor if it's not or else we can't call it. It's crazy we can do this at runtime!
                            const bool bWasCallable = Function->GetBoolMetaData(CallInEditorMeta);

                            if (!bWasCallable)
                                Function->SetMetaData(CallInEditorMeta, TEXT("true"));

                            Owner->ProcessEvent(Function, nullptr);

                            if (!bWasCallable)
                                Function->SetMetaData(CallInEditorMeta, TEXT("false"));

                            return FReply::Handled();

                        })
            ];
    }

    HeaderRow
    [
        ButtonBox
    ];
}

void FCallInEditorContainerDetails::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
    
}
