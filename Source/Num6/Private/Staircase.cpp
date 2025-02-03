#include "Staircase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

AStaircase::AStaircase()
{
    PrimaryActorTick.bCanEverTick = false;

    // ✅ 계단 메시 생성
    StairMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StairMesh"));
    RootComponent = StairMesh;

    // ✅ 트리거 박스 생성
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(RootComponent);
    TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
}

void AStaircase::BeginPlay()
{
    Super::BeginPlay();

    if (TriggerBox)
    {
        TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AStaircase::OnTriggerEnter);
    }

    // ✅ 계단을 처음엔 숨기기
    StairMesh->SetVisibility(false);
    StairMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AStaircase::OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->IsA(ACharacter::StaticClass()))
    {
        UE_LOG(LogTemp, Warning, TEXT("계단이 나타남!"));
        StairMesh->SetVisibility(true);
        StairMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

        // ✅ 트리거 비활성화 (한 번만 실행)
        if (TriggerBox)
        {
            TriggerBox->OnComponentBeginOverlap.RemoveDynamic(this, &AStaircase::OnTriggerEnter);
        }
    }
}
