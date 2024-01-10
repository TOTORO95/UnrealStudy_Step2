// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/ABHUDWidget.h"

#include "Interface/ABCharacterHUDInterface.h"
#include "UI/ABCharacterStatWidget.h"
#include "UI/ABHpBarWidget.h"

UABHUDWidget::UABHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UABHUDWidget::UpdateStat(const FABCharacterStat& BaseStat, const FABCharacterStat& ModifierStat)
{
	FABCharacterStat TotalStat = BaseStat + ModifierStat;
	HpBar->UpdateStat(BaseStat, ModifierStat);
	CharacterStat->UpdateStat(BaseStat, ModifierStat);
}

void UABHUDWidget::UpdateHpBar(float NewCurrentHp)
{
	HpBar->UpdateHpBar(NewCurrentHp);
}

void UABHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// 스탯 컴포넌트안의 스텟데이터가 업데이트되면 HUD위젯에 자동으로 반영되게 추가
	HpBar = Cast<UABHpBarWidget>(GetWidgetFromName(TEXT("WidgetHpBar")));
	ensure(HpBar);

	CharacterStat = Cast<UABCharacterStatWidget>(GetWidgetFromName(TEXT("WidgetCharacterStat")));
	ensure(CharacterStat);

	// 헤드업 디스플레이의 경우 GetOwningPlayer 나 GetOwningPlayerPawn를 사용해  빙의한 폰이나 플레이어의 컨트룰러를 가져올수도있다.
	IABCharacterHUDInterface* HUDPawn = Cast<IABCharacterHUDInterface>(GetOwningPlayerPawn());
	if (HUDPawn)
	{
		HUDPawn->SetupHUDWidget(this);
	}
}
