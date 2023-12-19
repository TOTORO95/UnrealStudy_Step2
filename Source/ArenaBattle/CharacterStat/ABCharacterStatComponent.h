// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "GameData/ABCharacterStat.h"

#include "ABCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate, float /*CurrentHp*/);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARENABATTLE_API UABCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UABCharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	FOnHpZeroDelegate OnHpZero;
	FOnHpChangedDelegate OnHpChanged;

	void SetLevelStat(int32 InNewLevel);

	FORCEINLINE float GetCurrentLevel() const
	{
		return CurrentLevel;
	}
	FORCEINLINE void SetModifierStat(const FABCharacterStat& InMidifierStat)
	{
		ModifierStat = InMidifierStat;
	}
	FORCEINLINE FABCharacterStat GetTotalStat() const
	{
		return BaseStat + ModifierStat;
	}
	FORCEINLINE float GetCurrentHp()
	{
		return CurrentHp;
	}
	float ApplyDamage(float InDamage);

protected:
	void SetHp(float NewHp);

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHp;

	UPROPERTY(VisibleInstanceOnly, Category = Stat)
	float CurrentLevel;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess= "true"))
	FABCharacterStat BaseStat;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess= "true"))
	FABCharacterStat ModifierStat;
};
