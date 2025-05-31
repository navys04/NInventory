// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NInventoryData.generated.h"

class UInventoryObjectBase;

/**
 * Contains information about item and it's current stack
 */
USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	FInventorySlot() {}
	FInventorySlot(UInventoryObjectBase* InObject, const int32& InCount) : Object(InObject), Count(InCount) {}

	/**
	 * Pointer to object
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	TObjectPtr<UInventoryObjectBase> Object;

	/**
	 * Current count of item in slot.
	 * If it is greater than object's max stack, you're doing something wrong
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	int32 Count;

	/**
	 * Is valid then object inside slot is valid and count is greater than zero
	 */
	bool IsSlotValid() const
	{
		return Object != nullptr && Count > 0;
	}
};

/**
 * Contains all base static data, you needed for inventory object
 */
USTRUCT(BlueprintType, Blueprintable)
struct FInventoryObjectStaticData : public FTableRowBase
{
	GENERATED_BODY()

	/**
	 * Item display name
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Default", meta = (AllowPrivateAccess = "true"))
	FText DisplayName;

	/**
	 * Item description
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Default", meta = (AllowPrivateAccess = "true"))
	FText Description;

	/**
	 * Item max stack
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Default", meta = (AllowPrivateAccess = "true"))
	int32 MaxStack;

	/**
	 * Unique object id, system will compare this with other object items because we need to detect if item is equal to other
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Default", meta = (AllowPrivateAccess = "true"))
	FGuid ItemID;
};

UENUM(BlueprintType)
enum EAddItemResult : uint8
{
	EADIR_Success = 0		UMETA(DisplayName = "Success"), // We successfully added item without any problems
	EADIR_NoSpace = 1		UMETA(DisplayName = "No Space"), // We cannot provide new cell for item, or add it to current item's stack
	EADIR_Failure = 2		UMETA(DisplayName = "Failure"), // Error, that is not written here, for example: given item object is not valid
};

/**
 * Global item action array, you should add here new actions if you want \n
 * Used this way, because I don't want to work with strings, this type of actions will be easier to debug, and localize for different languages
 */
UENUM(BlueprintType)
enum EItemAction : uint8
{
	EIA_Use = 0				UMETA(DisplayName = "Use")
};
