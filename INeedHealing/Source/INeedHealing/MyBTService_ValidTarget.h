// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "MyBTService_ValidTarget.generated.h"

/**
 * 
 */
UCLASS()
class INEEDHEALING_API UMyBTService_ValidTarget : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UMyBTService_ValidTarget(const FObjectInitializer& Object_Initializer);

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
