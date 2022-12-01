// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTService_ValidTarget.h"
#include "AICharacter.h"
#include "MyAIController.h"

UMyBTService_ValidTarget::UMyBTService_ValidTarget(const FObjectInitializer& Object_Initializer)
{
	NodeName = TEXT("Select Valid Target");
}

void UMyBTService_ValidTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* cont = OwnerComp.GetAIOwner();

	if (AAICharacter* ai = Cast<AAICharacter>(cont->GetPawn()))
	{
		if (!IsValid(ai->target))
			ai->target = ai->dest;
	}
}