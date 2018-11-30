// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_FollowCamera.h"


// Sets default values
AVR_FollowCamera::AVR_FollowCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	speed = 0;
}

// Called when the game starts or when spawned
void AVR_FollowCamera::BeginPlay()
{
	Super::BeginPlay();
	//get player ref
	playerRef = Cast<AVRCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	position = playerRef->CameraTarget->GetComponentLocation();
}

// Called every frame
void AVR_FollowCamera::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime);
	//while not near player camera target go to player camera target
	SetPosition();
	SetCamera();
}

void AVR_FollowCamera::SetPosition() 
{
	FVector distance = playerRef->CameraTarget->GetComponentLocation() - position;
	if (distance.Size() < speed)
		position = playerRef->CameraTarget->GetComponentLocation();
	else 
	{	
		distance.Normalize();
		velocity = speed * distance;
		position += velocity;
	}
	

}

void AVR_FollowCamera::SetCamera()
{
	playerRef->SetCameraOrigin(position);

}
