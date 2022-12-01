// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AttackAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class INEEDHEALING_API UAttackAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public :
	UAttackAnimInstance(const FObjectInitializer& Object_Initializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		bool IsWalking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		bool StartAttack = false;
};
