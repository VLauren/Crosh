// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "CroshMC.generated.h"

/**
 * 
 */
UCLASS()
class CROSH_API UCroshMC : public UPawnMovementComponent
{
	GENERATED_BODY()
	
private:
	int jumpFrames;
	FRotator CurrentRotation;
	FVector TickMove;
	bool moving;

protected:

	float ZVel;

public:


private:

	bool CheckGroundedAtPosition(FVector Position);

public:

	void Jump();

	UFUNCTION(BlueprintPure)
		bool IsGrounded();
	UFUNCTION(BlueprintPure)
		bool IsMoving();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
