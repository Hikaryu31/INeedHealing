// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseCharacter.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthEvent);

UCLASS()
class INEEDHEALING_API AAICharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		int life;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		int maxLife = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		int damage = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = true))
		AActor* target = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = true))
		AActor* dest;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float maxBuffTime = 10;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float buffTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		bool buffed = false;

	UPROPERTY(BlueprintAssignable, Category = "Event")
		FHealthEvent OnHealthUpdate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class AINeedHealingGameMode* gameMode;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Gameplay)
		void LifeDown(int dmg);

	void Heal(int healRecieved);
	void Buff();

	UFUNCTION(BlueprintCallable, Category = Misc)
		float GetLifePercent() { return (float)life / (float)maxLife; }
};
