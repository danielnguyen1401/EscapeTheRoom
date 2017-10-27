// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"

UOpenDoor::UOpenDoor()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	// get player character
	Owner = GetOwner();
	//	ActorThatOpen = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s missing pressure on plate"), *GetOwner()->GetName())
	}
}


void UOpenDoor::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0, -OpenAngle, 0));
}

void UOpenDoor::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0, 0, 0));
}

void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//	if (PressurePlate->IsOverlappingActor(ActorThatOpen))
	//	{
	//		OpenDoor();
	//		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	//	}
	//
	//	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorOpenDelay)
	//	{
	//		CloseDoor();
	//	}

	if (GetTotalMassOfActorOnPlate() > TriggerMass)
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorOpenDelay)
	{
		CloseDoor();
	}
}

float UOpenDoor::GetTotalMassOfActorOnPlate()
{
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors; // Find all overlapping actor

	if (!PressurePlate) return TotalMass;
	PressurePlate->GetOverlappingActors(OverlappingActors);

	for (const auto& Actor : OverlappingActors) // iterate through them adding their masses
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
//		UE_LOG(LogTemp, Warning, TEXT("%s"), *Actor->GetName())
	}
	return TotalMass;
}
