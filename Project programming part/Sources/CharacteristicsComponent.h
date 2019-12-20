// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacteristicsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UCharacteristicsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UCharacteristicsComponent();
	/**
	* 	@brief Здоровье персонажа
	*
	*/
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Health)
		float Health = 1.0f;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
