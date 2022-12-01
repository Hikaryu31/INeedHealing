// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "UObject/ConstructorHelpers.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

AMyAIController::AMyAIController(const FObjectInitializer& Object_Initializer) : AAIController(Object_Initializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("/Game/AI/AIBehaviorTree.AIBehaviorTree"));

	if (obj.Succeeded())
	{
		behaviorTree = obj.Object;
	}
	behaviorTreeComponent = Object_Initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("behaviorTreeComponent"));
	blackboardComponent = Object_Initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("blackboardComponent"));

	SetActorTickEnabled(true);
	bAllowStrafe = true;
}

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(behaviorTree);
	behaviorTreeComponent->StartTree(*behaviorTree);
	if (me != nullptr)
	{
		blackboardComponent->SetValueAsObject("Dest", me->dest);
		blackboardComponent->SetValueAsObject("Target", me->target);
		currentTarget = me->target;
	}
	else
	{
		blackboardComponent->SetValueAsObject("Dest", nullptr);
		blackboardComponent->SetValueAsObject("Target", nullptr);
		currentTarget = nullptr;
	}
}

void AMyAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (me == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-0, 1.f, FColor::Red, FString(TEXT("nullptr")));
		return;
	}

	if (me->target == nullptr)
	{
		me->target = me->dest;
		blackboardComponent->SetValueAsObject("Target", me->target);
		currentTarget = me->target;
	}

	else if (me->target != currentTarget)
	{
		blackboardComponent->SetValueAsObject("Target", me->target);
		currentTarget = me->target;
	}
	
}

void AMyAIController::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);
	me = Cast<AAICharacter>(GetPawn());
}

void AMyAIController::OnUnPossess()
{
	Super::OnUnPossess();
}