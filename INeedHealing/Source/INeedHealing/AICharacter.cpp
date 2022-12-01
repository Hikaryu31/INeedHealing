// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "MyGameStateBase.h"
#include "INeedHealingGameMode.h"
#include "Components/BoxComponent.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	life = maxLife;
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	gameMode = Cast<AINeedHealingGameMode>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (buffTime > 0)
		buffTime -= DeltaTime;

	else
	{
		buffed = false;

		GetMesh()->SetScalarParameterValueOnMaterials("Buffed", 0.f);
	}
}

void AAICharacter::LifeDown(int dmg)
{
	if (buffed)
		return;

	life -= dmg;

	if (life <= 0)
	{
		if (ActorHasTag("Enemy"))
			gameMode->enemiesCount--;
		else if (ActorHasTag("Ally"))
			gameMode->alliesCount--;

		Destroy();
	}
}

void AAICharacter::Heal(int healRecieved)
{
		life += healRecieved;
		OnHealthUpdate.Broadcast();
		if (life > maxLife)
		{
			life = maxLife;
		}
}

void AAICharacter::Buff()
{
	GetMesh()->SetScalarParameterValueOnMaterials("Buffed", 1.f);
	buffed = true;
	buffTime = maxBuffTime;
}