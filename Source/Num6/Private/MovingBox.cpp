#include "MovingBox.h"

AMovingBox::AMovingBox()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMovingBox::BeginPlay()
{
    Super::BeginPlay();

    StartLocation = GetActorLocation();
    TargetLocation = StartLocation + FVector(MoveDistance, 0, 0); // 앞뒤 이동
}

void AMovingBox::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FVector CurrentLocation = GetActorLocation();
    float DistanceMoved = FVector::Dist(CurrentLocation, StartLocation);

    // 목표 위치 도달 시 방향 변경
    if (DistanceMoved >= MoveDistance)
    {
        Direction *= -1.0f;
    }

    // 새로운 위치 계산
    FVector NewLocation = CurrentLocation + FVector(Direction * MoveSpeed * DeltaTime, 0, 0);
    SetActorLocation(NewLocation);
}
