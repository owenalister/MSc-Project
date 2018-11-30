// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VRCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "VR_FollowCamera.generated.h"

UCLASS()
class MSCPROJECT_API AVR_FollowCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVR_FollowCamera();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AVRCharacter* playerRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float speed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SetCamera();
	void SetPosition();
	FVector position;
	FVector velocity;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
