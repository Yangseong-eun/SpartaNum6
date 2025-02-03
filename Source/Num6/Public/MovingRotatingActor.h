// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingRotatingActor.generated.h"

UCLASS()
class NUM6_API AMovingRotatingActor : public AActor
{
    GENERATED_BODY()

public:
    AMovingRotatingActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    // ✅ 이동 속도 (초당 이동 거리)
    UPROPERTY(EditAnywhere, Category = "Movement")
    float MoveSpeed = 100.0f;

    // ✅ 최대 이동 거리 (좌우로 이동하는 범위)
    UPROPERTY(EditAnywhere, Category = "Movement")
    float MoveDistance = 500.0f;

    // ✅ 이동 반전 여부 (체크하면 반대 방향으로 이동)
    UPROPERTY(EditAnywhere, Category = "Movement")
    bool bReverseMovement = false;

    // ✅ 회전 속도 (초당 회전 각도)
    UPROPERTY(EditAnywhere, Category = "Rotation")
    float RotationSpeed = 100.0f;

    FVector StartLocation;  // 초기 위치
    FVector TargetLocation; // 목표 위치
    int32 Direction;  // 이동 방향 (1 또는 -1)

};
