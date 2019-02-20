// Fill out your copyright notice in the Description page of Project Settings.

#include "VRCharacter.h"


// Sets default values
AVRCharacter::AVRCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// setup vr origin component
	VROriginComp = CreateDefaultSubobject<USceneComponent>(TEXT("VRCameraOrigin"));


	//setup cameraoffset
	CameraOffset = CreateDefaultSubobject<USceneComponent>(TEXT("CameraOffset"));

	//setup camera target position
	CameraTarget = CreateDefaultSubobject<USceneComponent>(TEXT("CameraTarget"));
	CameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("CameraRoot"));
	FootLocation = CreateDefaultSubobject<USceneComponent>(TEXT("FootLocation"));

	// Setup camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// create a visible representation of hands
	HandMesh_L = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HandLeft"));
	HandMesh_R = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HandRight"));
	Sword = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sword"));

	// create motion controllers and assign hands
	MotionController_L = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerL"));
	MotionController_R = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerR"));
	MotionController_L->Hand_DEPRECATED = EControllerHand::Left;
	MotionController_R->Hand_DEPRECATED = EControllerHand::Right;


	// attatchment heiararchy 
	VROriginComp->AttachTo(RootComponent);
	FootLocation->AttachTo(RootComponent);
	CameraOffset->AttachTo(VROriginComp);
	CameraRoot->AttachTo(RootComponent);
	CameraTarget->AttachTo(CameraRoot);
	Sword->AttachTo(MotionController_R);
	Camera->SetupAttachment(CameraOffset);
	MotionController_L->AttachTo(VROriginComp);
	MotionController_R->AttachTo(VROriginComp);
	HandMesh_L->AttachTo(MotionController_L);
	HandMesh_R->AttachTo(MotionController_R);
	//Sword->AttachTo(MotionController_R);
	
	// initialize variables
	startingHealth = 100;
	damage = 40;
	isDead = false;
	firstPerson = true;
	CheckPointLocation = FVector(0, 0, 0);
	deathCount = 0;
	fallCount = 0;
	totalHealthLost = 0;
	movementInput = FVector(0, 0, 0);
}

// Called when the game starts or when spawned
void AVRCharacter::BeginPlay()
{
	GetMesh()->HideBoneByName("sword_bottom", EPhysBodyOp::PBO_None);
	Super::BeginPlay();
	
	// hide head if game starts in first person
	if (firstPerson)
		GetMesh()->HideBoneByName("head", EPhysBodyOp::PBO_None);
	
	currentHealth = startingHealth;
}

// Called every frame
void AVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ManageHealth();
	SetPlayerLoc();
	// get motion controller rotation
	FRotator PlayerRotation =  FRotator(0, Camera->GetComponentRotation().Yaw-90.0f, 0);
	GetMesh()->SetWorldRotation(PlayerRotation);
	FVector dir = MotionController_L->GetForwardVector();
	
	// kill player if health reaches 0
	if(currentHealth<=0 )
	{
		KillPlayer();
	}

	// rotate third person camera
	float camYaw = Camera->GetComponentRotation().Yaw;
	float tppYaw = CameraRoot->GetComponentRotation().Yaw;
	float angle = tppYaw - camYaw;
	if (abs(angle) > 10)
	{ 
		if (angle < 0)
		{
			angle += 360;
		}
		if (angle > 180)
		{
			CameraRoot->AddRelativeRotation(FRotator(0, 2, 0));
		}
			
		if (angle<= 180)
		{
			CameraRoot->AddRelativeRotation(FRotator(0, -2, 0));
		}
			
	}
	
}

// Called to bind functionality to input
void AVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Forwards", this, &AVRCharacter::Move_Forwards);	
	PlayerInputComponent->BindAxis("Strafe", this, &AVRCharacter::Strafe);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AVRCharacter::JumpStart);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AVRCharacter::JumpStop);
	PlayerInputComponent->BindAction("Camera", IE_Pressed, this, &AVRCharacter::SetFirsperson);
}

void AVRCharacter::Move_Forwards(float AxisValue) 
{

	float ForwardsSpeed = 100;
	FVector camDir(Camera->GetForwardVector());
	camDir.Z = 0;
	camDir.Normalize();
	FRotator rot(0.0f, GetControlRotation().Yaw, 0.0f);
	FVector fwd = FRotationMatrix(rot).GetScaledAxis(EAxis::X);
	// add movement in the direction the character is facing
	AddMovementInput(camDir, AxisValue * ForwardsSpeed);
	camDir=MotionController_L->GetRightVector();
	camDir.Z = 0;
	camDir.Normalize();
	fwd = FRotationMatrix(rot).GetScaledAxis(EAxis::Y);
	//add movement adjacent to the direction that the player is facing
	AddMovementInput(camDir, InputComponent->GetAxisValue(TEXT("Strafe")) * ForwardsSpeed);
	movementInput.X = AxisValue * ForwardsSpeed;
	movementInput.Y = InputComponent->GetAxisValue(TEXT("Strafe")) * ForwardsSpeed;
}

// this function is empty as the strafe functionality is implimented in the move forwards command. However deleting it will cause the strafe input axis to become unreadable.
void AVRCharacter::Strafe(float AxisValue)
{

}

void AVRCharacter::JumpStart()
{
	bPressedJump = true;
}

void AVRCharacter::JumpStop()
{
	bPressedJump = false;
}

// sets location of the camera in third person
void AVRCharacter::SetCameraOrigin(FVector pos) 
{
	if(!firstPerson)
		CameraOffset->SetWorldLocation(pos, false, 0, ETeleportType::None);
	
}

// reduce players health
void AVRCharacter::DamagePlayer(float damage)
{
	currentHealth -= damage;
	totalHealthLost += damage;
	if (currentHealth < 0)
		currentHealth = 0;
}


//kill the player
void AVRCharacter::KillPlayer()
{
		deathCount += 1;
		this->SetActorLocation(CheckPointLocation);
		currentHealth = startingHealth;
}

// check if the health is lower than 0
void AVRCharacter::ManageHealth()
{
	if (currentHealth <= 0)
	{
		if (!isDead)
		{
			isDead = true;
		}
	}
}

// respawn player at last check point and reset health
void AVRCharacter::RespawnPlayer()
{
	currentHealth = startingHealth;
	fallCount += 1;
	this->SetActorLocation(CheckPointLocation);
}

//set the location of the camera based on camera perspective
void AVRCharacter::SetCamera()
{
	if (firstPerson)
	{
		CameraOffset->SetRelativeLocation(FVector(0, 0, 0));
	}
	else
	{
		CameraOffset->SetWorldLocation(CameraTarget->GetComponentLocation());
	}
}

// toggle between first and third person
void AVRCharacter::SetFirsperson()
{
	if (firstPerson)
	{
		firstPerson = false;
		GetMesh()->UnHideBoneByName("head");
	}
	else
	{
		firstPerson = true;
		GetMesh()->HideBoneByName("head", EPhysBodyOp::PBO_None);
		CameraOffset->SetRelativeLocation(FVector(0, 0, 0));
	}
}


// set player mesh location to line up with position of the player in the real world
void AVRCharacter::SetPlayerLoc()
{

	FVector newLocation = Camera->RelativeLocation;
	newLocation.Z = FootLocation->RelativeLocation.Z;
	GetMesh()->SetRelativeLocation(newLocation);
	//CameraRoot->SetRelativeRotation(GetMesh()->RelativeRotation);

}

// attempts to scale the player model to the height of the player
void AVRCharacter::ScalePlayerModel()
{
	PlayerHeight = Camera->RelativeLocation.Z;
	float scale = PlayerHeight / 200.0f;
	GetMesh()->RelativeScale3D = FVector(scale, scale, scale);
}

