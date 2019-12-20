#pragma once
#include "Engine.h"

#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ChildActorComponent.h"

#include "Camera/CameraComponent.h"
#include "Math/Rotator.h"
#include "Templates/SubclassOf.h"

#include "AdvancedMovementComponent.h"
#include "CharacteristicsComponent.h"

#include "InvnetorySystem\PickupItem.h"
#include "InvnetorySystem\Inventory.h"
#include "InvnetorySystem\MasterItem\MasterItem.h"

#include "PlayerHero.generated.h"

UCLASS()
class MYPROJECT_API APlayerHero : public ACharacter
	{
		GENERATED_BODY()

	public:
		/**
			@brief Функция для задания параметров по умолчанию.
		*/
		APlayerHero();

		/**
			@brief Функция вызывается каждый tick.
			@param[in] DeltaTime Кадр
		*/
		virtual void Tick(float DeltaTime) override;

		/**
			@brief Функция предназначена для настройки контроллера игрока.
			@param[in] PlayerInputComponent Компонент ввода
		*/
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

		/// Рычаг для камеры
		UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Camera")
			class USpringArmComponent* CameraArm;	
		///	Компонент движения
		UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Camera")
			class UCameraComponent* Third_Person_Camera;
		///	Компонент движения
		UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Camera")
			class UCameraComponent* First_Person_Camera;
		///	Компонент движения
		UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Advanced Movement")
			class UAdvancedMovementComponent* AdvancedMovementComponent;
		///	Компонент характеристик
		UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Characteristics")
			class UCharacteristicsComponent* CharacteristicsComponent;
		/// Текст помощи игроку
		UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "HUD")
			FString HelpText;
		/// Инвентарь игрока
		UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Inventory")
			UInventory* CharacterInventory;
		/**
			@brief Функция отвечает за движение вперёд/назад.
			@param[in] Axis Значение по оси
		*/
		void MoveForward(float Axis);
		/**
			@brief Функция отвечает за движение вправо/влево.
			@param[in] Axis Значение по оси
		*/
		void MoveRight(float Axis);
		/**
			@brief Функция отвечает за бег.
		*/
		void Jog();
		/**
			@brief Функция отвечает за спринт.
		*/
		void Sprint();
		/**
			@brief Функция отвечает за ходьбу.
		*/
		void Walk();
		/**
			@brief Функция отвечает за смену режима вида персонажа.
		*/
		void ChangeView();
		/**
			@brief Функция для вычисления движений.
		*/
		void UpdateMovement();
	protected:
		/**
			@brief Функция вызывается, когда игра начинается или когда спавнется актёр.
		*/
		virtual void BeginPlay() override;
		///	Переменная, отвечающая за вид от 3 лица
		bool is_TP_View = true;
	private:	
		/*
			@brief Функция включает инвентарь
		*/
		void ToggleInventory();
		/*
			@brief Функция реализует взаимодействие с предметом
		*/
		void Interact();
		/**
			@brief Функция проверяет автоподнимаемые предметы в радиусе.
		*/
		void CollectAutoPickups();
		/** 
			@brief Функция проверяет поднимаемые предметы в радиусе и в обзоре.
		*/
		void CheckForInteractables();

		/// Предмет, на который смотрит игрок
		AMasterItem* CurrentInteractableItem;

	};
