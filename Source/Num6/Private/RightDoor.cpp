#include "RightDoor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"

ARightDoor::ARightDoor()
{
    PrimaryActorTick.bCanEverTick = true;

    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    RootComponent = DoorMesh;

    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(RootComponent);
    TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
    TriggerBox->SetGenerateOverlapEvents(true);
}

void ARightDoor::BeginPlay()
{
    Super::BeginPlay();

    DoorStartPosition = DoorMesh->GetRelativeLocation();

    if (TriggerBox)
    {
        TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ARightDoor::OnTriggerEnter);
    }

    if (OpenCurve)
    {
        FOnTimelineFloat ProgressFunction;
        ProgressFunction.BindUFunction(this, FName("MoveDoor"));
        DoorTimeline.AddInterpFloat(OpenCurve, ProgressFunction);
    }
}

void ARightDoor::OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->IsA(ACharacter::StaticClass()))
    {
        if (!DoorTimeline.IsPlaying())
        {
            DoorTimeline.PlayFromStart();
        }
    }
}

void ARightDoor::MoveDoor(float Value)
{
    UE_LOG(LogTemp, Warning, TEXT("🚪 MoveDoor 실행됨! 값: %f"), Value);

    FVector NewPosition = FMath::Lerp(DoorStartPosition, DoorStartPosition + DoorOpenOffset, Value);
    DoorMesh->SetRelativeLocation(NewPosition);
}


void ARightDoor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    DoorTimeline.TickTimeline(DeltaTime);
}
