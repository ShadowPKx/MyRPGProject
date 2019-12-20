// Fill out your copyright notice in the Description page of Project Settings.


#include "Lightsaber.h"
#include "Materials/Material.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ALightsaber::ALightsaber()
	{
 		// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
		PrimaryActorTick.bCanEverTick = true;

		/**
			Создаём meshcomponent для рукояти и лезвия, и создаём материал для лезвия
		*/
		Handle_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Handle_Mesh"));
		Saber_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Saber_Mesh"));
		Saber_Material = CreateDefaultSubobject<UMaterial>(TEXT("Saber_Material"));
		Saber_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Saber_Collision"));

		SetRootComponent(Handle_mesh);
		Saber_mesh->SetupAttachment(Handle_mesh);
		Saber_Collision->SetupAttachment(Saber_mesh);

		Saber_Collision->OnComponentBeginOverlap.AddDynamic(this,&ALightsaber::OnSaberBeginOverlap);
		/**
			Отключаем в начале коллизию, чтобы меч не вступал в действие с актёром и другими атёрами
		*/
		Handle_mesh->SetCollisionProfileName(TEXT("NoCollision"));
		Saber_mesh->SetCollisionProfileName(TEXT("NoCollision"));
		Saber_Collision->SetCollisionProfileName(TEXT("NoCollision"));
		/**
			Скрываем их 
		*/
		Handle_mesh->ToggleVisibility(false);
		Saber_mesh->ToggleVisibility(false);
		/**
			Устанавливаем размеры (найдено опытным путём) 
		*/
		Handle_mesh->RelativeScale3D = {0.05,0.05,0.3};
		Saber_mesh->RelativeScale3D = {0.5,0.5,4.0};
	}

// Called when the game starts or when spawned
void ALightsaber::BeginPlay()
	{
		Super::BeginPlay();
		Saber_mesh->SetMaterial(0,Saber_Material);
	}

// Called every frame
void ALightsaber::Tick(float DeltaTime)
	{
		Super::Tick(DeltaTime);	
	}

void ALightsaber::OnSaberBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)  
	{  
		/**
			Если актёр, с которым мы взаимодействуем не меч, не родитель(тот, кто держит меч) и меч не деактивирован
		*/
		// UE_LOG(LogTemp, Log,TEXT("Lightsaber_begin_overlap!")); // Debug
		if ( (OtherActor != nullptr ) && (OtherActor != this)  && (OtherActor != this->GetParentActor()) && !Deactivate)  
			{ 
				UGameplayStatics::ApplyDamage(OtherActor,0.2,this->GetParentActor()->GetInstigatorController(),this,SaberDamageType);
				//UE_LOG(LogTemp, Log,TEXT("Lightsaber add damage!")); // Debug
			}  
	}

void ALightsaber::Activate_Saber()
	{
		Saber_Collision->SetCollisionProfileName(TEXT("OverlapAll"));
		Deactivate=false;
	}

void ALightsaber::Deactivate_Saber()
	{
		Saber_Collision->SetCollisionProfileName(TEXT("NoCollision"));
		Deactivate=true;
	}