// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "Components/BoxComponent.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(Scene);

	ItemDataTable = nullptr;

}

FVector ASpawnVolume::GetRandomPointInVolume() const
{
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
	FVector BoxOrigin = SpawningBox->GetComponentLocation();

	return BoxOrigin + FVector(
		FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
		FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
		FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
	);
}

AActor* ASpawnVolume::SpawnItem(TSubclassOf<AActor> ItemClass)
{
	if (!ItemClass) return nullptr;
	AActor* SpawnedActor= GetWorld()->SpawnActor<AActor>(
		ItemClass,
		GetRandomPointInVolume(),
		FRotator::ZeroRotator
	);

	return SpawnedActor;
}

AActor* ASpawnVolume::SpawnRandomItem()
{
	UE_LOG(LogTemp, Warning, TEXT("🔍 SpawnRandomItem() called in %s"), *GetName());

	if (FItemSpawnRow* SelectedRow = GetRandomItem())
	{
		if (UClass* ActualClass = SelectedRow->ItemClass.Get())
		{
			UE_LOG(LogTemp, Warning, TEXT("🎯 Selected item: %s"), *ActualClass->GetName());

			AActor* SpawnedActor = SpawnItem(ActualClass);
			if (SpawnedActor)
			{
				UE_LOG(LogTemp, Warning, TEXT("✅ Spawned Actor: %s"), *SpawnedActor->GetName());
				return SpawnedActor;
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("❌ Failed to spawn actor!"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("❌ Selected Item Class is NULL!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("❌ GetRandomItem() returned NULL!"));
	}

	return nullptr;
}


FItemSpawnRow* ASpawnVolume::GetRandomItem() const
{
	if (!ItemDataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("❌ GetRandomItem() - ItemDataTable is NULL!"));
		return nullptr;
	}

	TArray<FItemSpawnRow*> AllRows;
	static const FString ContextString(TEXT("ItemSpawnContext"));
	ItemDataTable->GetAllRows(ContextString, AllRows);

	if (AllRows.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("❌ GetRandomItem() - No rows found in ItemDataTable!"));
		return nullptr;
	}

	float TotalChance = 0.0f;
	for (const FItemSpawnRow* Row : AllRows)
	{
		if (Row)
		{
			TotalChance += Row->SpawnChance;
			UE_LOG(LogTemp, Warning, TEXT("Item: %s, SpawnChance: %.2f"), *Row->ItemClass->GetName(), Row->SpawnChance);
		}
	}

	if (TotalChance <= 0.0f)
	{
		UE_LOG(LogTemp, Error, TEXT("❌ GetRandomItem() - Total spawn chance is 0! Check DataTable values."));
		return nullptr;
	}

	const float RandValue = FMath::FRandRange(0.0f, TotalChance);
	float AccumulateChance = 0;

	for (FItemSpawnRow* Row : AllRows)
	{
		AccumulateChance += Row->SpawnChance;
		if (RandValue <= AccumulateChance)
		{
			UE_LOG(LogTemp, Warning, TEXT("✅ Selected item: %s"), *Row->ItemClass->GetName());
			return Row;
		}
	}

	return nullptr;
}



