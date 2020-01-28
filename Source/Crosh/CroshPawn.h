// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "CroshMC.h"
#include "CroshPawn.generated.h"

UCLASS()
class CROSH_API ACroshPawn : public APawn
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Movement")
		float MovementSpeed;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float JumpStrength;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float GravityStrength;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowProvateAccess = "true"))
		UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowProvateAccess = "true"))
		USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UCroshMC* Movement;

private:

public:
	// Sets default values for this pawn's properties
	ACroshPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Jump();

};
