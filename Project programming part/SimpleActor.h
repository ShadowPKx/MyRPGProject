// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "SimpleActor.generated.h"

UCLASS()
class MYPROJECT_API ASimpleActor : public ACharacter
	{
		GENERATED_BODY()

	public:
		// Sets default values for this character's properties
		ASimpleActor();

		void MoveForward(float Axis);
		void MoveRight(float Axis);
	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	public:	
		// Called every frame
		virtual void Tick(float DeltaTime) override;

		// Called to bind functionality to input
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	};
