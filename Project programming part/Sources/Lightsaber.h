// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/DamageType.h"
#include "Lightsaber.generated.h"


class UStaticMeshComponent;

UCLASS()
class MYPROJECT_API ALightsaber : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightsaber();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable,Category = "Saber")
		void Activate_Saber();
	UFUNCTION(BlueprintCallable,Category = "Saber")
		void Deactivate_Saber();
	/// Mesh для рукоятки
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Handle")
		class UStaticMeshComponent* Handle_mesh;	
	///  Mesh для лезвия
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Saber")
		class UStaticMeshComponent* Saber_mesh;	
	///  CollisionBox для лезвия
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Saber")
		class UBoxComponent* Saber_Collision;		
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "WeaponState")
		bool Deactivate = true;
	/// Материал меча
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Saber")
		class UMaterial* Saber_Material;			

	UPROPERTY(EditAnywhere)
	TSubclassOf<UDamageType> SaberDamageType;

	UFUNCTION()
		void OnSaberBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};