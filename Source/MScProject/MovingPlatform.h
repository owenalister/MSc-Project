// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "MovingPlatform.generated.h"

UCLASS()
class MSCPROJECT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent *mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool horizontal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float frequency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float amplitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RunningTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent *end;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent *start;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* root;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
