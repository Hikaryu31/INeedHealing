// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AICharacter.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class INEEDHEALING_API AMyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMyAIController(const FObjectInitializer& Object_Initializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void OnPossess(APawn* const pawn) override;
	virtual void OnUnPossess() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = true))
		class UBehaviorTreeComponent* behaviorTreeComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = true))
		class UBehaviorTree* behaviorTree;

	class UBlackboardComponent* blackboardComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
		AAICharacter* me;

	AActor* currentTarget;
};
