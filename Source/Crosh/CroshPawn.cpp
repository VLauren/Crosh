// Fill out your copyright notice in the Description page of Project Settings.

#include "CroshPawn.h"

// Sets default values
ACroshPawn::ACroshPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// Add the character's capsule
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleComponent->InitCapsuleSize(34.0f, 88.0f);
	CapsuleComponent->SetCollisionProfileName("MainChar");
	CapsuleComponent->CanCharacterStepUpOn = ECB_No;
	// CapsuleComponent->bCheckAsyncSceneOnMove = false;
	CapsuleComponent->SetCanEverAffectNavigation(false);
	CapsuleComponent->bDynamicObstacle = true;
	RootComponent = CapsuleComponent;

	CapsuleComponent->SetVisibility(true);
	CapsuleComponent->SetHiddenInGame(false);

	// Mesh
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	if (Mesh != nullptr)
	{
		Mesh->AlwaysLoadOnClient = true;
		Mesh->AlwaysLoadOnServer = true;
		Mesh->bOwnerNoSee = false;
		Mesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPose;
		Mesh->bCastDynamicShadow = true;
		Mesh->bAffectDynamicIndirectLighting = true;
		Mesh->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		Mesh->SetupAttachment(CapsuleComponent);
		static FName MeshCollisionProfileName(TEXT("CharacterMesh"));
		Mesh->SetCollisionProfileName(MeshCollisionProfileName);
		Mesh->SetGenerateOverlapEvents(false);
		Mesh->SetCanEverAffectNavigation(false);
	}

	// Movement component
	Movement = CreateDefaultSubobject<UCroshMC>(TEXT("Movement"));
	Movement->UpdatedComponent = RootComponent;

	// Default values
	MovementSpeed = 500.0f;
	// RotationLerpSpeed = 0.1f;
	// JumpStrength = 24;
	// GravityStrength = 60.0f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ACroshPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACroshPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACroshPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Input de movimiento
	PlayerInputComponent->BindAxis("MoveRight", this, &ACroshPawn::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACroshPawn::MoveForward);

	// Input de acciones
	// PlayerInputComponent->BindAction("Cosa", IE_Pressed, this, &ACroshPawn::Cosa);
}

void ACroshPawn::MoveForward(float AxisValue)
{
	Movement->AddInputVector(AxisValue * FVector::ForwardVector);
}

void ACroshPawn::MoveRight(float AxisValue)
{
	UE_LOG(LogTemp, Warning, TEXT("MoveRight %f"), AxisValue);
	Movement->AddInputVector(AxisValue * FVector::RightVector);
}

