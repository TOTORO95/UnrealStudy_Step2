// Fill out your copyright notice in the Description page of Project Settings.

#include "Item/ABItemBox.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Interface/ABCharacterItemInterface.h"
#include "Particles/ParticleSystemComponent.h"
#include "Physics/ABCollision.h"
#include "Engine/AssetManager.h"
#include "ABItemData.h"

// Sets default values
AABItemBox::AABItemBox()
{
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Effect"));

	RootComponent = Trigger;
	Mesh->SetupAttachment(Trigger);
	Effect->SetupAttachment(Trigger);

	Trigger->SetCollisionProfileName(CPROFILE_ABTRIGGER);
	Trigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshRef(
		TEXT("/Script/Engine.StaticMesh'/Game/ArenaBattle/Environment/Props/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1'"));
	if (BoxMeshRef.Object)
	{
		Mesh->SetStaticMesh(BoxMeshRef.Object);
	}
	Mesh->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));	   // 매쉬충돌은 제거

	static ConstructorHelpers::FObjectFinder<UParticleSystem> EffectRef(
		TEXT("/Script/Engine.ParticleSystem'/Game/ArenaBattle/Effect/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh'"));
	if (EffectRef.Object)
	{
		Effect->SetTemplate(EffectRef.Object);
		Effect->bAutoActivate = false;
	}
}

void AABItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UAssetManager& Manager = UAssetManager::Get();
	TArray<FPrimaryAssetId> Assets;
	
	Manager.GetPrimaryAssetIdList(TEXT("ABItemData"), Assets);
	ensure(Assets.Num() < 0);

	int32 RandomIdx = FMath::RandRange(0, Assets.Num() -1 );
	FSoftObjectPtr AssetPtr(Manager.GetPrimaryAssetPath(Assets[RandomIdx]));
	if (AssetPtr.IsPending())
	{
		AssetPtr.LoadSynchronous();
	}

	Item = Cast<UABItemData>(AssetPtr.Get());
	ensure(Item);

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AABItemBox::OnOverlapBegin);
}

void AABItemBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	if (Item == nullptr)
	{
		Destroy();
		return;
	}

	IABCharacterItemInterface* OverlappingPawn = Cast<IABCharacterItemInterface>(OtherActor);
	if (OverlappingPawn)
	{
		OverlappingPawn->TakeItem(Item);
	}

	Effect->Activate(true);
	Mesh->SetHiddenInGame(true);
	SetActorEnableCollision(false);
	Effect->OnSystemFinished.AddDynamic(this, &AABItemBox::OnEffectFinished);
}

void AABItemBox::OnEffectFinished(UParticleSystemComponent* ParticleSystem)
{
	Destroy();
}
