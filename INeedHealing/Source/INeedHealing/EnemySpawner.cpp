// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemySpawner::Spawn(int bonusHealth)
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
		mob->dest = target;
		mob->life += bonusHealth;
	}
	spawnsHere--;
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

