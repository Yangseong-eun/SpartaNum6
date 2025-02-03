// Fill out your copyright notice in the Description page of Project Settings.


#include "RabbitShapeCandy.h"

ARabbitShapeCandy::ARabbitShapeCandy()
{
	CandyValue = 50;
	ItemType = "RabbitShapeCandy";
}

void ARabbitShapeCandy::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}

