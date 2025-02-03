
#include "RotateActor.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"

// Sets default values
ARotateActor::ARotateActor()
{
    PrimaryActorTick.bCanEverTick = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;


    RotationSpeed = FRotator(0.0f, 90.0f, 0.0f); 
}

void ARotateActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FRotator NewRotation = GetActorRotation() + (RotationSpeed * DeltaTime);
    SetActorRotation(NewRotation);
}

void ARotateActor::SetRotationSpeed(FRotator NewSpeed)
{
    RotationSpeed = NewSpeed;
}
