#pragma once

#include "CoreMinimal.h"
#include "CallInEditorContainer.h"

#include "CIEContainerDemoActor.generated.h"

class UObject;

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
	UPROPERTY(VisibleAnywhere, Category="CIEContainer|SubCategory1|SubSubCat")
	FCallInEditorContainer DemoContainer;
	UPROPERTY(VisibleAnywhere, Category="CIEContainer|SubCategory1|SubSubCat", meta=(EditCondition = "!bEditCondition"))
	FCallInEditorContainer DemoContainerDisabled;
	UPROPERTY(VisibleAnywhere, Category="CIEContainer|SubCategory2|SubSubCat", meta=(DisplayAfter="bEditCondition", EditCondition = "bEditCondition && bCheckbox", EditConditionHides))
	FCallInEditorContainer DemoContainer2;
	UPROPERTY(EditAnywhere, Category="CIEContainer|SubCategory2|SubSubCat")
	bool bEditCondition;
	UPROPERTY(EditAnywhere, Category="CIEContainer|SubCategory2|SubSubCat")
	bool bCheckbox;

	UFUNCTION(meta=(CallInEditorContainer="DemoContainer"))
	void TestCallInContainer() { }

	UFUNCTION(meta=(CallInEditorContainer="DemoContainerDisabled"))
	void TestCallInContainerDisabled() { }

	UFUNCTION(meta=(CallInEditorContainer="DemoContainer2"))
	void TestCallInContainer2() { }

	UFUNCTION(CallInEditor, Category="CIEContainer|SubCategory3|SubSubCat")
	void BadCallInEditor() { }
};
