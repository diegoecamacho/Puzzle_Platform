// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformGameInstance.h"
#include <Engine/Engine.h>
#include <Engine/World.h>
#include <GameFramework/PlayerController.h>
#include <ConstructorHelpers.h>
#include "PlatformTrigger.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/MenuWidget.h"
#include <OnlineSubsystem.h>
#include <OnlineSessionSettings.h>
#include <OnlineSessionInterface.h>
#include <SharedPointer.h>

const static FName SESSION_NAME = TEXT("GameSession");


UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> PlatformTriggerBP(TEXT("/Game/MenuSystem/WBP_MainMenu"));

	if (!ensure(PlatformTriggerBP.Class != nullptr)) return;

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
	OnlineSubsystem = IOnlineSubsystem::Get();

	if (OnlineSubsystem != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Subsystem %s"), *OnlineSubsystem->GetSubsystemName().ToString());
		SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Found Session."));
			AssignSessionEvents();

		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Subsystem found."));
	}
}

void UPuzzlePlatformGameInstance::AssignSessionEvents()
{
	SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnCreateSessionComplete);
	SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnDestroySessionComplete);
}

void UPuzzlePlatformGameInstance::JoinServer(const FString& Address)
{
	UEngine* Engine = GetEngine();

	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 5.f, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();

	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(*Address, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformGameInstance::HostServer()
{
	if (SessionInterface.IsValid())
	{
		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (ExistingSession != nullptr)
		{
			SessionInterface->DestroySession(SESSION_NAME);
			CreateSession();
		}
		else
		{
			CreateSession();
		}

		UE_LOG(LogTemp, Warning, TEXT("Created Session"));

	
	}
}

void UPuzzlePlatformGameInstance::OnCreateSessionComplete(FName SessionName, bool Succesful)
{
	if (!Succesful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed To Create Session"));
		return;
	}

	UEngine* Engine = GetEngine();

	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 5.f, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();

	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/ThirdPersonBP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformGameInstance::OnDestroySessionComplete(FName SessionName, bool Succesful)
{
	if (Succesful)
	{
		CreateSession();
	}
}

void UPuzzlePlatformGameInstance::CreateSession()
{
	SessionSettings = MakeShareable(new FOnlineSessionSettings());

	SessionInterface->CreateSession(0, TEXT("Game Session"), *SessionSettings);
}

void UPuzzlePlatformGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;

	ActiveMenu = CreateWidget<UMenuWidget>(this, MenuClass);

	if (!ensure(ActiveMenu != nullptr)) return;

	ActiveMenu->Setup();

	ActiveMenu->SetupMenuInterface(this);
}

void UPuzzlePlatformGameInstance::LoadInGameMenu()
{
	if (!ensure(MenuClass != nullptr)) return;

	ActiveMenu = CreateWidget<UMenuWidget>(this, GameOverlayClass);

	if (!ensure(ActiveMenu != nullptr)) return;

	ActiveMenu->Setup();

	ActiveMenu->SetupMenuInterface(this);
}

void UPuzzlePlatformGameInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();

	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel("/Game/ThirdPersonBP/Maps/MainMenuMap", ETravelType::TRAVEL_Absolute);
}