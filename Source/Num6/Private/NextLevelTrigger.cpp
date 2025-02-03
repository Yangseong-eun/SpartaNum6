#include "NextLevelTrigger.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

ANextLevelTrigger::ANextLevelTrigger()
{
    PrimaryActorTick.bCanEverTick = false;

    // 트리거 박스 생성 및 설정
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;
    TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
    TriggerBox->SetGenerateOverlapEvents(true);
}

void ANextLevelTrigger::BeginPlay()
{
    Super::BeginPlay();

    if (TriggerBox)
    {
        TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ANextLevelTrigger::OnTriggerEnter);
    }
}

void ANextLevelTrigger::OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->IsA(ACharacter::StaticClass()))
    {
        UE_LOG(LogTemp, Warning, TEXT("다음 레벨로 이동: %s"), *NextLevelName.ToString());

        // 다음 레벨 로드
        if (!NextLevelName.IsNone())
        {
            UGameplayStatics::OpenLevel(this, NextLevelName);
        }
    }
}
