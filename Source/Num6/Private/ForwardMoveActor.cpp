// ForwardMoveActor.cpp
#include "ForwardMoveActor.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"

// Sets default values
AForwardMoveActor::AForwardMoveActor()
{
    PrimaryActorTick.bCanEverTick = true;


    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;

    MoveSpeed = 200.0f;
    MoveDistance = 500.0f;
    bIsNegate = false;
    bMovingForward = true;
    CurrentDistance = 0.0f;
}

// Called every frame
void AForwardMoveActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

 
    float Direction = (bMovingForward ^ bIsNegate) ? 1.0f : -1.0f;
    float DeltaMove = Direction * MoveSpeed * DeltaTime;

    FVector NewLocation = GetActorLocation();
    NewLocation.X += DeltaMove;
    SetActorLocation(NewLocation);

    CurrentDistance += DeltaMove;

    
    if (FMath::Abs(CurrentDistance) >= MoveDistance)
    {
        CurrentDistance = FMath::Clamp(CurrentDistance, -MoveDistance, MoveDistance);
        bMovingForward = !bMovingForward;
    }
}

void AForwardMoveActor::ToggleNegate()
{
    bIsNegate = !bIsNegate;
}
