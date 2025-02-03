#include "MovingRotatingActor.h"

AMovingRotatingActor::AMovingRotatingActor()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMovingRotatingActor::BeginPlay()
{
    Super::BeginPlay();

    StartLocation = GetActorLocation();

    // ✅ 이동 방향 설정
    Direction = bReverseMovement ? -1 : 1;

    // ✅ 목표 위치 설정 (X축 이동)
    TargetLocation = StartLocation + FVector(0, MoveDistance * Direction, 0);
}

void AMovingRotatingActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FVector CurrentLocation = GetActorLocation();
    FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, MoveSpeed);

    // ✅ 비정상적인 위치 체크
    if (!FMath::IsFinite(NewLocation.X) || !FMath::IsFinite(NewLocation.Y) || !FMath::IsFinite(NewLocation.Z))
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid Position Detected! Resetting MovingRotatingActor to StartLocation."));
        SetActorLocation(StartLocation);
        return;
    }

    // ✅ 액터 이동
    SetActorLocation(NewLocation);

    // ✅ 회전 추가 (Y축 기준 회전)
    FRotator CurrentRotation = GetActorRotation();
    FRotator NewRotation = CurrentRotation + FRotator(0, RotationSpeed * DeltaTime, 0);
    SetActorRotation(NewRotation);

    // ✅ 목표 지점에 도달했으면 방향 반전
    if (FVector::Dist(CurrentLocation, TargetLocation) < 10.0f)
    {
        Direction *= -1; // 방향 반전
        TargetLocation = StartLocation + FVector(0, MoveDistance * Direction, 0);
    }
}
