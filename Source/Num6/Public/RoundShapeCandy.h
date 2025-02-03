// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "roundcandy.h"
#include "RoundShapeCandy.generated.h"

/**
 * 
 */
UCLASS()
class NUM6_API ARoundShapeCandy : public Aroundcandy
{
	GENERATED_BODY()

public:
	ARoundShapeCandy();

	virtual void ActivateItem(AActor* Activator) override;

	
};
