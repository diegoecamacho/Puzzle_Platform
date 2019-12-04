// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include <Button.h>
#include <WidgetSwitcher.h>
#include "MenuInterface.h"
#include <EditableTextBox.h>

bool UMainMenu::Initialize()
{
	bool Succesful = Super::Initialize();

	if (!Succesful) return false;

	Succesful = InitializeButtonEvents();

	return Succesful;
}

bool UMainMenu::InitializeButtonEvents()
{
	if (!ensure(HostButton != nullptr)) return false;

	HostButton->OnClicked.AddDynamic(this, &UMainMenu::OnHostPressed);

	if (!ensure(OpenJoinMenu != nullptr)) return false;

	OpenJoinMenu->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenuPressed);

	if (!ensure(ReturnMenuButton != nullptr)) return false;

	ReturnMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OnReturnButtonPressed);

	if (!ensure(JoinServerButton != nullptr)) return false;

	JoinServerButton->OnClicked.AddDynamic(this, &UMainMenu::OnJoinPressed);

	if (!ensure(QuitButton != nullptr)) return false;

	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);

	return true;
}

#pragma region Events

void UMainMenu::OnHostPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Host Server"));

	if (!ensure(MenuInterface != nullptr)) return;

	MenuInterface->HostServer();
}

void UMainMenu::OpenJoinMenuPressed()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::OnJoinPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Join Server"));

	if(!ensure(IPAddressField != nullptr)) return;

	const FString Address = IPAddressField->GetText().ToString();

	MenuInterface->JoinServer(Address);
}

void UMainMenu::OnReturnButtonPressed()
{
	if (!ensure(MainMenu != nullptr)) return;
	if (!ensure(MenuSwitcher != nullptr)) return;

	MenuSwitcher->SetActiveWidget(MainMenu);
}


void UMainMenu::QuitGame()
{
	APlayerController* PlayerController = GetOwningPlayer();
	UE_LOG(LogTemp, Warning, TEXT("Quit Game"));

	if(!ensure(PlayerController != nullptr)) return;


	PlayerController->ConsoleCommand("quit");
}

#pragma endregion Events