// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "EscapeBuilding.h"
#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )

class ESCAPETHEROOM_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	UOpenDoor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
	override;

private:
	void OpenDoor();
	void CloseDoor();

	AActor* Owner = nullptr;

	UPROPERTY(EditAnywhere)
	float OpenAngle = 60.f;
	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr; // Always initialize pointer to nullptr

//	AActor* ActorThatOpen;

	UPROPERTY(EditAnywhere)
	float DoorOpenDelay = 1.f;

	float LastDoorOpenTime;

	UPROPERTY(EditAnywhere)
	float TriggerMass = 30.f;

	// return total mass 
	float GetTotalMassOfActorOnPlate();
};