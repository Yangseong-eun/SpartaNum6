#include "Num6GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Num6Character.h"
#include "Num6GameBase.h"

ANum6GameMode::ANum6GameMode()
{

    GameStateClass = ANum6GameBase::StaticClass();
}


