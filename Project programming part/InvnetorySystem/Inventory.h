#pragma once
#include "Engine.h"
#include "Components/ActorComponent.h"
#include "PickupItem.h"
#include "InventoryItem.h"
#include "MasterItem\MasterItem.h"
#include "Inventory.generated.h"

/**
	@brief Класс для описания инвентаря
 */
UCLASS()
class MYPROJECT_API UInventory: public UActorComponent
	{
		GENERATED_BODY()

		public:

			UInventory();
			/**
			*	@brief Функция обновления инвентаря
			*/
			/**
			*	@brief Инвентарь
			*/
			UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Inventory")
				TArray<AMasterItem*> Inventory;
			/**
			*	@brief Деньги
			*/
			UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
				int32 Money;
			/**
			*	@brief Огранечение слотов в инвентаре
			*/
			UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
				int32 InventorySlotLimit;
			/**
			*	@brief Огранечение инвентаря по весу
			*/
			UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
				int32 InventoryWeightLimit;
			/**
			*	@brief Функция возврацает вес инвентаря
			*	@return вес инвентаря (int32)
			*/
			UFUNCTION(BlueprintCallable, Category = "Utils")
				int32 GetInventoryWeight();
			/**
			*	@brief Функция для обновления золота
			*	@param[in] Amount Количество золота
			*/
			UFUNCTION(BlueprintCallable,Category =  "Inventory Functions")
				void AddMoney(int32 Amount);
			/**
			*	@brief Функция для добавления предмета в инвентарь
			*	@param[in] Item Структура, содержащая информацию о предмете.
			*/
			UFUNCTION(BlueprintPure,Category =  "Inventory Functions")
				bool AddItemToInventory(AMasterItem* Item);
			/**
			*	@brief Функция для получения 2D текстуры предмета в инвентаре по слоту
			*	@param[in] Slot Номер слота.
			*/
			UFUNCTION(BlueprintPure,Category =  "Inventory Functions")
				UTexture2D* GetThumbnailOfInventorySlot(int32 Slot);
			/**
			*	@brief Функция для получения названия предмета в инвентаре по слоту
			*	@param[in] Slot Номер слота.
			*/
			UFUNCTION(BlueprintPure,Category =  "Inventory Functions")
				FString GetNameOfInventorySlot(int32 Slot);
			/**
			*	@brief Функция для применения предмета в инвентаре по слоту
			*	@param[in] Slot Номер слота.
			*/
			UFUNCTION(BlueprintCallable,Category =  "Inventory Functions")
				void UseItemfInventorySlot(int32 Slot);
	};
