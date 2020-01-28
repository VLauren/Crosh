
#include "CroshMC.h"
#include "CroshPawn.h"
#include "DrawDebugHelpers.h"

void UCroshMC::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Movimiento Horizontal

	float speed = ((ACroshPawn*)GetOwner())->MovementSpeed;
	FVector InputVector = ConsumeInputVector().GetClampedToMaxSize(1.0f);

	FHitResult Hit;
	TickMove = FMath::Lerp(TickMove, InputVector * speed * DeltaTime, 0.2f);
	SafeMoveUpdatedComponent(TickMove, UpdatedComponent->GetComponentRotation(), true, Hit);

	// Movimiento Vertical

	float gravityStrength = ((ACroshPawn*)GetOwner())->GravityStrength;

	if (IsGrounded() && jumpFrames <= 0)
		ZVel = 0;
	else 
		ZVel -= gravityStrength * DeltaTime;

	SafeMoveUpdatedComponent(FVector::UpVector * ZVel * DeltaTime * 60, UpdatedComponent->GetComponentRotation(), true, Hit);
	if (Hit.IsValidBlockingHit())
		SlideAlongSurface(FVector(0, 0, ZVel) * DeltaTime * 60, 1.f - Hit.Time, Hit.Normal, Hit);

	if (jumpFrames > 0)
		jumpFrames--;

	// Orientacion del modelo
	if (!InputVector.IsNearlyZero())// && IsGrounded() && jumpFrames <= 0)
	{
		// Target rotation
		FRotator ctrlRot = InputVector.Rotation();
		// float rotLerpSpeed = ((ACroshPawn*)GetOwner())->RotationLerpSpeed;
		float rotLerpSpeed = 0.1f;

		// Rotate character towards target rotation
		CurrentRotation = FMath::Lerp(CurrentRotation, ctrlRot, rotLerpSpeed);
		UpdatedComponent->GetOwner()->SetActorRotation(CurrentRotation);
	}
}

void UCroshMC::Jump()
{
	float jumpStrength = ((ACroshPawn*)GetOwner())->JumpStrength;
	ZVel = jumpStrength;
	jumpFrames = 3;
}

bool UCroshMC::CheckGroundedAtPosition(FVector Position)
{
	float Radius = Cast<UCapsuleComponent>(UpdatedComponent)->GetScaledCapsuleRadius();

	FHitResult OutHit;
	FCollisionQueryParams ColParams;

	ColParams.AddIgnoredActor(GetOwner());

	if (GetWorld()->SweepSingleByChannel(OutHit, Position, Position - FVector::UpVector * 3, FQuat::Identity, ECollisionChannel::ECC_Visibility, FCollisionShape::MakeSphere(Radius)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UCroshMC::IsGrounded()
{
	if (ZVel > 0)
		return false;

	float CapsuleHalfHeight = Cast<UCapsuleComponent>(UpdatedComponent)->GetUnscaledCapsuleHalfHeight();
	float Radius = Cast<UCapsuleComponent>(UpdatedComponent)->GetScaledCapsuleRadius();
	FVector Position = UpdatedComponent->GetOwner()->GetActorLocation() - FVector(0, 0, CapsuleHalfHeight - Radius /*+ 3.0f*/);

	// Grounded sphere
	// DrawDebugSphere(GetWorld(), Position, Radius, 8, FColor::Green);

	return CheckGroundedAtPosition(Position);
}
