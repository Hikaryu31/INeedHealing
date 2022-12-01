// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemySpawner.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveController.generated.h"

UCLASS()
class INEEDHEALING_API AWaveController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveController();

	UPROPERTY()
		class USoundWave* MySoundWave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawners")
		TArray<AEnemySpawner*> spawners;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawners")
		float spawnDelay = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawners")
		float delayBetweenWaves = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawners")
		float warningDuration = 1.f;

protected:
	int enemiesToSpawn = 0;

	class AINeedHealingGameMode* gameMode;
	FTimerHandle spawnTimerHandle{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave stats", meta = (ClampMin = "0.0", UIMin = "0.0"))
		int FlatAmountToSpawn = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave stats")
		int SpawnMultiplier = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Wave stats")
		bool rest = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void UseSpawner();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private :
	void InitNewWave();
	int bonusHealth = 0;
};
