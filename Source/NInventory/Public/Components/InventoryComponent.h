// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NInventoryData.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

/**
 * This component is main class for this inventory framework. You can get, use, and drop items through this component
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NINVENTORY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

	/**
	 * Tries to add item to inventory, will stack if possible, important that you should take added object version from inventory after add,
	 * because if it stacks it deletes original version of object to clean memory
	 * @param InItem Item to add
	 * @param Count Count to add (it will add this to stack, if item is stackable)
	 * @return Result enum
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TEnumAsByte<EAddItemResult> TryAddItem(UInventoryObjectBase* InItem, int32 Count = 1);

	/**
	 * Takes slot with given index from inventory
	 * @param InIndex Index to get
	 * @return Inventory slot from given index, it contains index and pointer to item
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FInventorySlot GetItemAtIndex(const int32& InIndex);
	
private:

#pragma region InternalFunctions
	/**
	 * Tries to add item to current stack if we already have this item.
	 * If it adds to stack it will destroy given item object, so if it will be true, you should take version of this object from inventory, and not use yours
	 * @param InItem Item to stack
	 * @param Count Count to stack
	 * @return True if item was successfully stacked
	 */
	bool TryToAddItemToStack(UInventoryObjectBase* InItem, const int32& Count);
#pragma endregion InternalFunctions
	
#pragma region Settings
	/**
	 * Max count of inventory slots
	 * one slot represents one cell of inventory
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Inventory|Settings", meta = (AllowPrivateAccess = "true"))
	int32 MaxItems;
#pragma endregion Settings

#pragma region InternalVariables
	/**
	 * Contains internal inventory slots, please, change this through Add / Drop item methods
	 */
	UPROPERTY()
	TArray<FInventorySlot> InventorySlots;
#pragma endregion InternalVariables
};
