#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryItem.generated.h"

/**
 * @brief Набор категорий предметов
 * 
 */
UENUM()
enum class EItemCategories:uint8
	{
		Consumable,
		Equipment,
		QuestItems,
		Readables
	};

/**
*	@brief Структура для описания предмета инвентаря
*/
USTRUCT(BlueprintType)
struct FInventoryItem
	{
		GENERATED_BODY()

	public:
		FInventoryItem();

		/**
		*	@brief Название предмета
		*
		*/
		UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Item Properties")
		FString ItemName;
		/**
		*	@brief 2D текстура предмета
		*
		*/
		UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Item Properties")
		UTexture2D* Thumbnail;
		/**
		 * @brief Категория предмета
		 * 
		 */
		UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Item Properties")
		EItemCategories ItemCategory;
		/**
		*	@brief ID предмета
		*
		*/
		UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Item Properties")
		FString ItemID;
		/**
		*	@brief Вес предмета
		*
		*/
		UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Item Properties")
		int32 Weight;
		/**
		*	@brief Стоимость предмета
		*
		*/
		UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Item Properties")
		int32 Value;
		/**
		 * @brief Переменная, отвечающая за возможность использования
		 * 
		 */
		UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Item Properties")
		bool CanBeUsed;
		/**
		 * @brief Переменная, отвечающая за возможность cкладывания
		 * 
		 */
		UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Item Properties")
		bool is_Stackable;
		/**
		 * @brief Количество предметов
		 * 
		 */
		UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Item Properties")
			int32 quantity;
		/**
		 * @brief Максимальное количество предметов в стопке
		 * 
		 */
		UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Item Properties")
			int32 max_stack_size;
		/**
		*	@brief Описание предмета
		*/
		UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Item Properties")
		FString Description;
		/**
		*	@brief Функция сравнивает 2 предмета
		*
		*	@return true если их ID совпадают, иначе false
		*/
		bool operator==(const FInventoryItem& OtherItem) const
			{
				if (ItemID == OtherItem.ItemID)
					return true;
				return false;
			}
		/**
		 * @brief Функция возвращает информацию о предмете 
		 * 
		 * @return FInventoryItem Информация о предмете 
		 */
		FInventoryItem information__of_InventoryItem()
			{
				return *this;
			}
	};