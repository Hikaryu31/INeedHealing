// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_Attack.h"
#include "AICharacter.h"
#include "MyAIController.h"
#include "AttackAnimInstance.h"

UMyBTTask_Attack::UMyBTTask_Attack(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UMyBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* cont = OwnerComp.GetAIOwner();

	if (AAICharacter* ai = Cast<AAICharacter>(cont->GetPawn()))
	{
		if (ai->target == ai->dest)
			return EBTNodeResult::Type::Failed;

		USkeletalMeshComponent* mesh = ai->GetMesh();
		if (mesh == nullptr)
			return EBTNodeResult::Type::Failed;

		UAttackAnimInstance* animInstance = Cast<UAttackAnimInstance>(mesh->GetAnimInstance());

		if (animInstance == nullptr)
			return EBTNodeResult::Type::Failed;

		animInstance->StartAttack = true;
	}

	return EBTNodeResult::Type::Succeeded;
}