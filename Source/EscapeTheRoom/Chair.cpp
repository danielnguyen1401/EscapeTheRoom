// Fill out your copyright notice in the Description page of Project Settings.

#include "Chair.h"


UChair::UChair()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UChair::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Hello world"));
	
}


void UChair::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

