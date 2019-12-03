// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformGameInstance.h"
#include <Engine/Engine.h>
#include <Engine/World.h>
#include <GameFramework/PlayerController.h>
#include <ConstructorHelpers.h>
#include "PlatformTrigger.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/MenuWidget.h"

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> PlatformTriggerBP(TEXT("/Game/MenuSystem/WBP_MainMenu"));

	if(!ensure(PlatformTriggerBP.Class != nullptr)) return;

	MenuClass = PlatformTriggerBP.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> OverlayBP(TEXT("/Game/MenuSystem/WBP_Overlay"));

	if (!ensure(OverlayBP.Class != nullptr)) return;

	GameOverlayClass = OverlayBP.Class;

	UE_LOG(LogTemp, Warning, TEXT("Class Found %s"), *MenuClass->GetName());

}

void UPuzzlePlatformGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("Init Call"));
	
}


void UPuzzlePlatformGameInstance::HostServer()
{
	UEngine* Engine = GetEngine();

	if(!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 5.f, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();

	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/ThirdPersonBP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformGameInstance::JoinServer(const FString& Address)
{
	UEngine* Engine = GetEngine();

	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 5.f, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();

	if(!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(*Address, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformGameInstance::LoadMenu()
{
	if(!ensure(MenuClass != nullptr)) return;

	UMenuWidget* Menu = CreateWidget<UMenuWidget>(this, MenuClass);

	if(!ensure(Menu != nullptr)) return;

	Menu->Setup();

	Menu->SetupMenuInterface(this);
}

void UPuzzlePlatformGameInstance::LoadInGameMenu()
{
	if (!ensure(MenuClass != nullptr)) return;

	UMenuWidget* Menu = CreateWidget<UMenuWidget>(this, GameOverlayClass);

	if (!ensure(Menu != nullptr)) return;

	Menu->Setup();

	Menu->SetupMenuInterface(this);
}
