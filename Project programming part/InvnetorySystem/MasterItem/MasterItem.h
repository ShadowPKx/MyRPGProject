#pragma once
#include "CoreMinimal.h"
#include "../InventoryItem.h"
#include "GameFramework/Actor.h"
#include "MasterItem.generated.h"

UCLASS()
class MYPROJECT_API AMasterItem : public AActor
	{
		GENERATED_BODY()
		
	public:	
		// Sets default values for this actor's properties
		AMasterItem();
		/**
		*	@brief Информация о предмете
		*/
		UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Item Info")
			FInventoryItem ItemInfo;
		/**
		*	@brief Текст с помощью
		*/
		UPROPERTY(EditAnywhere, Category = "Item Info")
			FString HelpText;
		/**
		* @brief Функция взаимодействия с предметом
		* 
		*/
		UFUNCTION(BlueprintNativeEvent)
			void Interact();
		/**
		* @brief Функция описнаия взаимодействия с предметом
		* 
		*/
		virtual void Interact_Implementation();
		/**
		* Функция описывает взаимодействие используемого предмета по отношению к персонажу
		* 
		* @brief Функция используется для описания применения предмета
		* 
		*/
		UFUNCTION(BlueprintImplementableEvent,Category = "Item Functions")
			void OnUsedEvent();
		/*
			Предполагается, что все предметы, с которыми будет происходить взаимодействие, будут иметь mesh
		*/
		/**
		* @brief Mesh предмета
		* 
		*/
		UPROPERTY(EditAnywhere, Category = "Item Properties")
		class UStaticMeshComponent* ItemMesh;
	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;
	};
