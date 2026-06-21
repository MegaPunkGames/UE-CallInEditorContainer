


#include "CIEContainerDemoActor.h"


DEFINE_LOG_CATEGORY(LogCIEContainerDemo);

// Sets default values
ACIEContainerDemoActor::ACIEContainerDemoActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ACIEContainerDemoActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACIEContainerDemoActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACIEContainerDemoActor::TestCallInContainer() const
{
	UE_LOG(LogCIEContainerDemo, Log, TEXT("TestCallInContainer called on actor %s"), *this->GetActorNameOrLabel());
}

void ACIEContainerDemoActor::TestCallInContainerDisabled() const
{
	UE_LOG(LogCIEContainerDemo, Log, TEXT("TestCallInContainerDisabled called on actor %s"), *this->GetActorNameOrLabel());
}

void ACIEContainerDemoActor::TestCallInContainer2() const
{
	UE_LOG(LogCIEContainerDemo, Log, TEXT("TestCallInContainer2 called on actor %s"), *this->GetActorNameOrLabel());
}

