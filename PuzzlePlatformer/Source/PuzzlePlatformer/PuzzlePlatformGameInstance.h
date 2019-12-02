// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzlePlatformGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API UPuzzlePlatformGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPuzzlePlatformGameInstance();

	virtual void Init() override;

	UFUNCTION(Exec)
		void HostServer();

	UFUNCTION(Exec)
		void JoinServer(const FString& Address);

};