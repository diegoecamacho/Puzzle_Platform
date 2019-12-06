// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuInterface.h"
#include "MenuWidget.h"
#include <SubclassOf.h>
#include "MainMenu.generated.h"

/**
 *
 */
UCLASS()
class PUZZLEPLATFORMER_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* OpenJoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinServerButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* RefreshButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ReturnMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* ListScrollBox;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	TSubclassOf<class UUserWidget> ServerEntries;

	TOptional<uint32> SelectedIndex;

public:
	UMainMenu();

	virtual void SetServerList(const TArray<FString>& ServerList);

	void SelectIndex(uint32 Index);

protected:
	virtual bool Initialize() override;

private:
	bool InitializeButtonEvents();


	UFUNCTION()
	void OnHostPressed();

	UFUNCTION()
	void OpenJoinMenuPressed();

	UFUNCTION()
	void OnJoinPressed();

	UFUNCTION()
	void OnReturnButtonPressed();
	
	UFUNCTION()
	void QuitGame();

	UFUNCTION()
	void RefreshList();

public:
};
