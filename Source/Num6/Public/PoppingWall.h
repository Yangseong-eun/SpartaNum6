// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoppingWall.generated.h"

UCLASS()
class NUM6_API APoppingWall : public AActor
{
    GENERATED_BODY()

public:
    APoppingWall();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(EditAnywhere, Category = "Movement")
    float MoveDistance = 300.0f;  // 최대 이동 거리

    UPROPERTY(EditAnywhere, Category = "Movement")
    float MoveSpeed = 5.0f;  // 이동 속도 (값을 줄여 더 부드럽게)

    UPROPERTY(EditAnywhere, Category = "Movement")
    float DelayTime = 3.0f;  // 장애물이 다시 들어가기 전 대기 시간

    FVector StartLocation;
    FVector TargetLocation;
    bool bMovingOut;
    float Timer;
};
