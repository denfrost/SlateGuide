// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"


class FSlateGuideNotificationInfoModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	//Called from SlateGuideModalWindow module OnClicked delegate binding
	FReply OnCreateModalWindowNotificationInfo();
	
};
