// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include <iostream>
#include <fstream>
#include "VRCharacter.h"	
#include "Kismet/GameplayStatics.h"
#include "LevelEnd.generated.h"

UCLASS()
class MSCPROJECT_API ALevelEnd : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float completionTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float healthLost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float deathCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool timerActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool isEnded;

	ALevelEnd();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void TimerStart();
	
	UFUNCTION(BlueprintCallable)
	void LevelComplete();

	UFUNCTION()
	void OnMeshBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
