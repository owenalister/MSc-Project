// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseEnemy.h"


// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	//get player ref
	playerRef = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	tryAttack = false;
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator targetRot;
	targetRot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), playerRef->GetActorLocation());
	this->SetActorRotation(targetRot);
	if (GetDistanceTo(playerRef) > 130) {
		AddMovementInput(this->GetActorForwardVector(), 0.7f);
		inAttackRange = false;
	}
	else 
	{
		inAttackRange = true;
	}
	if (inAttackRange && !isStunned)
	{
		tryAttack = true;
	}
	else 
	{
		tryAttack = false;
	}
}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

