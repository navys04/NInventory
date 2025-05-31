// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"

#include "AudioMixerBlueprintLibrary.h"
#include "Algo/ForEach.h"
#include "Objects/ActionInventoryObject.h"
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
		InventorySlots.Add({ InItem, InItem->GetMaxStack() });
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

bool UInventoryComponent::TryToCallAction(const int32& ItemIndex, const TEnumAsByte<EItemAction>& ItemAction)
{
	if (!InventorySlots.IsValidIndex(ItemIndex)) return false;
	if (!InventorySlots[ItemIndex].IsSlotValid()) return false;
	
	if (UActionInventoryObject* ActionInventoryObject = Cast<UActionInventoryObject>(InventorySlots[ItemIndex].Object))
	{
		return ActionInventoryObject->TryToCallAction(ItemAction, GetOwner());
	}

	return false;
}

int32 UInventoryComponent::TryToAddItemToStack(UInventoryObjectBase* InItem, int32& Count)
{
	auto Result = 0;
	auto CopiedCount = Count; // need to rewrite all code to pass this through reference, because this code is stupid
	
	for (auto& Slot : InventorySlots)
	{
		if (InItem->GetItemID() == Slot.Object->GetItemID() || Slot.Count < InItem->GetMaxStack())
		{
			auto CountToAdd = Slot.Count + Count - Slot.Count;
			if (CountToAdd > 0)
			{
				if (Slot.Count + CountToAdd > InItem->GetMaxStack())
				{
					auto ValueToRemove = InItem->GetMaxStack() - Slot.Count;
					Slot.Count = InItem->GetMaxStack();
					Result += ValueToRemove;
					CopiedCount -= ValueToRemove;
				}

				else
				{
					Slot.Count += CountToAdd;
					Result += CountToAdd;
					CopiedCount -= CountToAdd;

					//InItem->BeginDestroy();
				}
			}
		}
	}

	return Result;
}
