// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvancedMovementComponent.h"


UAdvancedMovementComponent::UAdvancedMovementComponent()
	{
		PrimaryComponentTick.bCanEverTick = true;

		InputX = 0.0f;
		InputZ = 0.0f;
		Direction = 0.0f;
	}



void UAdvancedMovementComponent::BeginPlay()
	{
		Super::BeginPlay();	
	}

void UAdvancedMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
	{
		Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	}

