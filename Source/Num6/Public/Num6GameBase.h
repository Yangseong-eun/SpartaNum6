#pragma once  // 헤더 파일 중복 포함 방지

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Num6GameBase.generated.h"

UCLASS()
class NUM6_API ANum6GameBase : public AGameState
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;
    ANum6GameBase();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Score")
    int32 Score;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Candy")
    int32 SpawnedCandyCount;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Candy")
    int32 CollectedCandyCount;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
    float LevelDuration;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
    int32 CurrentLevelIndex;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
    int32 MaxLevels;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
    TArray<FName> LevelMapNames;

    FTimerHandle LevelTimerHandle;
    FTimerHandle HUDUpdateTimerHandle;

    UFUNCTION(BlueprintPure, Category = "Score")
    int32 GetScore() const;

    UFUNCTION(BlueprintCallable, Category = "Score")
    void AddScore(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Level")
    void OnGameOver();

    void OnLevelTimeUp();
    void StartLevel();
    void EndLevel();
    void OnCandyCollected();
    void UpdateHUD();
};
