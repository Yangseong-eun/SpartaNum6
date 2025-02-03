// Fill out your copyright notice in the Description page of Project Settings.


#include "RoundShapeCandy.h"


ARoundShapeCandy::ARoundShapeCandy()
{
	CandyValue =10;
	ItemType = "RoundShapeCandy";
}

void ARoundShapeCandy::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}