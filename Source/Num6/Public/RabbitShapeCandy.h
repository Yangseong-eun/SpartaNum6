// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "roundcandy.h"
#include "RabbitShapeCandy.generated.h"

/**
 * 
 */
UCLASS()
class NUM6_API ARabbitShapeCandy : public Aroundcandy
{
	GENERATED_BODY()
	

protected:


	ARabbitShapeCandy();

	virtual void ActivateItem(AActor* Activator) override;
};
