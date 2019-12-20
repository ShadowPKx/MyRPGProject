#include "PlayerHero.h"
#include "Engine/EngineTypes.h"
#include "Engine/Engine.h"
#include "Math/UnrealMathUtility.h"
#include "MyProjectGameMode.h"

#include "DrawDebugHelpers.h"

// Sets default values
APlayerHero::APlayerHero() 
	{

		/// Set this character to call Tick() every frame.  You can turn this off to
		/// improve performance if you don't need it.
		PrimaryActorTick.bCanEverTick = true;

		/// Я не позволяю контроллеру поворачивать, вместо этого камера будет
		/// поворачивать контроллер
		bUseControllerRotationPitch = false;
		bUseControllerRotationRoll = false;
		bUseControllerRotationYaw = false;
		/**
										Устанавливаем камеры
		*/
		GetCharacterMovement()->bOrientRotationToMovement = true;  /// Будет поворачивать персонажа по направлению движения
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
		GetCharacterMovement()->JumpZVelocity = 1000.0f;  /// Устанавливаем значение скорости прыжка
		GetCharacterMovement()->AirControl = 0.1f;  /// Устанавливаем значение управляемости в полёте
		/**
			Созаём рычаг камеры и настраиваем его
		*/
		CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
		CameraArm->SetupAttachment(RootComponent);
		CameraArm->TargetArmLength = 300.f;
		CameraArm->bUsePawnControlRotation = true;
		/**
			Созаём камеру от 3 лица
		*/
		Third_Person_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
		Third_Person_Camera->SetupAttachment(CameraArm,USpringArmComponent::SocketName);
		Third_Person_Camera->bUsePawnControlRotation = false;
		/**
			Создаём камеру от 1 лица
		*/
		First_Person_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
		First_Person_Camera->Deactivate();
		First_Person_Camera->AttachToComponent(Cast<USceneComponent>(GetMesh()),FAttachmentTransformRules::KeepRelativeTransform,FName("FP_Camera"));  /// Присоединяем его к своему сокету
		First_Person_Camera->bUsePawnControlRotation = true;
		/**
						Движение
		*/
		AdvancedMovementComponent = CreateDefaultSubobject<UAdvancedMovementComponent>(TEXT("AdvancedMovement"));
		/**
   						Характеристики
		*/
		CharacteristicsComponent = CreateDefaultSubobject<UCharacteristicsComponent>(TEXT("CharacteristicsComponent"));
		/**
   						Инвентарь
		*/
		CharacterInventory = CreateDefaultSubobject<UInventory> (TEXT("InventoryComponent"));
	}

void APlayerHero::BeginPlay() 
	{ 
		Super::BeginPlay(); 

		CharacterInventory->Inventory.SetNum(4);

		CurrentInteractableItem = nullptr;
	}

void APlayerHero::Tick(float DeltaTime) 
	{
		Super::Tick(DeltaTime);
		UpdateMovement();
		CheckForInteractables();
		//CollectAutoPickups();
	}

void APlayerHero::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent) 
	{
	  Super::SetupPlayerInputComponent(PlayerInputComponent);

	  PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	  PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	  PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	  PlayerInputComponent->BindAction("Jump", IE_Released, this,&ACharacter::StopJumping);

	  PlayerInputComponent->BindAxis("MoveForward", this, &APlayerHero::MoveForward);
	  PlayerInputComponent->BindAxis("MoveRight", this, &APlayerHero::MoveRight);

	  PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APlayerHero::Jog);
	  PlayerInputComponent->BindAction("Run", IE_Released, this, &APlayerHero::Jog);
	  PlayerInputComponent->BindAction("Run", IE_DoubleClick, this, &APlayerHero::Sprint);

	  PlayerInputComponent->BindAction("Walk", IE_Pressed, this, &APlayerHero::Walk);
	  PlayerInputComponent->BindAction("Walk", IE_Released, this, &APlayerHero::Walk);

	  PlayerInputComponent->BindAction("ChangeView", IE_Pressed, this, &APlayerHero::ChangeView);

	  PlayerInputComponent->BindAction("ToggleInventory", IE_Pressed, this, &APlayerHero::ToggleInventory);
	  PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerHero::Interact);
	}

void APlayerHero::MoveForward(float Axis) 
	{
	  FRotator Rotation = Controller->GetControlRotation();
	  FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	  FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	  if(!AdvancedMovementComponent->is_Attacking)
		  {
			  AddMovementInput(Direction * AdvancedMovementComponent->Speed, Axis);
		  }
	}

void APlayerHero::MoveRight(float Axis) 
	{
	  FRotator Rotation = Controller->GetControlRotation();
	  FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	  FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	   if(!AdvancedMovementComponent->is_Attacking)
		  {
			  AddMovementInput(Direction * AdvancedMovementComponent->Speed, Axis);
		  }
	}

void APlayerHero::Jog()
	{
	  if (AdvancedMovementComponent->is_Jogging) 
		  {
			AdvancedMovementComponent->is_Jogging = false;
			AdvancedMovementComponent->is_Sprinting = false;
		  } 
	  else 
		  {
			AdvancedMovementComponent->is_Jogging = true;
		  }
	}

void APlayerHero::Sprint() 
	{
	  if (AdvancedMovementComponent->is_Sprinting) 
		{
			AdvancedMovementComponent->is_Sprinting = false;
		} 
	  else 
		  {
			AdvancedMovementComponent->is_Sprinting = true;
		  }
	}

void APlayerHero::Walk() 
	{
	  if (AdvancedMovementComponent->is_Walking) 
		  {
			AdvancedMovementComponent->is_Walking = false;
		  } 
	  else 
		  {
			AdvancedMovementComponent->is_Walking = true;
		  }
	}

void APlayerHero::ChangeView() 
	{
	  if (is_TP_View) 
		  {
			is_TP_View = false;
			Third_Person_Camera->Deactivate();
			First_Person_Camera->Activate();
			bUseControllerRotationYaw = true;
		  } 
	  else 
		  {
			is_TP_View = true;

			First_Person_Camera->Deactivate();
			Third_Person_Camera->Activate();
			bUseControllerRotationYaw = false;
		  }
	}

void APlayerHero::UpdateMovement() 
	{
		AdvancedMovementComponent->InputX = GetInputAxisValue("MoveForward");								// Получаем входящее значение движения по оси X 
		AdvancedMovementComponent->InputZ = -1.0f * GetInputAxisValue("MoveRight");							// Получаем входящее значение движения по оси Y 
		FVector temp_vector_ = {AdvancedMovementComponent->InputX,AdvancedMovementComponent->InputZ, 0.0f};	// Создаём вектор из полученных значений
		FRotator Delta_1 = ((Third_Person_Camera->GetComponentRotation()) - (GetCapsuleComponent()->GetComponentRotation()));// Создаём ротатор на основании вращения камеры и капсулы
		Delta_1.Normalize();	// Нормализуем ротатор
		FRotator Delta = Delta_1 - temp_vector_.Rotation();
		Delta.Normalize();		// Нормализуем ротатор
		AdvancedMovementComponent->Direction = Delta.Yaw;
		float temp = abs(AdvancedMovementComponent->InputX) + abs(AdvancedMovementComponent->InputZ);
		if (!AdvancedMovementComponent->is_Alive)
			{
				AdvancedMovementComponent->Speed = 0.0;
				return;
			}
		temp = FMath::Clamp(temp, 0.0f, 1.0f);
		AdvancedMovementComponent->Speed = temp;	// Скорость вычисляется исходя из значений по осям, вписанная в интервал от 0 до 1
		// Далее скорость увеличиватся или уменьшается в зависимости от типа движения
		if (AdvancedMovementComponent->is_Sprinting) 
			{
				AdvancedMovementComponent->Speed *= 2.0f;
			} 
		else if (AdvancedMovementComponent->is_Jogging) 
			{
				AdvancedMovementComponent->Speed *= 1.3f;
			} 
		else if (AdvancedMovementComponent->is_Walking)
			{
				AdvancedMovementComponent->Speed *= 0.3f;
			} 
		else 
			{
				AdvancedMovementComponent->Speed *= 0.6f;
			}
		// UE_LOG(LogTemp, Log,TEXT("| InputX %f | InputZ %f | Direction %f | Speed %f|"),AdvancedMovementComponent->InputX,AdvancedMovementComponent->InputZ,AdvancedMovementComponent->Direction,AdvancedMovementComponent->Speed);
	}

/*
void APlayerHero::CollectAutoPickups()
	{
		// Получаем всех актёров с которыми взаимодействует сфера для сбора и складываем их в массив
		TArray<AActor*> CollectedActors;
		CollectionSphere->GetOverlappingActors(CollectedActors);

		AInventoryController* IController = Cast<AInventoryController>(GetController());

		// Для каждого актёра 
		for (int32 iCollected = 0; iCollected < CollectedActors.Num(); ++iCollected)
			{
				//UE_LOG(LogTemp, Log,TEXT("item"));
				// Переводим актёра в AAutoPickup
				//AAutoPickup* const TestPickup = Cast<AAutoPickup>(CollectedActors[iCollected]);
				// Если перевод был удачен и возможно его положить
				if (TestPickup && !TestPickup->IsPendingKill())
					{
						TestPickup->Collect(IController);
					}
			}
	}*/

void APlayerHero::ToggleInventory()
	{		
		if(GEngine)
			{
				FString temp;
				for (auto Item:CharacterInventory->Inventory)
					{
						if (Item != nullptr)
							{
								temp = Item->ItemInfo.ItemName + ' ' + FString::FromInt(Item->ItemInfo.quantity) + ' ' + FString::FromInt(Item->ItemInfo.Value) + ' ' + FString::FromInt(Item->ItemInfo.Weight) + '\n';
							}
					}
				temp += "Money: " + FString::FromInt(CharacterInventory->Money) + '\n';
				temp += "Weight: " + FString::FromInt(CharacterInventory->GetInventoryWeight()) + '/' + FString::FromInt(CharacterInventory->InventoryWeightLimit)+ '\n';
				GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Blue, temp);
			}
	}

void APlayerHero::Interact()
	{
		if(CurrentInteractableItem != nullptr)
			{	
				CurrentInteractableItem->Interact_Implementation();
				HelpText = "";
			}
	}

void APlayerHero::CheckForInteractables()
	{
		// Create a LineTrace to check for a hit
		FHitResult HitResult;
		
		int32 Range = 500;
		FVector StartTrace = Third_Person_Camera->GetComponentLocation();
		FVector EndTrace = (Third_Person_Camera->GetForwardVector() * Range) + StartTrace;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);

		//DrawDebugLine(GetWorld(),StartTrace,EndTrace,FColor::Red,false,1,0,1); // For debugging
		
		auto IController = GetController();
		// Проверяется если что-то задето
		if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, QueryParams))
			{	
				AMasterItem* Item = Cast<AMasterItem>(HitResult.GetActor());	
				if (Item == nullptr)
					{
						HelpText = FString("");
						CurrentInteractableItem = nullptr;
						return;
					}
				else
					{
						HelpText = Item->HelpText;
						CurrentInteractableItem = Item;
						return;
					}
			}
	}