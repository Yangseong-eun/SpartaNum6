#include "PoppingWall.h"

APoppingWall::APoppingWall()
{
    PrimaryActorTick.bCanEverTick = true;
}

void APoppingWall::BeginPlay()
{
    Super::BeginPlay();

    StartLocation = GetActorLocation();
    TargetLocation = StartLocation + FVector(-MoveDistance, 0, 0); // 앞으로 튀어나올 방향
    bMovingOut = true;
    Timer = 0.0f;
}

void APoppingWall::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FVector CurrentLocation = GetActorLocation();
    FVector DesiredLocation = bMovingOut ? TargetLocation : StartLocation;

    // 이동 보간
    FVector NewLocation = FMath::VInterpTo(CurrentLocation, DesiredLocation, DeltaTime, MoveSpeed);

    // ✅ 비정상적인 위치 값 체크
    if (!FMath::IsFinite(NewLocation.X) || !FMath::IsFinite(NewLocation.Y) || !FMath::IsFinite(NewLocation.Z))
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid Position Detected! Resetting PoppingWall to StartLocation."));
        SetActorLocation(StartLocation);
        return;
    }

    SetActorLocation(NewLocation);

    // 일정 시간 후 방향 변경
    Timer += DeltaTime;
    if (Timer >= DelayTime)
    {
        bMovingOut = !bMovingOut;
        Timer = 0.0f;
    }
}
