// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/ABGameMode.h"

#include "Player/ABPlayerController.h"

AABGameMode::AABGameMode()
{
	// �������̱� ������ ConstructorHelpers �ʿ�
	// static ConstructorHelpers::FClassFinder<APawn> ThirdPersonClassRef(*CharacterResourcePath);
	// if (ThirdPersonClassRef.Class)
	//{
	//	DefaultPawnClass = ThirdPersonClassRef.Class;
	//}
	// else
	//{
	//	UE_LOG(LogTemp, Log, TEXT("Not Found ThirdEPrson Object!! Path = %s"), *CharacterResourcePath);
	//}

	// /Script/Engine.Blueprint'/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter' ���� �Ʒ��� ����
	// /Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter_C <- _C�� Ŭ���� ������ �������� ���� �߰�
	FString CharacterResourcePath = TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter_C");

	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Script/ArenaBattle.ABCharacterPlayer"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	PlayerControllerClass = AABPlayerController::StaticClass();

	/// Script/CoreUObject.Class'/Script/ArenaBattle.ABPlayerController'
	// static ConstructorHelpers::FClassFinder<APlayerController>
	// PlayerControllerClassRef(TEXT("/Script/ArenaBattle.ABPlayerController_C")); if (PlayerControllerClassRef.Class)
	//{
	//	PlayerControllerClass = PlayerControllerClassRef.Class;
	// }
}
