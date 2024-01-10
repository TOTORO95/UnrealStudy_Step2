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
	// ���� ������Ʈ���� ���ݵ����Ͱ� ������Ʈ�Ǹ� HUD������ �ڵ����� �ݿ��ǰ� �߰�
	HpBar = Cast<UABHpBarWidget>(GetWidgetFromName(TEXT("WidgetHpBar")));
	ensure(HpBar);

	CharacterStat = Cast<UABCharacterStatWidget>(GetWidgetFromName(TEXT("WidgetCharacterStat")));
	ensure(CharacterStat);

	// ���� ���÷����� ��� GetOwningPlayer �� GetOwningPlayerPawn�� �����  ������ ���̳� �÷��̾��� ��Ʈ�귯�� �����ü����ִ�.
	IABCharacterHUDInterface* HUDPawn = Cast<IABCharacterHUDInterface>(GetOwningPlayerPawn());
	if (HUDPawn)
	{
		HUDPawn->SetupHUDWidget(this);
	}
}
