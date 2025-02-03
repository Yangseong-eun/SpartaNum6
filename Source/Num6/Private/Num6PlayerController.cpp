#include "Num6PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Num6GameBase.h"

ANum6PlayerController::ANum6PlayerController()
	: InputMappingContext(nullptr),
	MoveAction(nullptr),
	LookAction(nullptr),
	SprintAction(nullptr),
	JumpAction(nullptr),
	HUDWidgetClass(nullptr)
{
}

void ANum6PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 1);
			}
		}
	}

	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("❌ HUDWidgetInstance 생성 실패!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("❌ HUDWidgetClass가 설정되지 않음!"));
	}

	ANum6GameBase* Num6GameState = GetWorld() ? GetWorld()->GetGameState<ANum6GameBase>() : nullptr;
	if (Num6GameState)
	{
		Num6GameState->UpdateHUD();
		UE_LOG(LogTemp, Warning, TEXT("✅ UpdateHUD() 호출됨"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("❌ GameState가 NULL!"));
	}
}

UUserWidget* ANum6PlayerController::GetHUDWidget() const
{
	return HUDWidgetInstance;
}

