#include "StaircaseTrigger.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

AStaircaseTrigger::AStaircaseTrigger()
{
    PrimaryActorTick.bCanEverTick = false;  // 틱 필요 없음
}

void AStaircaseTrigger::BeginPlay()
{
    Super::BeginPlay();

    // 트리거 박스가 설정되어 있다면 이벤트 바인딩
    if (TriggerBox)
    {
        TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AStaircaseTrigger::OnOverlapBegin);
    }

    // 계단을 기본적으로 숨김
    if (TargetStairs)
    {
        TargetStairs->SetActorHiddenInGame(true);
        TargetStairs->SetActorEnableCollision(false);
    }
}

void AStaircaseTrigger::OnOverlapBegin(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (TargetStairs)
    {
        UE_LOG(LogTemp, Warning, TEXT("계단이 나타남!"));
        TargetStairs->SetActorHiddenInGame(false);
        TargetStairs->SetActorEnableCollision(true);
    }
}
