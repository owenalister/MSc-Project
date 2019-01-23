// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/Classes/Components/SKeletalMeshComponent.h"
#include "Engine/Classes/Kismet/KismetMathLibrary.h"
#include "BaseEnemy.generated.h"


UCLASS()
class MSCPROJECT_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemy();

	//reference to player
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ACharacter* playerRef;

	UPROPERTY(VisibleAnywhere)
	float KnockBack;
	
	UPROPERTY(VisibleAnywhere)
	bool inAttackRange;

	UPROPERTY(VisibleAnywhere)
	bool canAttack;

	UPROPERTY(VisibleAnywhere)
	bool isStunned;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool tryAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float startingHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float currentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isDead;

	UPROPERTY(EditAnywhere)
	UAnimSequence *Anim;

	FVector startPos;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float dmg);

	UFUNCTION(BlueprintCallable)
	void KillEnemy();
	UFUNCTION(BlueprintCallable)
	void SetPlayerRef();
};
	
