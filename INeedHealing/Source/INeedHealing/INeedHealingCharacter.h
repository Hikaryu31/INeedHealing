// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "BaseCharacter.h"
#include "AICharacter.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "INeedHealingCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealCast);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBuffCast);

UCLASS(config = Game)
class AINeedHealingCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
public:
	AINeedHealingCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		int healingAmount = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float maxHealCooldown = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float healCooldown = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float maxBuffCooldown = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float buffCooldown = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float turnSpeed = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<AAICharacter*> alliesList;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FRotator meshRotation;

	UPROPERTY(BlueprintAssignable, Category = "Event")
		FHealCast OnHealCast;

	UPROPERTY(BlueprintAssignable, Category = "Event")
		FBuffCast OnBuffUpdate;
protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable, Category="Spells")
		void CastHeal();

	UFUNCTION(BlueprintCallable, Category = "Spells")
		void CastBuff();
};

