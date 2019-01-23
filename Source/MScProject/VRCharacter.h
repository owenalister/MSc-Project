// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HeadMountedDisplay.h"
#include "MotionControllerComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/Classes/Components/SKeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"

#include "VRCharacter.generated.h"


UCLASS()
class MSCPROJECT_API AVRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVRCharacter();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

	// origin for hmd and motion controls
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* VROriginComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* CameraOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool firstPerson;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* CameraTarget;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* HandMesh_L;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* HandMesh_R;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Sword;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMotionControllerComponent* MotionController_R;

	UPROPERTY(EditAnywhere)
	UMotionControllerComponent* MotionController_L;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector movementInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float currentHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float startingHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float damage;

	UPROPERTY(EditAnywhere)
	UAnimMontage *Anim;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool isDead;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FVector CurrentVelocity;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move_Forwards(float AxisValue);
	void Strafe(float AxisValue);
	void JumpStart();
	void JumpStop();
	void SetCameraOrigin(FVector pos);
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float dmg);

	void SetFirsperson();

	UFUNCTION(BlueprintCallable)
	void KillPlayer();

	UFUNCTION(BlueprintCallable)
	void RespawnPlayer();
};
