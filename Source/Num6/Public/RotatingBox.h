// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingBox.generated.h"

UCLASS()
class NUM6_API ARotatingBox : public AActor
{
    GENERATED_BODY()

public:
    ARotatingBox();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(EditAnywhere, Category = "Rotation")
    FRotator RotationSpeed = FRotator(0, 90.0f, 0); // 초당 회전 속도 (Y축 90도 회전)

};
