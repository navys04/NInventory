// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"

#include "Algo/ForEach.h"
#include "Objects/InventoryObjectBase.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	MaxItems = 32;
}

TEnumAsByte<EAddItemResult> UInventoryComponent::TryAddItem(UInventoryObjectBase* InItem, int32 Count)
{
	if (!IsValid(InItem)) return EADIR_Failure;
	if (InventorySlots.Num() == MaxItems) return EADIR_NoSpace;
	if (TryToAddItemToStack(InItem, Count)) return EADIR_Success;
	
	InventorySlots.Add({ InItem, Count });
	return EADIR_Success;
}

FInventorySlot UInventoryComponent::GetItemAtIndex(const int32& InIndex)
{
	if (InventorySlots.IsValidIndex(InIndex)) return InventorySlots[InIndex];

	return FInventorySlot();
}

bool UInventoryComponent::TryToAddItemToStack(UInventoryObjectBase* InItem, const int32& Count)
{
	auto Result = false;
	
	Algo::ForEach(InventorySlots, [&](FInventorySlot& Slot)
	{
		if (InItem->GetItemID() == Slot.Object->GetItemID() && Slot.Count + Count <= Slot.Object->GetMaxStack())
		{
			Slot.Count += Count;
			InItem->BeginDestroy(); // We destroy original item object, to clean up memory, because we don't need it after this procedure
			Result = true;
		}
	});

	return Result;
}
