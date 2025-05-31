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

#pragma region AddFunctions
	/**
	 * Tries to add item to inventory, will stack if possible, important that you should take added object version from inventory after add,
	 * because if it stacks it deletes original version of object to clean memory
	 * @param InItem Item to add
	 * @param Count Count to add (it will add this to stack, if item is stackable)
	 * @return Result enum
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TEnumAsByte<EAddItemResult> TryAddItem(UInventoryObjectBase* InItem, int32 Count = 1);
#pragma endregion AddFunctions

#pragma region GetFunctions
	/**
	 * Takes slot with given index from inventory
	 * @param InIndex Index to get
	 * @return Inventory slot from given index, it contains index and pointer to item
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FInventorySlot GetItemAtIndex(int32 InIndex);

	/**
	 * Takes slot with FIRST ITEM of given id from inventory
	 * @param InID ID of item to get
	 * @return Inventory slot with item of given id, it contains index and pointer to item
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FInventorySlot GetItemByID(const FGuid& InID);

	/**
	 * Takes slot with FIRST ITEM of given class from inventory
	 * @param ObjectClass Class of object to get
	 * @return Inventory slot with item of given class, it contains index and pointer to item
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FInventorySlot GetItemByClass(TSubclassOf<UInventoryObjectBase> ObjectClass);

	/**
	 * Takes all inventory slots, it is protected by const keyword, because you don't need to change items like that, using this array
	 * This is for UX/UI, to display items to player. (idk, you also can create your own pattern, to display IT!)
	 * @return All inventory slots
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	const TArray<FInventorySlot>& GetSlots() const; 
#pragma endregion GetFunctions

#pragma region Item Workflow Functions
	/**
	 * Tries to call action on given item. \n
	 * It will work if item can handle actions and this action exists in it. By default, instigator for action is owner of this component.
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool TryToCallAction(const int32& ItemIndex, const TEnumAsByte<EItemAction>& ItemAction);
#pragma endregion Item Workflow Functions
	
	
private:

#pragma region InternalFunctions
	/**
	 * Tries to add item to current stack if we already have this item.
	 * If it adds to stack overall count it will destroy given item object you should take version of this object from inventory, and not use yours
	 * @param InItem Item to stack
	 * @param Count Count to stack
	 * @return Count of added items
	 */
	int32 TryToAddItemToStack(UInventoryObjectBase* InItem, int32& Count);
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
