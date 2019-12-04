// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include <SubclassOf.h>
#include "MenuSystem/MenuInterface.h"
#include <OnlineSubsystem.h>
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
	void JoinServer(const FString& Address);

private:
	//Initialization
	void AssignSessionEvents();

	//Session Events
	void OnCreateSessionComplete(FName SessionName, bool Succesful);
	void OnDestroySessionComplete(FName SessionName, bool Succesful);

	//Session Functions
	void CreateSession();

private:

	class UMenuWidget* ActiveMenu;

	class IOnlineSubsystem* OnlineSubsystem;

	IOnlineSessionPtr SessionInterface;

	TSharedPtr<class FOnlineSessionSettings> SessionSettings;

	TSubclassOf<class UUserWidget> MenuClass;

	TSubclassOf<class UUserWidget> GameOverlayClass;
};