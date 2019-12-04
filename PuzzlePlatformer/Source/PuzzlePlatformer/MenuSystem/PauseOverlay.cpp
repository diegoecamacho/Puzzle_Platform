// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseOverlay.h"
#include <Button.h>
#include "MenuInterface.h"


bool UPauseOverlay::Initialize()
{
	Super::Initialize();

	if (!ensure(CancelOverlayButton != nullptr)) return false;

	CancelOverlayButton->OnClicked.AddDynamic(this, &UPauseOverlay::OnCancelButtonClicked);

	if (!ensure(QuitOverlayButton != nullptr)) return false;

	QuitOverlayButton->OnClicked.AddDynamic(this, &UPauseOverlay::OnQuitButtonClicked);

	return true;
}

void UPauseOverlay::OnCancelButtonClicked()
{
	TearDown();
}

void UPauseOverlay::OnQuitButtonClicked()
{
	MenuInterface->LoadMainMenu();
}
