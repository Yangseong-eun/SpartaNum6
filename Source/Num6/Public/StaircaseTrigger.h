#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StaircaseTrigger.generated.h"

class UBoxComponent;

UCLASS()
class NUM6_API AStaircaseTrigger : public AActor
{
    GENERATED_BODY()

public:
    AStaircaseTrigger();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, Category = "Components")
    UBoxComponent* TriggerBox;  // 에디터에서 설정 가능하도록 변경

    UPROPERTY(EditAnywhere, Category = "Staircase")
    AActor* TargetStairs;  // 나타날 계단 오브젝트

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);
};
