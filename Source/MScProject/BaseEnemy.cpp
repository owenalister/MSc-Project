// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseEnemy.h"


// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	damage = 15;
	startingHealth = 100;
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	//get player ref
	SetPlayerRef();
	tryAttack = false;
	currentHealth = startingHealth;
	isDead = false;
	startPos = this->GetActorLocation();
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float distToPlayer = GetDistanceTo(playerRef);
	if (KnockBack < 0)
	{
		// turn towards player
		FRotator targetRot;
		targetRot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), playerRef->GetActorLocation());
		this->SetActorRotation(targetRot);
		//walk away from player
		AddMovementInput(this->GetActorForwardVector()*-1.0f, 0.75f);
		KnockBack -= 0.75f;
		Jump();
	}
	else{
	// check if player close
	if (distToPlayer < 1000) {
		if (distToPlayer > 130)
		{
			// turn towards player
			FRotator targetRot;
			targetRot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), playerRef->GetActorLocation());
			this->SetActorRotation(targetRot);
			// walk towards player
			AddMovementInput(this->GetActorForwardVector(), 0.5f);
			inAttackRange = false;
		}
		else
		{
			inAttackRange = true;
		}
		
	}
	else //walk back to start loc
	{
		if ((this->GetActorLocation()-startPos).Size() > 150)
		{
			// turn towards player
			FRotator targetRot;
			targetRot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), startPos);
			this->SetActorRotation(targetRot);
			// walk towards player
			AddMovementInput(this->GetActorForwardVector(), 0.5f);
			inAttackRange = false;
		}
	}
	}

	//check if in range of player
	if (inAttackRange && !isStunned)
	{
		tryAttack = true;
	}
	else 
	{
		tryAttack = false;
	}
	// check if dead
	if (currentHealth <= 0)
	{
		isDead = true;
		KillEnemy();
	}
}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseEnemy::TakeDamage(float dmg)
{
	currentHealth -= damage;
	KnockBack = 1000;
	if (currentHealth < 0)
		currentHealth = 0;
	AddMovementInput(this->GetActorForwardVector()*-1.0f, 0.75f);
	// turn towards player
	FRotator targetRot;
	targetRot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), playerRef->GetActorLocation());
	this->SetActorRotation(targetRot);
	//walk away from player
	AddMovementInput(this->GetActorForwardVector()*-1.0f, KnockBack);
	KnockBack -= 0.75f;
	Jump();
}

void ABaseEnemy::KillEnemy()
{
	if(!isDead)
	GetMesh()->PlayAnimation(Anim, false);
}

void ABaseEnemy::SetPlayerRef()
{
	playerRef = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}