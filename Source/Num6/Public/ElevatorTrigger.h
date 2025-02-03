#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "ElevatorTrigger.generated.h"

UCLASS()
class NUM6_API AElevatorTrigger : public AActor
{
    GENERATED_BODY()

public:
    AElevatorTrigger();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, Category = "Elevator")
    UBoxComponent* TriggerBox;  // 트리거 박스 (에디터에서 설정)

    UPROPERTY(EditAnywhere, Category = "Elevator")
    AActor* TargetElevator; // 엘리베이터 오브젝트

    UPROPERTY(EditAnywhere, Category = "Elevator")
    FVector EndPosition; // 최종 위치

    UPROPERTY()
    FTimeline ElevatorTimeline;

    UFUNCTION()
    void OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void MoveElevator(float Value);



private:
    FVector StartPosition; // 시작 위치
    UPROPERTY(EditAnywhere, Category = "Elevator")
    AActor* TargetEndPosition; // 엘리베이터의 끝 위치를 지정할 액터

};
