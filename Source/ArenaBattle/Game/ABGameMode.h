// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interface/ABGameInterface.h"

#include "ABGameMode.generated.h"

/**
 *
 */
UCLASS()
class ARENABATTLE_API AABGameMode : public AGameModeBase, public IABGameInterface
{
	GENERATED_BODY()

public:
	AABGameMode();

public:
	virtual void OnPlayerScoreChanged(int32 NewPlayerScore) override;
	virtual void OnPlayerDead() override;
	virtual bool IsGameCleared() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Game)
	int32 ClearScore;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = Game)
	int32 CurrentScore;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = Game)
	uint8 bIsCleared : 1;
};
