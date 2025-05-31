// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/ActionInventoryObject.h"

bool UActionInventoryObject::TryToCallAction_Implementation(const TEnumAsByte<EItemAction>& Action, const AActor* Instigator)
{
	if (!Actions.Contains(Action)) return false;

	// just returning true, don't have any logic here
	return true;
}

UActionInventoryObject::UActionInventoryObject()
{
	Actions.Add(EIA_Use);
}
