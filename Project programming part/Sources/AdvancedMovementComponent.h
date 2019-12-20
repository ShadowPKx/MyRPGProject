#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AdvancedMovementComponent.generated.h"

/**
 *	Класс предназначен для описания 
 *	@brief Construct a new UCLASS object 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UAdvancedMovementComponent : public UActorComponent
	{
		GENERATED_BODY()

	public:	

		UAdvancedMovementComponent();
		/**
		*	@brief Переменная состояния ходьбы
		*/
		UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Moving)
		bool is_Alive = true;
		/**
		*	@brief Переменная состояния ходьбы
		*/
		UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Moving)
		bool is_Walking = false;
		/**
		*	@brief Переменная состояния легкого бега
		*/
		UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Moving)
		bool is_Jogging = false;
		/**
		*	@brief Переменная состояния спринта
		*/
		UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Moving)
		bool is_Sprinting = false;
		/**
		*	@brief Переменная состояния готовности к атаке
		*/
		UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Moving)
		bool is_Armed = false;
		/**
		*	@brief Переменная состояния атаки
		*/
		UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Moving)
		bool is_Attacking = false;

		/**
		*	@brief Вхдящее значение по оси х
		*/
		UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = Moving)
		float InputX;
		/**
		*	@brief Вхдящее значение по оси у
		*/
		UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = Moving)
		float InputZ;
		/**
		*	@brief Вычисляемое значение направления камеры
		*/
		UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = Moving)
		float Direction;
		/**
		*	@brief Вычисляемое значение скорости персонажа
		*/
		UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = Moving)
		float Speed;
	protected:
		/**
		 * @brief Функция, вызываемая после конструктора
		 */
		virtual void BeginPlay() override;

	public:	
		/**
		 * @brief Функция, вызываемая каждую секунду
		 * 
		 * @param DeltaTime Кадр
		 * @param TickType Тип тика
		 * @param ThisTickFunction Функция тика актёра
		 */
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	};
