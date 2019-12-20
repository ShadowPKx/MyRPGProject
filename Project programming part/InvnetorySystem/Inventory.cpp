#include "Inventory.h"

UInventory::UInventory()
	{
		InventorySlotLimit = 50;
		InventoryWeightLimit = 500;
	}

int32 UInventory::GetInventoryWeight()
	{
		int32 Weight = 0;
			for (auto& Item : Inventory)
				{				
					if (Item != NULL)
						{
							Weight += Item->ItemInfo.Weight;
						}
				}

		return Weight;
	}

void UInventory::AddMoney( int32 Amount )
	{
		Money += Amount;
	}

bool UInventory::AddItemToInventory( AMasterItem* Item )
	{	
		
		if (Item == nullptr)	// Если указатель - пустой
			{
				//UE_LOG(LogTemp, Log,TEXT("Item is null pointer!"));		// Debug
				return false;
			}

		if (!Item->ItemInfo.is_Stackable) // Если предмет не стакается, то 
			{		
				if ((Inventory.Num() + 1 < InventorySlotLimit) && (GetInventoryWeight() + Item->ItemInfo.Weight < InventoryWeightLimit)) // Если он проходит по весу и лимиту слотов, от
					{					
						const int32 AvaliableSlot = Inventory.Find(nullptr); // Ищем превый свободный слот
						if (AvaliableSlot != INDEX_NONE)	// Если был найден слот
							{
								//UE_LOG(LogTemp, Log,TEXT("Add item"));
								Inventory[AvaliableSlot] = Item;
								return true;
							}
					}
				else // Иначе
					{
						//UE_LOG(LogTemp, Log,TEXT("Сan't carry more items!"));	// Debug
						Item->Destroy();
						return false;
					}
			}
		else // Иначе (если стакается)
			{
				for (AMasterItem* ListItem:Inventory) // Смотрим лист на наличие такого же предмета
					{
						if (ListItem == NULL)
							{
								continue;
							}
						if (Item->ItemInfo.ItemID == ListItem->ItemInfo.ItemID) // Если находим с таким же ID
							{
								//UE_LOG(LogTemp, Log,TEXT("Found slot with same ID"));	// Debug
								int32 delta = ListItem->ItemInfo.quantity + Item->ItemInfo.quantity - ListItem->ItemInfo.max_stack_size;
								if (delta > 0) // Если предметов больше, чем в стаке
									{
										ListItem->ItemInfo.quantity = ListItem->ItemInfo.max_stack_size;
										Item->ItemInfo.quantity = delta;
										if ((Inventory.Num() + 1 < InventorySlotLimit) && (GetInventoryWeight() + Item->ItemInfo.Weight < InventoryWeightLimit))
											{
												// Ищем превый свободный слот
												const int32 AvaliableSlot = Inventory.Find(nullptr);
												if (AvaliableSlot != INDEX_NONE)
													{
														//UE_LOG(LogTemp, Log,TEXT("Item Add"));	// Debug
														Inventory[AvaliableSlot] = Item;
														return true;
													}
											}
										else
											{
												//UE_LOG(LogTemp, Log,TEXT("Сan't carry more items!"));	// Debug
												Item->Destroy();
												return true;
											}
									}
								else if (delta == 0 || delta < 0)
									{
										//UE_LOG(LogTemp, Log,TEXT("Item Add"));	// Debug
										ListItem->ItemInfo.quantity=ListItem->ItemInfo.quantity + Item->ItemInfo.quantity;
										ListItem->ItemInfo.Weight=ListItem->ItemInfo.Weight + Item->ItemInfo.Weight;
										Item->Destroy();
										return true;
									}
							}
					}
				// Сюда мы приходим, когда в List не нашли такой же предмет
				if (Inventory.Num() < InventorySlotLimit && GetInventoryWeight() + Item->ItemInfo.Weight < InventoryWeightLimit)
					{
						// Ищем превый свободный слот
						const int32 AvaliableSlot = Inventory.Find(nullptr);
						if (AvaliableSlot != INDEX_NONE)
							{
								//UE_LOG(LogTemp, Log,TEXT("Item Add"));	// Debug
								Inventory[AvaliableSlot] = Item;
								return true;
							}
					}
				else
					{
						//UE_LOG(LogTemp, Log,TEXT("Сan't carry more items!"));	// Debug
						Item->Destroy();
						return false;
					}
			}
		//UE_LOG(LogTemp, Log,TEXT("Сan't carry more items!"));	// Debug
		Item->Destroy();
		return false;
	}

UTexture2D * UInventory::GetThumbnailOfInventorySlot( int32 Slot )
	{
		if (Inventory[Slot] != NULL)
			{
				return Inventory[Slot]->ItemInfo.Thumbnail;
			}
		return nullptr;
	}

FString UInventory::GetNameOfInventorySlot( int32 Slot )
	{
		if (Inventory[Slot] != NULL)
			{
				return Inventory[Slot]->ItemInfo.ItemName;
			}
		return FString("None");
	}

void UInventory::UseItemfInventorySlot( int32 Slot )
	{
		/* Future features */
	}