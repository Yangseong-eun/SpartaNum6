#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "AutoDoor.generated.h"
UENUM(BlueprintType)
enum class EDoorType : uint8
{
    SingleDoor UMETA(DisplayName = "Single Door"),
    DoubleDoor UMETA(DisplayName = "Double Door")
};

UCLASS()
class NUM6_API AAutoDoor : public AActor
{
    GENERATED_BODY()

public:
    AAutoDoor();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DelaTime) override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Type")
    EDoorType DoorType;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* LeftDoor;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* RightDoor;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UBoxComponent* TriggerBox;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
    FVector LeftDoorOpenOffset = FVector(0, -100, 0); // Y축 방향 이동 (왼쪽)

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
    FVector RightDoorOpenOffset = FVector(0, 100, 0); // Y축 방향 이동 (오른쪽)


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
    UCurveFloat* OpenCurve;


    UPROPERTY()
    FTimeline DoorTimeline;

    UFUNCTION()
    void OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION(BlueprintCallable)
    void MoveDoor(float Value);


private:
    FVector LeftDoorStartPosition;
    FVector RightDoorStartPosition;
};

