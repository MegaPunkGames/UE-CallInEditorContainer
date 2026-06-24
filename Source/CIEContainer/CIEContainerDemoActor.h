#pragma once

#include "CoreMinimal.h"
#include "CallInEditorContainer.h"

#include "CIEContainerDemoActor.generated.h"

class UObject;

DECLARE_LOG_CATEGORY_EXTERN(LogCIEContainerDemo, Log, All);

UCLASS()
class CIECONTAINER_API ACIEContainerDemoActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACIEContainerDemoActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category="CIEContainer|SubCategory1|SubSubCat")
	FCallInEditorContainer DemoContainer;
	UPROPERTY(VisibleInstanceOnly, Category="CIEContainer|SubCategory1|SubSubCat", meta=(EditCondition = "!bEditCondition"))
	FCallInEditorContainer DemoContainerDisabled;
	UPROPERTY(VisibleAnywhere, Category="CIEContainer|SubCategory2|SubSubCat", meta=(DisplayAfter="bEditCondition", EditCondition = "bEditCondition && bCheckbox", EditConditionHides))
	FCallInEditorContainer DemoContainer2;
#endif

	UPROPERTY(EditAnywhere, Category="CIEContainer|SubCategory2|SubSubCat")
	bool bEditCondition;
	UPROPERTY(EditAnywhere, Category="CIEContainer|SubCategory2|SubSubCat")
	bool bCheckbox;

	UFUNCTION(meta=(CallInEditorContainer="DemoContainer"))
	void TestCallInContainer() const;

	UFUNCTION(DisplayName="DisplayName Support", meta=(Tooltip = "Button disabling on EditCondition", CallInEditorContainer="DemoContainerDisabled"))
	void TestCallInContainerDisabled() const;

	UFUNCTION(meta=(CallInEditorContainer="DemoContainer2"))
	void TestCallInContainer2() const;

	UFUNCTION(CallInEditor, Category="CIEContainer|SubCategory3|SubSubCat")
	void BadCallInEditor() { }
};
