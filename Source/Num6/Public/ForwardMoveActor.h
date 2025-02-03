// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ForwardMoveActor.generated.h"

UCLASS()
class NUM6_API AForwardMoveActor : public AActor
{
    GENERATED_BODY()

public:
    
    AForwardMoveActor();

    virtual void Tick(float DeltaTime) override;

    void ToggleNegate();

protected:
   
    UPROPERTY(EditAnywhere, Category = "Movement")
    float MoveSpeed;

    
    UPROPERTY(EditAnywhere, Category = "Movement")
    float MoveDistance;

    
    UPROPERTY(BlueprintReadWrite, Category = "Movement")
    bool bIsNegate;

private:
    
    float CurrentDistance;

    
    bool bMovingForward;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Mesh;
};
