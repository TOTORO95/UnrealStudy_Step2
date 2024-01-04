// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameData/ABCharacterStat.h"

#include "ABCharacterStatWidget.generated.h"

/**
 *
 */
UCLASS() class ARENABATTLE_API UABCharacterStatWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateStat(const FABCharacterStat& BaseStat, const FABCharacterStat& ModifierStat);

private:
	UPROPERTY()
	TMap<FName, class UTextBlock*> BaseLookUp;

	UPROPERTY()
	TMap<FName, class UTextBlock*> ModifierLookUp;
};
