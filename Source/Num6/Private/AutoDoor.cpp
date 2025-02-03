#include "AutoDoor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"

AAutoDoor::AAutoDoor()
{
    PrimaryActorTick.bCanEverTick = true;

    // 왼쪽 문 설정
    LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoor"));
    RootComponent = LeftDoor;

    // 오른쪽 문 설정
    RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoor"));
    RightDoor->SetupAttachment(RootComponent);

    // 트리거 박스 설정
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(RootComponent);
    TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
    TriggerBox->SetGenerateOverlapEvents(true);

    // 왼쪽 문은 -Y 방향, 오른쪽 문은 +Y 방향으로 이동
    LeftDoorOpenOffset = FVector(0, -100, 0);
    RightDoorOpenOffset = FVector(0, 100, 0);
}

void AAutoDoor::BeginPlay()
{
    Super::BeginPlay();

    // 초기 위치 저장
    LeftDoorStartPosition = LeftDoor->GetRelativeLocation();
    RightDoorStartPosition = RightDoor->GetRelativeLocation();

    if (TriggerBox)
    {
        TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AAutoDoor::OnTriggerEnter);
    }

    if (OpenCurve)
    {
        UE_LOG(LogTemp, Warning, TEXT("✅ OpenCurve가 정상적으로 설정됨!"));

        FOnTimelineFloat ProgressFunction;
        ProgressFunction.BindUFunction(this, FName("MoveDoor"));
        DoorTimeline.AddInterpFloat(OpenCurve, ProgressFunction);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("❌ OpenCurve가 설정되지 않았습니다!"));
    }
}

void AAutoDoor::OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->IsA(ACharacter::StaticClass()))
    {
        UE_LOG(LogTemp, Warning, TEXT("🚪 플레이어가 트리거 박스를 밟았습니다!"));

        if (!DoorTimeline.IsPlaying())
        {
            UE_LOG(LogTemp, Warning, TEXT("🚪 문이 열리는 중..."));
            DoorTimeline.PlayFromStart();
        }
    }
}

void AAutoDoor::MoveDoor(float Value)
{
    // 왼쪽 문은 왼쪽(-Y)으로 이동
    FVector NewLeftPosition = FMath::Lerp(LeftDoorStartPosition, LeftDoorStartPosition + LeftDoorOpenOffset, Value);
    LeftDoor->SetRelativeLocation(NewLeftPosition);

    // 오른쪽 문은 오른쪽(+Y)으로 이동
    FVector NewRightPosition = FMath::Lerp(RightDoorStartPosition, RightDoorStartPosition + RightDoorOpenOffset, Value);
    RightDoor->SetRelativeLocation(NewRightPosition);

    UE_LOG(LogTemp, Warning, TEXT("🚪 문 이동 값: %f"), Value);
}

void AAutoDoor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    DoorTimeline.TickTimeline(DeltaTime);
}
