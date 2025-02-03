#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "RightDoor.generated.h"

UCLASS()
class NUM6_API ARightDoor : public AActor
{
    GENERATED_BODY()

public:
    ARightDoor();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* DoorMesh;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UBoxComponent* TriggerBox;

    UPROPERTY(EditAnywhere, Category = "Door")
    FVector DoorOpenOffset = FVector(0, 100, 0); // 오른쪽(+Y)으로 이동

    UPROPERTY(EditAnywhere, Category = "Door")
    UCurveFloat* OpenCurve;

    FTimeline DoorTimeline;
    FVector DoorStartPosition;

    UFUNCTION()
    void OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void MoveDoor(float Value);
};
