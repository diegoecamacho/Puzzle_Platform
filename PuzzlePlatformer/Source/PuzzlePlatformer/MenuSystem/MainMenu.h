// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuInterface.h"
#include "MenuWidget.h"
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
	class UButton* OpenJoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinServerButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ReturnMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* IPAddressField;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;


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

	
};
