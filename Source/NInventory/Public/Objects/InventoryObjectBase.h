// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NInventoryData.h"
#include "UObject/Object.h"
#include "InventoryObjectBase.generated.h"

/**
 * This class contains static, and dynamic info about inventory object
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class NINVENTORY_API UInventoryObjectBase : public UObject
{
	GENERATED_BODY()

friend class UInventoryComponent;
	
public:

#pragma region Getters
	/**
	 * Returns display name of inventory item
	 */
	UFUNCTION(BlueprintPure, Category = "Inventory")
	FORCEINLINE FText GetDisplayName() const { return StaticData.DisplayName; }

	/**
	 * Returns description of inventory item
	 */
	UFUNCTION(BlueprintPure, Category = "Inventory")
	FORCEINLINE FText GetDescription() const { return StaticData.Description; }

	/**
	 * Returns max stack of inventory item
	 */
	UFUNCTION(BlueprintPure, Category = "Inventory")
	FORCEINLINE int32 GetMaxStack() const { return StaticData.MaxStack; }

	/**
	 * Returns unique id of inventory item
	 */
	UFUNCTION(BlueprintPure, Category = "Inventory")
	FORCEINLINE FGuid GetItemID() const { return StaticData.ItemID; }
#pragma endregion Getters
	
private:

#pragma region ItemBaseInfo
	/**
	 * Static inventory object data
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory",
		meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true"))
	FInventoryObjectStaticData StaticData;
#pragma endregion ItemBaseInfo
};
