// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AICharacter.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class INEEDHEALING_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	UPROPERTY(EditAnywhere, Category = "Entity")
		TSubclassOf<AAICharacter> mobType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
		AActor* target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
		int spawnsHere = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Spawn(int bonusHealth);

};
