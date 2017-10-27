// Copyright 2017

#include "Grabber.h"

#define  OUT

UGrabber::UGrabber()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicComponent();
	SetInputComponent();
}

void UGrabber::FindPhysicComponent()
{
	PhysicHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing PhysicHandle component"), *GetOwner()->GetName());
	}
}

void UGrabber::SetInputComponent()
{
	InputComp = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComp)
	{
		InputComp->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComp->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing Input component"), *GetOwner()->GetName())
	}
}


void UGrabber::Grab()
{
	auto Hit = GetFirstPhysicBodyInReach();
	auto ComponentToGrab = Hit.GetComponent();
	auto ActorHit = Hit.GetActor();

	if (ActorHit)
	{
		if (!PhysicHandle) return;
		PhysicHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(), //GrabLocation
			true // allow rotation
		);
	}
}

void UGrabber::Release()
{
	if (!PhysicHandle) return;
	PhysicHandle->ReleaseComponent();
}


void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicHandle->GrabbedComponent) // if physic handle is attached
	{
		PhysicHandle->SetTargetLocation(GetReachLineEnd()); // move the object we're holding
	}
}

const FHitResult UGrabber::GetFirstPhysicBodyInReach()
{
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	// Raycast out to reach distance
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		    GetReachLineStart(),
		    GetReachLineEnd(),
		    FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		    TraceParameters
	);

	// See what we hit
	//	AActor* ActorHit = HitResult.GetActor();
	//	if (ActorHit)
	//	{
	//		// GetName return Fstring, but UE_LOG wants us to dereference those Fstring with *
	////		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit->GetName()));
	//	}
	return HitResult;
}

FVector UGrabber::GetReachLineStart()
{
	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewpointLocation,
		    OUT PlayerViewpointRotation);

	//	UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *PlayerViewpointLocation.ToString(), *PlayerViewpointRotation.ToString())
	// Draw a red line to visual
	//	FVector LineTraceEnd = PlayerViewpointLocation + PlayerViewpointRotation.Vector() * ReachRange;
	//	DrawDebugLine(GetWorld(), PlayerViewpointLocation, LineTraceEnd, FColor(255.f, 0, 0), false, 0, 0, 10.f);

	return PlayerViewpointLocation;
}

FVector UGrabber::GetReachLineEnd()
{
	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewpointLocation,
		    OUT PlayerViewpointRotation);

	return PlayerViewpointLocation + PlayerViewpointRotation.Vector() * ReachRange;
}
