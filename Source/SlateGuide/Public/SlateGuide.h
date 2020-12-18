// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Widgets/SBasicWidget.h"
#include "Widgets/SNotificationsWidget.h"
#include "Widgets/SDetailsViewWidget.h"
#include "Settings/SlateGuideDetailsViewSettings.h"
#include "Widgets/SSceneOutlinerWidget.h"
//#include "Widgets/SBasicWidget.h"
//#include "Widgets/SNotificationsWidget.h"
//#include "Widgets/SDetailsViewWidget.h"

class FToolBarBuilder;
class FMenuBuilder;

class FSlateGuideModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	
private:

	void AddToolbarExtension(FToolBarBuilder& Builder);
	void AddMenuExtension(FMenuBuilder& Builder);

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

	TSharedPtr<class SBasicWidget> BasicWidget;
	TSharedPtr<class SNotificationsWidget> NotificationWidget;
	TSharedPtr<class SDetailsViewWidget> DetailsViewWidget; 
	TSharedPtr<class SSceneOutlinerWidget> SceneOutlinerWidget;

	USlateGuideDetailsViewSettings* DetailSettings;
private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
