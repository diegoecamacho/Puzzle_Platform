// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerEntries.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API UServerEntries : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerID;

	UPROPERTY(meta = (BindWidget))
	class UButton* EntryButton;

private:

	UPROPERTY()
	class UMainMenu* MainMenu;

	uint32 ButtonIndex;

public:

	UFUNCTION(BlueprintCallable)
	void SetServerIDText(const FString& Text);

	void SetParentMenu(class UMainMenu* UserWidget, uint32 index);

	UFUNCTION()
		void OnClicked();

	
};
