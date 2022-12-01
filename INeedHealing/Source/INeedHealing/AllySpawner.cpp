// Fill out your copyright notice in the Description page of Project Settings.


#include "AllySpawner.h"
#include "INeedHealingGameMode.h"

// Sets default values
AAllySpawner::AAllySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAllySpawner::BeginPlay()
{
	Super::BeginPlay();
	gameMode = Cast<AINeedHealingGameMode>(GetWorld()->GetAuthGameMode());
	numTargets = targets.Num();

	for (int i = 0; i <= FlatAmountToSpawn; i++)
	{
		Spawn();
	}

	GetWorldTimerManager().SetTimer(spawnTimerHandle, this, &AAllySpawner::Spawn, spawnRate, true, 0.1f);
}

void AAllySpawner::Spawn()
{
	FRotator rot = { 0.f, 0.f, 0.f };
	FActorSpawnParameters spawnParameters;
	if (mobType.GetDefaultObject() == nullptr || mobType.GetDefaultObject()->GetClass() == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Cyan, FString(TEXT("mobtype = nullptr")));
		return;
	}

	AAICharacter* mob = GetWorld()->SpawnActor<AAICharacter>(mobType.GetDefaultObject()->GetClass(), GetActorLocation(), rot, spawnParameters);

	if (mob != nullptr)
	{
		currentTarget++;

		if (numTargets == 0)
			return;

		else if (currentTarget > numTargets - 1)
			currentTarget = 0;
		
		mob->dest = targets[currentTarget];
		gameMode->alliesCount++;
	}
}

// Called every frame
void AAllySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

