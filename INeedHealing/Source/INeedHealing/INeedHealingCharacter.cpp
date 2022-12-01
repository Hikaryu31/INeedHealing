// Copyright Epic Games, Inc. All Rights Reserved.

#include "INeedHealingCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// AINeedHealingCharacter

AINeedHealingCharacter::AINeedHealingCharacter()
{
	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate

	//Jump
	//GetCharacterMovement()->JumpZVelocity = 600.f;
	//GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AINeedHealingCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	//Jump
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AINeedHealingCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AINeedHealingCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AINeedHealingCharacter::TurnAtRate);
	//PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	//PlayerInputComponent->BindAxis("LookUpRate", this, &AINeedHealingCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AINeedHealingCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AINeedHealingCharacter::TouchStopped);
}

void AINeedHealingCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		//Jump();
}

void AINeedHealingCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		//StopJumping();
}

void AINeedHealingCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AINeedHealingCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AINeedHealingCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AINeedHealingCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AINeedHealingCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	healCooldown -= DeltaTime;
	buffCooldown -= DeltaTime;

}

void AINeedHealingCharacter::CastHeal()
{
	if (healCooldown <= 0.f && alliesList.Num() > 0)
	{
		healCooldown = maxHealCooldown;
		OnHealCast.Broadcast();
		for (AAICharacter* ally : alliesList)
		{
			ally->Heal(healingAmount);
		}
	}
}

void AINeedHealingCharacter::CastBuff()
{
	if (buffCooldown <= 0.f && alliesList.Num() > 0 && healCooldown <= 0.f)
	{
		buffCooldown = maxBuffCooldown;
		OnBuffUpdate.Broadcast();
		for (AAICharacter* ally : alliesList)
		{
			ally->Buff();
		}
	}
}

