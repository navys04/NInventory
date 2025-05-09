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
	 * If it is greater than object's max stack, you doing something wrong
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	int32 Count;
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
