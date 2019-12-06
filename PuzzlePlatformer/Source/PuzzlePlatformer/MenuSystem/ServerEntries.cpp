// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerEntries.h"
#include <TextBlock.h>
#include <Button.h>
#include "MainMenu.h"

void UServerEntries::SetServerIDText(const FString& Text)
{
	ServerID->Text = FText::FromString(Text);
}

void UServerEntries::SetParentMenu(class UMainMenu* UserWidget, uint32 index)
{
	MainMenu = UserWidget;
	ButtonIndex = index;
	EntryButton->OnClicked.AddDynamic(this, &UServerEntries::OnClicked);
}

void UServerEntries::OnClicked()
{
	MainMenu->SelectIndex(ButtonIndex);
	UE_LOG(LogTemp, Warning, TEXT("Set Index: %i"), ButtonIndex);
}
