#include "ElevatorTrigger.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

AElevatorTrigger::AElevatorTrigger()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AElevatorTrigger::BeginPlay()
{
    Super::BeginPlay();

    if (TriggerBox)
    {
        TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AElevatorTrigger::OnTriggerEnter);
    }

    if (TargetElevator)
    {
        StartPosition = TargetElevator->GetActorLocation();

        // TargetEndPosition이 설정되었을 경우 해당 위치를 EndPosition으로 사용
        if (TargetEndPosition)
        {
            EndPosition = TargetEndPosition->GetActorLocation();
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("TargetEndPosition이 설정되지 않았습니다!"));
        }
    }
}

// 엘리베이터가 부드럽게 이동하도록 설정
void AElevatorTrigger::MoveElevator(float Value)
{
    if (TargetElevator)
    {
        FVector NewPosition = FMath::Lerp(StartPosition, EndPosition, Value);
        TargetElevator->SetActorLocation(NewPosition);
    }
}


void AElevatorTrigger::OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->IsA(ACharacter::StaticClass()))
    {
        UE_LOG(LogTemp, Warning, TEXT("트리거 박스 활성화됨! 엘리베이터 이동 시작"));

        if (TargetElevator)
        {
            ElevatorTimeline.PlayFromStart();
        }
    }
}

