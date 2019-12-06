// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include <Button.h>
#include <WidgetSwitcher.h>
#include "MenuInterface.h"
#include <EditableTextBox.h>
#include <UserWidget.h>
#include <ConstructorHelpers.h>
#include <AssertionMacros.h>
#include "ServerEntries.h"
#include <ScrollBox.h>


bool UMainMenu::Initialize()
{
	bool Succesful = Super::Initialize();

	if (!Succesful) return false;

	Succesful = InitializeButtonEvents();

	return Succesful;
}

UMainMenu::UMainMenu() : UMenuWidget()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ServerEntryBP(TEXT("/Game/MenuSystem/WBP_ServerEntry"));

	if(!ensure(ServerEntryBP.Class != nullptr)) return;

	ServerEntries = ServerEntryBP.Class;
}

void UMainMenu::SetServerList(const TArray<FString>& ServerList)
{

	ListScrollBox->ClearChildren();

	uint32 Index = 0;
	for (const FString& ServerName : ServerList )
	{
		UServerEntries* NewEntry = CreateWidget<UServerEntries>(this, ServerEntries);

		NewEntry->SetServerIDText(ServerName);

		NewEntry->SetParentMenu(this, Index);
		Index++;

		ListScrollBox->AddChild(NewEntry);
	}

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

	if (!ensure(RefreshButton != nullptr)) return false;

	RefreshButton->OnClicked.AddDynamic(this, &UMainMenu::RefreshList);

	return true;
}

void UMainMenu::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;
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
	if (SelectedIndex.IsSet() && MenuInterface != nullptr)
	{
		MenuInterface->JoinServer(SelectedIndex.GetValue());
	}
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

void UMainMenu::RefreshList()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->RefreshServerList();
	}
}

#pragma endregion Events