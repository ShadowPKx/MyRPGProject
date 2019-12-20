#include "MasterItem.h"
#include "Sources/PlayerHero.h"

// Sets default values
AMasterItem::AMasterItem()
	{
		HelpText = FString("Press E to interact with item.");
		ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("Item Mesh");
		ItemMesh->SetSimulatePhysics(true);
	}

// Called when the game starts or when spawned
void AMasterItem::BeginPlay()
	{
		Super::BeginPlay();
	}

void AMasterItem::Interact_Implementation()
	{
		APlayerHero* Character = Cast<APlayerHero>(UGameplayStatics::GetPlayerCharacter(this,0));
		Character->CharacterInventory->AddItemToInventory(this);
		ItemMesh->SetVisibility(false);
		ItemMesh->SetSimulatePhysics(false);
		ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}