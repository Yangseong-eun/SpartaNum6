// Fill out your copyright notice in the Description page of Project Settings.


#include "Num6GameInstance.h"

UNum6GameInstance::UNum6GameInstance()
{
	TotalScore = 0;
	CurrentLevelIndex = 0;;
}

void UNum6GameInstance::AddToScore(int32 Amount)
{
	TotalScore += Amount;
	UE_LOG(LogTemp, Warning, TEXT("TotalScore Updated: %d"), TotalScore);
}
