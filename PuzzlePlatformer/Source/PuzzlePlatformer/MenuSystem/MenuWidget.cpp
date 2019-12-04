// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "PuzzlePlatformGameInstance.h"
#include "MenuInterface.h"

void UMenuWidget::Setup()
{
	this->bIsFocusable = true;

	this->AddToViewport();

	UWorld* World = GetWorld();

	if (!ensure(World != nullptr)) return;

	APlayerController* playerController = World->GetFirstPlayerController();

	if (!ensure(playerController != nullptr)) return;

	FInputModeUIOnly InputMode;

	InputMode.SetWidgetToFocus(this->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	playerController->SetInputMode(InputMode);

	playerController->bShowMouseCursor = true;
}

void UMenuWidget::SetupMenuInterface(IMenuInterface* MenuInterface)
{
	this->MenuInterface = MenuInterface;
}

void UMenuWidget::TearDown()
{
	this->RemoveFromViewport();

	APlayerController* PlayerController = this->GetOwningPlayer();

	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->bShowMouseCursor = false;

	FInputModeGameOnly InputMode;

	PlayerController->SetInputMode(InputMode);
}

void UMenuWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);

	TearDown();
}
