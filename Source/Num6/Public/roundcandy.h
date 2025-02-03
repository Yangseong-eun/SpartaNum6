// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "roundcandy.generated.h"

/**
 * 
 */
UCLASS()
class NUM6_API Aroundcandy : public ABaseItem
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Candy")
	int32 CandyValue;

	Aroundcandy();

	virtual void ActivateItem(AActor* Activator) override;

};
