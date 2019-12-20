// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MyProjectGameMode.h"
#include "MyProjectCharacter.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

void AMyProjectGameMode::BeginPlay()
	{
		ApplyHUDChanges();
	}

AMyProjectGameMode::AMyProjectGameMode()
	{
		// set default pawn class to our Blueprinted character
		static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
		if (PlayerPawnBPClass.Class != NULL)
			{
				DefaultPawnClass = PlayerPawnBPClass.Class;
			}

		HUDState = EHUDState::HS_Ingame;
	}

void AMyProjectGameMode::ApplyHUDChanges()
	{
		// Убираем предыдущий HUD с момента, как применяем новый
		if(CurrentWidget != nullptr)
			{
				CurrentWidget->RemoveFromParent();
			}

		switch(HUDState)
		{
			case EHUDState::HS_Ingame:
				{
					ApplyHUD(IngameHUDClass,false,false);
					break;
				}
			case EHUDState::HS_Inventory:
				{
					ApplyHUD(InventoryHUDClass,true,true);
					break;
				}
			case EHUDState::HS_Shop_General:
				{
					ApplyHUD(ShopGeneralHUDClass,true,true);
					break;
				}
			case EHUDState::HS_Main_Menu:
				{
					ApplyHUD(MenuHUDClass,true,true);
					break;
				}
			default:
				{
					ApplyHUD(IngameHUDClass,false,false);
				}
		}
	}

uint8 AMyProjectGameMode::GetHUDState()
	{
		return HUDState;
	}

void AMyProjectGameMode::ChangeHUDState( uint8 NewState )
	{
		HUDState = NewState;
		ApplyHUDChanges();
	}

bool AMyProjectGameMode::ApplyHUD( TSubclassOf<class UUserWidget> WidgetToApply, bool bShowMouseCursor, bool EnableClickEvents )
	{
		// Получаем ссылку на игрока и его контроллер
		APlayerHero* MyCharacter = Cast<APlayerHero>(UGameplayStatics::GetPlayerCharacter(this,0));
		APlayerController* MyController = GetWorld()->GetFirstPlayerController();

		if (WidgetToApply != nullptr)
			{
				// Устаналиваем видимость мышки и возможность создавать события по клику
				MyController->bShowMouseCursor = bShowMouseCursor;
				MyController->bEnableClickEvents = EnableClickEvents;
				// Создаём виджет
				CurrentWidget = CreateWidget<UUserWidget>(GetWorld(),WidgetToApply);

				if (CurrentWidget != nullptr)
					{
						CurrentWidget->AddToViewport();
						return true;
					}
			}
		return false;
	}
