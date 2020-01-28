
#include "CroshMC.h"
#include "CroshPawn.h"

void UCroshMC::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector InputVector = ConsumeInputVector();

	float speed = ((ACroshPawn*)GetOwner())->MovementSpeed;

	FHitResult Hit;
	SafeMoveUpdatedComponent(InputVector * speed * DeltaTime, UpdatedComponent->GetComponentRotation(), true, Hit);
}
