#include "InventoryItem.h"

FInventoryItem::FInventoryItem()
	{
		ItemName = "No Name";
		Weight = 1;
		Value = 1;
		Description = "No Description";
		CanBeUsed = false;
		is_Stackable = false;
		Thumbnail = NULL;
		ItemCategory = EItemCategories::Consumable;
		quantity = 0;
		max_stack_size = 0;
	}