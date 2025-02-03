// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotateActor.generated.h"

UCLASS()
class NUM6_API ARotateActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ARotateActor();

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Set rotation speed dynamically
    void SetRotationSpeed(FRotator NewSpeed);

protected:
    // Rotation speed per second
    UPROPERTY(EditAnywhere, Category = "Rotation")
    FRotator RotationSpeed;

    // Mesh component
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Mesh;

};
