// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.h"
#include "PauseOverlay.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API UPauseOverlay : public UMenuWidget
{
	GENERATED_BODY()

private:

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelOverlayButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitOverlayButton;

public:

	virtual bool Initialize() override;

private:
	UFUNCTION()
	void OnCancelButtonClicked();

	UFUNCTION()
	void OnQuitButtonClicked();
};
