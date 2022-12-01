// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AICharacter.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AllySpawner.generated.h"

UCLASS()
class INEEDHEALING_API AAllySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAllySpawner();

	UPROPERTY(EditAnywhere, Category = "Entity")
		TSubclassOf<AAICharacter> mobType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
		TArray<AActor*> targets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
		float spawnRate = 1.f;

protected:
	class AINeedHealingGameMode* gameMode;
	FTimerHandle spawnTimerHandle{};
	int currentTarget = 0;
	int numTargets = 0;
	int currentWave = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave stats", meta=(ClampMin = "0.0", UIMin= "0.0"))
		int FlatAmountToSpawn = 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Spawn();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
