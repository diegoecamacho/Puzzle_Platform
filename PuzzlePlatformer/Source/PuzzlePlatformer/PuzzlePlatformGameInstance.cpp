// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformGameInstance.h"
#include <Engine/Engine.h>
#include <Engine/World.h>
#include <GameFramework/PlayerController.h>
#include <ConstructorHelpers.h>
#include "PlatformTrigger.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/MenuWidget.h"
#include <OnlineSessionSettings.h>
#include <SharedPointer.h>
#include "MenuSystem/PauseOverlay.h"

const static FName SESSION_NAME = TEXT("GameSession");

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance()
{
	static ConstructorHelpers::FClassFinder<UMainMenu> PlatformTriggerBP(TEXT("/Game/MenuSystem/WBP_MainMenu"));

	if (!ensure(PlatformTriggerBP.Class != nullptr)) return;

	MenuClass = PlatformTriggerBP.Class;

	static ConstructorHelpers::FClassFinder<UPauseOverlay> OverlayBP(TEXT("/Game/MenuSystem/WBP_Overlay"));

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
			AssignSessionEvents();
			RefreshServerList();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Subsystem found."));
	}
}

void UPuzzlePlatformGameInstance::RefreshServerList()
{
	
	if (SessionSearch == nullptr)
		SessionSearch = MakeShareable(new FOnlineSessionSearch());
	
	if (SessionSearch.IsValid())
	{
		SessionSearch->bIsLanQuery = true;
		UE_LOG(LogTemp, Warning, TEXT("Starting to find Session."));
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

void UPuzzlePlatformGameInstance::AssignSessionEvents()
{
	SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnCreateSessionComplete);
	SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnDestroySessionComplete);
	SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnFindSessionsComplete);
	SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnJoinSessionComplete);
	
}

void UPuzzlePlatformGameInstance::JoinServer(uint32 SearchResultIndex)
{
	if (!SessionInterface.IsValid()) return;
	if (!SessionSearch.IsValid()) return;
		
	SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[SearchResultIndex]);
}


void UPuzzlePlatformGameInstance::HostServer()
{
	UE_LOG(LogTemp, Warning, TEXT("Created Session"));
	if (SessionInterface.IsValid())
	{
		FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (ExistingSession != nullptr)
		{
			SessionInterface->DestroySession(SESSION_NAME);
			CreateSession();
		}
		else
		{
			CreateSession();
		}
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
}

void UPuzzlePlatformGameInstance::OnFindSessionsComplete(bool Succesful)
{
	UE_LOG(LogTemp, Warning, TEXT("Session Found"));

	if(!Succesful) return;

	if (SessionSearch.IsValid())
	{
		for (const FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults)
		{
			TArray<FString> ServerList;
			for (const FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults)
			{
				ServerList.Add(SearchResult.GetSessionIdStr());
			}

			MainMenu->SetServerList(ServerList);
		}
	}
}

void UPuzzlePlatformGameInstance::OnJoinSessionComplete(FName Session, EOnJoinSessionCompleteResult::Type Result)
{
	

	UE_LOG(LogTemp, Warning, TEXT("TEXT"));

	if (SessionInterface.IsValid()) return;

	FString Address;
	if (!SessionInterface->GetResolvedConnectString(Session, Address)) {
		UE_LOG(LogTemp, Warning, TEXT("Failed To get IP"));
		return;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Address: %s"), &Address);
	}
		
	UEngine* Engine = GetEngine();

	if (!ensure(Engine != nullptr)) return;

	APlayerController* PlayerController = GetFirstLocalPlayerController();

	if (!ensure(PlayerController != nullptr)) return;

	UWorld* World = GetWorld();

	if (!ensure(World != nullptr)) return;

	World->ServerTravel(Address, true);

	//PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformGameInstance::CreateSession()
{
	SessionSettings = MakeShareable(new FOnlineSessionSettings());

	SessionSettings->bIsLANMatch = true;
	SessionSettings->NumPublicConnections = 2;
	SessionSettings->bShouldAdvertise = true;

	SessionInterface->CreateSession(0, SESSION_NAME, *SessionSettings);
}

void UPuzzlePlatformGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;
	
	MainMenu = CreateWidget<UMainMenu>(this, MenuClass);

	MainMenu->SetupMenuInterface(this);
	
	MainMenu->Setup();
	//ActiveMenu = MainMenu;
}

void UPuzzlePlatformGameInstance::LoadInGameMenu()
{
	if (!ensure(GameOverlayClass != nullptr)) return;

	InGameMenu = CreateWidget<UPauseOverlay>(this, GameOverlayClass);

	InGameMenu->SetupMenuInterface(this);
	
	InGameMenu->Setup();
	//ActiveMenu = InGameMenu;
}

void UPuzzlePlatformGameInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();

	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel("/Game/ThirdPersonBP/Maps/MainMenuMap", ETravelType::TRAVEL_Absolute);
}