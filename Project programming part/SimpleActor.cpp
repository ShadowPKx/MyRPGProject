#include "SimpleActor.h"

// Sets default values
ASimpleActor::ASimpleActor()
	{
 		// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
		PrimaryActorTick.bCanEverTick = true;

		// Я не позволяю контроллеру поворачивать, вместо этого камера будет поворачивать контроллер
		bUseControllerRotationPitch = false;
		bUseControllerRotationRoll = false;
		bUseControllerRotationYaw = false;
	}

// Called when the game starts or when spawned
void ASimpleActor::BeginPlay()
	{
		Super::BeginPlay();
	
	}

// Called every frame
void ASimpleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASimpleActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
	{
		Super::SetupPlayerInputComponent(PlayerInputComponent);

		PlayerInputComponent->BindAxis("Turn",this,&APawn::AddControllerYawInput);
		PlayerInputComponent->BindAxis("LookUp",this,&APawn::AddControllerPitchInput);
	
		PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ACharacter::Jump);
		PlayerInputComponent->BindAction("Jump",IE_Released,this,&ACharacter::StopJumping);
	
		PlayerInputComponent->BindAxis("MoveForward",this,&ASimpleActor::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight",this,&ASimpleActor::MoveRight);
	}


void ASimpleActor::MoveForward(float Axis) 
	{
	   FRotator Rotation = Controller->GetControlRotation();
	   FRotator YawRotation(0.0f,Rotation.Yaw,0.0f);

	   FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	   AddMovementInput(Direction, Axis);
	}

void ASimpleActor::MoveRight(float Axis) 
	{
	   FRotator Rotation = Controller->GetControlRotation();
	   FRotator YawRotation(0.0f,Rotation.Yaw,0.0f);

	   FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	   AddMovementInput(Direction, Axis);
	}