// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "roundcandy.h"
#include "BoxGiftShape.generated.h"

/**
 * 
 */
UCLASS()
class NUM6_API ABoxGiftShape : public Aroundcandy
{
	GENERATED_BODY()


public:
	ABoxGiftShape();
	virtual void ActivateItem(AActor* Activator) override;
};
