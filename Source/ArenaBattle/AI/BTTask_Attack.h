// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "CoreMinimal.h"

#include "BTTask_Attack.generated.h"

/**
 *
 */
UCLASS()
class ARENABATTLE_API UBTTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_Attack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
