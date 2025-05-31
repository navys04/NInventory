// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryObjectBase.h"
#include "UObject/Object.h"
#include "ActionInventoryObject.generated.h"

/**
 * This class contains information about actions \n
 * Action is some part of logic, that can be called by user from UI, like "Use", "Repair" and others
 */
UCLASS()
class NINVENTORY_API UActionInventoryObject : public UInventoryObjectBase
{
	GENERATED_BODY()

public:
	UActionInventoryObject();

#pragma region Action Methods
	/**
	 *  Tries to call given action. By default, is empty, just checks if this object contains action, but you can override and your own logic for actions
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "ActionInventoryObject")
	bool TryToCallAction(const TEnumAsByte<EItemAction>& Action, const AActor* Instigator);
#pragma endregion Action Methods
	
	
private:
#pragma region Action Inventory Object Info
	/**
	 * List of actions, that can be used by this item
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Action", meta = (AllowPrivateAccess = "true"))
	TArray<TEnumAsByte<EItemAction>> Actions;
#pragma endregion Action Inventory Object Info
};
