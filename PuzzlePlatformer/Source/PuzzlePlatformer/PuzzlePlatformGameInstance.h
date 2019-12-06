// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include <SubclassOf.h>
#include "MenuSystem/MenuInterface.h"
#include <OnlineSubsystem.h>
#include <OnlineSessionInterface.h>
#include "PuzzlePlatformGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API UPuzzlePlatformGameInstance : public UGameInstance , public IMenuInterface
{
	GENERATED_BODY()

public:

	UPuzzlePlatformGameInstance();

	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	void RefreshServerList();

	// Menu Functions
	UFUNCTION(Exec, BlueprintCallable)
	void LoadMenu();

	UFUNCTION(Exec, BlueprintCallable)
	void LoadInGameMenu();

	UFUNCTION(Exec, BlueprintCallable)
	virtual void LoadMainMenu() override;

	//Server Functions
	UFUNCTION(Exec)
	void HostServer();

	UFUNCTION(Exec)
	void JoinServer(uint32 SearchResultIndex);

private:
	//Initialization
	void AssignSessionEvents();

	//Session Events
	void OnCreateSessionComplete(FName SessionName, bool Succesful);
	void OnDestroySessionComplete(FName SessionName, bool Succesful);
	void OnFindSessionsComplete(bool Succesful);

	void OnJoinSessionComplete(FName Session, EOnJoinSessionCompleteResult::Type Result);

	//Session Functions
	void CreateSession();

private:

	class UMenuWidget* ActiveMenu;

	class UPauseOverlay* InGameMenu;

	class UMainMenu* MainMenu;

	IOnlineSubsystem* OnlineSubsystem;

	IOnlineSessionPtr SessionInterface;

	TSharedPtr<class FOnlineSessionSearch>SessionSearch;

	TSharedPtr<class FOnlineSessionSettings> SessionSettings;

	TSubclassOf<class UMainMenu> MenuClass;

	TSubclassOf<class UPauseOverlay> GameOverlayClass;
};