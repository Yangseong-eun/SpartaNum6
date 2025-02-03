// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NextLevelTrigger.generated.h"
class UBoxComponent;

UCLASS()
class NUM6_API ANextLevelTrigger : public AActor
{
    GENERATED_BODY()

public:
    ANextLevelTrigger();

protected:
    virtual void BeginPlay() override;

public:
    // 트리거 박스 (플레이어가 감지될 영역)
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UBoxComponent* TriggerBox;

    // 이동할 레벨 이름 (블루프린트에서 설정 가능)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
    FName NextLevelName;

    // 트리거 박스 이벤트 함수
    UFUNCTION()
    void OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
