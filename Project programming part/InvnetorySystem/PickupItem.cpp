#include "PickupItem.h"
#include "Sources/PlayerHero.h"

APickupItem::APickupItem()
	{
		//	Устанавливаем mesh для pickup
		ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
		ItemMesh->SetSimulatePhysics(true);

		HelpText = FString("Press E to pick item up.");
	}

void APickupItem::BeginPlay()
	{
		HelpText = FString::Printf(TEXT("%s : Press E to pick up."),*(ItemInfo.ItemName));
	}


void APickupItem::Interact_Implementation()
	{
		APlayerHero* Character = Cast<APlayerHero>(UGameplayStatics::GetPlayerCharacter(this,0));
		//Put code here that places item into characters inventory

		OnPickedUp();
		 UE_LOG(LogTemp, Log,TEXT("Add item")); 
		//Character->CharacterInventory->AddItemToInventory(this);
		 
	}

void APickupItem::Use_Implementation()
	{
		GLog->Log("Use() from pickup class : YOU SHOULD NOT BE SEEING THIS");
	}

void APickupItem::OnPickedUp()
	{
		ItemMesh->SetVisibility(false);
		ItemMesh->SetSimulatePhysics(false);
		ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
