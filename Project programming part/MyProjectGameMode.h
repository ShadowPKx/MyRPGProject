#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Sources/PlayerHero.h"
#include "MyProjectGameMode.generated.h"

UCLASS(minimalapi)
class AMyProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
public:
	AMyProjectGameMode();

	enum EHUDState : uint8
		{
			HS_Ingame,
			HS_Inventory,
			HS_Shop_General,
			HS_Shop_Weapon,
			HS_Main_Menu
		};
	/**
		@brief Функция проверяет состояние HUD и вызывает HUD в зависимости от того, какой HUD мы хотим видеть.
	*/
	void ApplyHUDChanges();

	/**
	*	@brief Функция возвращает статус HUD
	*/
	UFUNCTION(BlueprintCallable, Category = "HUD Functions")
	uint8 GetHUDState();
	/**
	*	@brief Функция устанавливает статус HUD
	*/
	UFUNCTION(BlueprintCallable, Category = "HUD Functions")
	void ChangeHUDState(uint8 NewState);

	/**
	*	@brief Функция выводит HUD на экран.
	*	@return true если прошло удачно. Иначе false.
	*/
	bool ApplyHUD(TSubclassOf<class UUserWidget> WidgetToApply,bool bShowMouseCursor,bool EnableClickEvents);

protected:
	
	/**
	*	@brief Указатель на текущий виджет
	*/
	UPROPERTY()
	class UUserWidget* CurrentWidget;
	/**
	*	@brief Номер виджета
	*/
	uint8 HUDState;

	/**
	*	@brief HUD-меню
	*/
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "HUDWidgets",Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> MenuHUDClass;
	/**
	*	@brief HUD, который должен показывается в игре	
	*/
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "HUDWidgets",Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> IngameHUDClass;
	/**
	*	@brief HUD, который должен показывается в инвентаре	
	*/
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "HUDWidgets",Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> InventoryHUDClass;
	/**
	*	@brief HUD, который должен показывается в игре	
	*/
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "HUDWidgets",Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> ShopGeneralHUDClass;
};



