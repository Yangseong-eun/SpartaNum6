#include "RotatingBox.h"

ARotatingBox::ARotatingBox()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ARotatingBox::BeginPlay()
{
    Super::BeginPlay();
}

void ARotatingBox::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 현재 회전 값 가져오기
    FRotator CurrentRotation = GetActorRotation();

    // 새로운 회전 값 계산
    FRotator NewRotation = CurrentRotation + (RotationSpeed * DeltaTime);

    // 엑터에 회전 적용
    SetActorRotation(NewRotation);
}
