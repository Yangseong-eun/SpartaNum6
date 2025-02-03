// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxGiftShape.h"

ABoxGiftShape::ABoxGiftShape()
{
	CandyValue = -20;
}

void ABoxGiftShape::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}
