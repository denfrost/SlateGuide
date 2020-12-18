// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "SlateGuideStyle.h"

class FSlateGuideCommands : public TCommands<FSlateGuideCommands>
{
public:

	FSlateGuideCommands()
		: TCommands<FSlateGuideCommands>(TEXT("SlateGuideSlateGuide"), NSLOCTEXT("Contexts", "Slate Guide Modal Window", "Slate Guide Plugin"), NAME_None, FSlateGuideStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};