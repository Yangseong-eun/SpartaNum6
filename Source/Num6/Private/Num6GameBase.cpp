// Fill out your copyright notice in the Description page of Project Settings.


#include "Num6GameBase.h"
#include "Kismet/GameplayStatics.h"
#include "Num6PlayerController.h"
#include "SpawnVolume.h"
#include "roundcandy.h"
#include "Num6GameInstance.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"


ANum6GameBase::ANum6GameBase()
{
	Score = 0;;
	SpawnedCandyCount = 0;
	CollectedCandyCount = 0;
	LevelDuration = 30;
	CurrentLevelIndex = 0;
	MaxLevels = 3;
}

void ANum6GameBase::BeginPlay()
{
	Super::BeginPlay(); // 부모 클래스 AGameState의 BeginPlay() 실행

	// 여기에 게임 상태 초기화 코드 추가
	StartLevel();
}



int32 ANum6GameBase::GetScore() const
{
	
	return Score;
}



void ANum6GameBase::AddScore(int32 Amount)
{
	Score += Amount; // ✅ 총 점수를 직접 증가시킴

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UNum6GameInstance* Num6GameInstance = Cast<UNum6GameInstance>(GameInstance);
		if (Num6GameInstance)
		{
			Num6GameInstance->AddToScore(Amount);
		}
	}

	// ✅ 점수가 500 이상이면 즉시 다음 레벨로 이동
	if (Score >= 500)
	{
		UE_LOG(LogTemp, Warning, TEXT("Score reached 500! Moving to next level."));
		EndLevel();
	}
}



void ANum6GameBase::StartLevel()
{
	UE_LOG(LogTemp, Warning, TEXT("StartLevel called! Level Duration: %.1f"), LevelDuration);

	SpawnedCandyCount = 0;
	CollectedCandyCount = 0;

	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	int32 NumVolumes = FoundVolumes.Num();
	UE_LOG(LogTemp, Warning, TEXT("Number of spawn volumes: %d"), NumVolumes);

	if (NumVolumes == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("❌ No spawn volumes found!"));
		return;
	}

	const int32 ItemToSpawn = 40;
	int32 BaseItemsPerVolume = ItemToSpawn / NumVolumes;
	int32 RemainingItems = ItemToSpawn % NumVolumes;

	for (int32 i = 0; i < NumVolumes; i++)
	{
		ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[i]);
		if (!SpawnVolume)
		{
			UE_LOG(LogTemp, Error, TEXT("❌ SpawnVolume cast failed!"));
			continue;
		}

		int32 ItemsForThisVolume = BaseItemsPerVolume;
		if (RemainingItems > 0)
		{
			ItemsForThisVolume++;
			RemainingItems--;
		}

		for (int32 j = 0; j < ItemsForThisVolume; j++)
		{
			AActor* SpawnedActor = SpawnVolume->SpawnRandomItem();

			if (!SpawnedActor)
			{
				UE_LOG(LogTemp, Error, TEXT("❌ SpawnRandomItem() returned nullptr!"));
				continue;
			}

			UE_LOG(LogTemp, Warning, TEXT("✅ Spawned Actor: %s"), *SpawnedActor->GetName());

			// ⏳ ✅ Candy인지 확인하고, 개수 증가
			if (SpawnedActor->IsA(Aroundcandy::StaticClass()))
			{
				SpawnedCandyCount++;
				UE_LOG(LogTemp, Warning, TEXT("✅ Candy Spawned: %s"), *SpawnedActor->GetName());
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("❌ Spawned Actor is NOT a candy!"));
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Total spawned candies: %d"), SpawnedCandyCount);

	if (SpawnedCandyCount == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("❌ No candies were spawned. Check SpawnVolume and SpawnRandomItem()!"));
		return;
	}

	GetWorldTimerManager().SetTimer(
		LevelTimerHandle,
		this,
		&ANum6GameBase::OnLevelTimeUp,
		LevelDuration,
		false
	);

	float TestRemainingTime = GetWorldTimerManager().GetTimerRemaining(LevelTimerHandle);
	UE_LOG(LogTemp, Warning, TEXT("📌 LevelTimerHandle RemainingTime after StartLevel: %.1f"), TestRemainingTime);

	UpdateHUD();
}




void ANum6GameBase::OnLevelTimeUp()
{
	if (SpawnedCandyCount == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No candies were spawned. Skipping level..."));
		EndLevel();
		return;
	}
}


void ANum6GameBase::EndLevel()
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UNum6GameInstance* Num6GameInstance = Cast<UNum6GameInstance>(GameInstance);
		if (Num6GameInstance)
		{
			Num6GameInstance->CurrentLevelIndex = ++CurrentLevelIndex;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Moving to Level %d"), CurrentLevelIndex);

	if (CurrentLevelIndex >= MaxLevels)
	{
		OnGameOver();
		return;
	}
	if (LevelMapNames.IsValidIndex(CurrentLevelIndex))
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[CurrentLevelIndex]);
	}
	else
	{
		OnGameOver();
	}
}

void ANum6GameBase::OnCandyCollected()
{
	if (SpawnedCandyCount > 0)
	{
		CollectedCandyCount++;
		UE_LOG(LogTemp, Warning, TEXT("Candy Collected %d / %d "), CollectedCandyCount, SpawnedCandyCount);

		// ✅ 점수 500 이상이면 레벨 종료
		if (Score >= 500)
		{
			EndLevel();
			return;
		}

		// ✅ 모든 사탕을 다 모았으면 레벨 종료
		if (CollectedCandyCount >= SpawnedCandyCount)
		{
			UE_LOG(LogTemp, Warning, TEXT("All candies collected! Moving to next level."));
			EndLevel();
		}
	}
}


void ANum6GameBase::OnGameOver()
{
	UpdateHUD();
	UE_LOG(LogTemp, Warning, TEXT("GAMEOVER!"));
}


void ANum6GameBase::UpdateHUD()
{
	UE_LOG(LogTemp, Warning, TEXT("UpdateHUD Called!")); 

	if (GEngine && GEngine->GameViewport)
	{
		ULocalPlayer* LocalPlayer = GEngine->GetFirstGamePlayer(GetWorld());
		if (LocalPlayer)
		{
			APlayerController* PlayerController = LocalPlayer->GetPlayerController(GetWorld());
			if (PlayerController)
			{
				if (ANum6PlayerController* Num6PlayerController = Cast<ANum6PlayerController>(PlayerController))
				{
					if (UUserWidget* HUDWidget = Num6PlayerController->GetHUDWidget())
					{
						// Score 업데이트
						if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Score"))))
						{
							ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), Score)));
						}

						// Timer 업데이트
						if (UTextBlock* TimerText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Time"))))
						{
							float RemainingTime = GetWorldTimerManager().GetTimerRemaining(LevelTimerHandle);
							if (RemainingTime < 0) RemainingTime = 0; 
							TimerText->SetText(FText::FromString(FString::Printf(TEXT("Time: %.1f"), RemainingTime)));
						}

						// Level 업데이트
						if (UTextBlock* LevelText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Level"))))
						{
							LevelText->SetText(FText::FromString(FString::Printf(TEXT("Level: %d"), CurrentLevelIndex + 1)));
						}
					}
				}
			}
		}
	}
}

