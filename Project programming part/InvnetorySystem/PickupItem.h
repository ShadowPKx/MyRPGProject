#pragma once
#include "CoreMinimal.h"
#include "InvnetorySystem/MasterItem/MasterItem.h"
#include "PickupItem.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API APickupItem : public AMasterItem
	{
		GENERATED_BODY()
	public:
		APickupItem();
	
		virtual void BeginPlay() override;

		void Interact_Implementation() override;

		UFUNCTION(BlueprintNativeEvent)
			void Use();
			virtual void Use_Implementation();
		/**
		* @brief Функция будет вызываться, когда предмет поднят и нуждается в очистке с уровня
		* 
		*/
		void OnPickedUp();

	};
