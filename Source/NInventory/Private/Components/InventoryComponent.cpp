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

	auto CountToAdd = Count;

	const auto AddedCount = TryToAddItemToStack(InItem, Count);
	if (AddedCount == Count)
	{
		return EADIR_Success;
	}
	
	CountToAdd -= AddedCount;
	while (CountToAdd > InItem->GetMaxStack())
	{
		InventorySlots.Add({ InItem, CountToAdd });
		CountToAdd -= InItem->GetMaxStack();
	}

	if (CountToAdd > 0)
	{
		InventorySlots.Add({ InItem, CountToAdd });
	}
	
	return EADIR_Success;
}

FInventorySlot UInventoryComponent::GetItemAtIndex(int32 InIndex)
{
	if (InventorySlots.IsValidIndex(InIndex)) return InventorySlots[InIndex];

	return FInventorySlot();
}

FInventorySlot UInventoryComponent::GetItemByID(const FGuid& InID)
{
	for (auto& Slot : InventorySlots)
	{
		if (Slot.Object->GetItemID() == InID) return Slot;
	}
	
	return FInventorySlot();
}

FInventorySlot UInventoryComponent::GetItemByClass(const TSubclassOf<UInventoryObjectBase> ObjectClass)
{
	for (auto& Slot : InventorySlots)
	{
		if (Slot.Object->StaticClass() == ObjectClass) return Slot;
	}
	
	return FInventorySlot();
}

const TArray<FInventorySlot>& UInventoryComponent::GetSlots() const
{
	return InventorySlots;
}

int32 UInventoryComponent::TryToAddItemToStack(UInventoryObjectBase* InItem, const int32& Count)
{
	auto Result = 0;
	
	for (auto& Slot : InventorySlots)
	{
		const auto CountToAdd = Slot.Object->GetMaxStack() - Slot.Count + Count;
		if (InItem->GetItemID() == Slot.Object->GetItemID() && CountToAdd > 0)
		{
			Slot.Count += CountToAdd;
			if (CountToAdd == Count) InItem->BeginDestroy(); // We destroy original item object, to clean up memory, because we don't need it after this procedure
			Result += CountToAdd;
		}
	}

	return Result;
}
