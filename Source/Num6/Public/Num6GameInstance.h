// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Num6GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class NUM6_API UNum6GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:

	UNum6GameInstance();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category="GameData")
	int32 TotalScore;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 CurrentLevelIndex;
	
	UFUNCTION(BlueprintCallable, Category = "GameData")
	void AddToScore(int32 Amount);
};
