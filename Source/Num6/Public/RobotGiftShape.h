// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "RobotGiftShape.generated.h"

/**
 * 
 */
UCLASS()
class NUM6_API ARobotGiftShape : public ABaseItem
{
	GENERATED_BODY()
	
public:
	ARobotGiftShape();

	USphereComponent* ExplosionCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Candy")
	float ExplosionDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Candy")
	float ExplosionRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Candy")
	int ExplosionDamage;

	virtual void ActivateItem(AActor* Activator) override;

	void Explode();

	FTimerHandle ExplosionTimerHandle;
};
