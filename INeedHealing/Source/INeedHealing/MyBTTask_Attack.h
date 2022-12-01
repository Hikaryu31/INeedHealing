// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class INEEDHEALING_API UMyBTTask_Attack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UMyBTTask_Attack(const FObjectInitializer& Object_Initializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
