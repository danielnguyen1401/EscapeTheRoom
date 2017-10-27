// Copyright 2017

#pragma once


#include "EscapeBuilding.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPETHEROOM_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float ReachRange = 100.f;

	UPhysicsHandleComponent* PhysicHandle = nullptr;
	UInputComponent* InputComp = nullptr;

	void Grab();
	void Release();
	void FindPhysicComponent();
	void SetInputComponent();
	FVector GetReachLineStart();
	FVector GetReachLineEnd();
	const FHitResult GetFirstPhysicBodyInReach();
};
