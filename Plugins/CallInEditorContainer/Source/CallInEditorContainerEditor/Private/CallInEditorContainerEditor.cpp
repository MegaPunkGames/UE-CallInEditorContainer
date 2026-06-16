// Fill out your copyright notice in the Description page of Project Settings.

#include "CallInEditorContainerEditor.h"

#include "CallInEditorContainerDetails.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_MODULE(FCallInEditorContainerEditorModule, CallInEditorContainerEditor );

const FName PropertyEditorModuleName("PropertyEditor");

void FCallInEditorContainerEditorModule::StartupModule()
{
#if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 8)
    FCoreDelegates::GetOnPostEngineInit().AddRaw(this, &FCIEContainerEditorModule::OnPostEngineInit);
#else
    FCoreDelegates::OnPostEngineInit.AddRaw(this, &FCallInEditorContainerEditorModule::OnPostEngineInit);
#endif
}

void FCallInEditorContainerEditorModule::ShutdownModule()
{
    if (FModuleManager::Get().IsModuleLoaded(PropertyEditorModuleName))
    {
        FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(PropertyEditorModuleName);
    
        // Unregister all structures
        for (auto It = RegisteredPropertyTypes.CreateConstIterator(); It; ++It)
        {
            if(It->IsValid())
            {
                PropertyModule.UnregisterCustomPropertyTypeLayout(*It);
            }
        }

        PropertyModule.NotifyCustomizationModuleChanged();
    }
}

void FCallInEditorContainerEditorModule::OnPostEngineInit()
{
#if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 8)
    FCoreDelegates::GetOnPostEngineInit().RemoveAll(this);
#else
    FCoreDelegates::OnPostEngineInit.RemoveAll(this);
#endif

    RegisterCustomPropertyTypeLayout(TEXT("CallInEditorContainer"), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FCallInEditorContainerDetails::MakeInstance));
}

void FCallInEditorContainerEditorModule::RegisterCustomPropertyTypeLayout(FName PropertyTypeName, const FOnGetPropertyTypeCustomizationInstance& PropertyTypeLayoutDelegate)
{
    check(PropertyTypeName != NAME_None);

    RegisteredPropertyTypes.Add(PropertyTypeName);

    if (FModuleManager::Get().IsModuleLoaded(PropertyEditorModuleName))
    {
        FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(PropertyEditorModuleName);
        PropertyModule.RegisterCustomPropertyTypeLayout(PropertyTypeName, PropertyTypeLayoutDelegate);
    }
}
