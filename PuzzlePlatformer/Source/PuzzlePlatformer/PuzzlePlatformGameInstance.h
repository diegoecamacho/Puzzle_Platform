// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include <SubclassOf.h>
#include "MenuSystem/MenuInterface.h"
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

	UFUNCTION(Exec, BlueprintCallable)
	void LoadMenu();

	UFUNCTION(Exec, BlueprintCallable)
	void LoadInGameMenu();

	UFUNCTION(Exec)
	void HostServer();

	UFUNCTION(Exec)
	void JoinServer(const FString& Address);

	TSubclassOf<class UUserWidget> MenuClass;
	TSubclassOf<class UUserWidget> GameOverlayClass;
};