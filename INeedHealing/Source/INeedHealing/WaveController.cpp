// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveController.h"
#include "Kismet/GameplayStatics.h"
#include "INeedHealingGameMode.h"

// Sets default values
AWaveController::AWaveController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USoundWave> myAudioResource(TEXT("/Game/Sounds/war_horn.war_horn"));
	MySoundWave = myAudioResource.Object;
}

// Called when the game starts or when spawned
void AWaveController::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> spawnerList;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawner::StaticClass(), spawnerList);

	for (AActor* spawner : spawnerList)
	{
		spawners.Add(Cast<AEnemySpawner>(spawner));
	}

	GetWorldTimerManager().SetTimer(spawnTimerHandle, this, &AWaveController::UseSpawner, spawnDelay, true, 0.1f);
	gameMode = Cast<AINeedHealingGameMode>(GetWorld()->GetAuthGameMode());
}

void AWaveController::UseSpawner()
{
	if (spawners.Num() != 0 && enemiesToSpawn > 0)
	{
		int index = FMath::RandRange(0, spawners.Num() - 1);
		spawners[index]->spawnsHere++;

		FTimerHandle warningTimeHandle{};
		FTimerDelegate spawnDelegate = FTimerDelegate::CreateUObject(spawners[index], &AEnemySpawner::Spawn, bonusHealth);
		GetWorldTimerManager().SetTimer(warningTimeHandle, spawnDelegate, warningDuration, false);

		enemiesToSpawn--;
		gameMode->enemiesCount++;
	}
	else if (rest == true)
	{
		return;
	}

	else if (enemiesToSpawn == 0 && gameMode->enemiesCount == 0)
	{
		gameMode->waveNumber++;
		if (gameMode->waveNumber % 5 == 0)
			bonusHealth += 5;

		FTimerHandle restTimeHandle{};
		rest = true;
		GetWorldTimerManager().SetTimer(restTimeHandle, this, &AWaveController::InitNewWave, delayBetweenWaves, false);
	}
}

void AWaveController::InitNewWave()
{
	enemiesToSpawn = FlatAmountToSpawn + gameMode->waveNumber * SpawnMultiplier;
	rest = false;
	GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Emerald, "Wave " + FString::FromInt(gameMode->waveNumber));
	UGameplayStatics::PlaySound2D(this, MySoundWave);
}

// Called every frame
void AWaveController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

