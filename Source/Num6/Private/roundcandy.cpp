// Fill out your copyright notice in the Description page of Project Settings.


#include "roundcandy.h"
#include "Engine/World.h"
#include "Num6GameBase.h"



Aroundcandy::Aroundcandy()
{
	CandyValue = 0;
	ItemType = "DefaultCandy";
}

void Aroundcandy::ActivateItem(AActor* Activator)
{
    if (Activator && Activator->ActorHasTag("Player"))
    {
        if (UWorld* World = GetWorld())
        {
            if (ANum6GameBase* GameState = World->GetGameState<ANum6GameBase>())
            {
                GameState->AddScore(CandyValue);  // ✅ 캔디 점수를 추가
                GameState->OnCandyCollected();   // ✅ 사탕이 수집되었음을 알림
            }
        }
        DestroyItem();
    }
}

