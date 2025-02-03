// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingBox.generated.h"

UCLASS()
class NUM6_API AMovingBox : public AActor
{
    GENERATED_BODY()

public:
    AMovingBox();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    FVector StartLocation;
    FVector TargetLocation;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float MoveDistance = 300.0f; // 이동 거리 (앞뒤 왕복 거리)

    UPROPERTY(EditAnywhere, Category = "Movement")
    float MoveSpeed = 200.0f; // 이동 속도

    float Direction = 1.0f; // 이동 방향 (1: 앞으로, -1: 뒤로)

};
