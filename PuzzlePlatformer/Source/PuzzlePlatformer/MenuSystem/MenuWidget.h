// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void Setup();

	virtual void SetupMenuInterface(class IMenuInterface* MenuInterface);

protected:
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

	IMenuInterface* MenuInterface;
};
