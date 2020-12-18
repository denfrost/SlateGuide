// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SlateGuide.h"
#include "SlateGuideStyle.h"
#include "SlateGuideCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include <Widgets/Input/SButton.h>
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include <EditorStyleSet.h>

#include "Widgets/SNotificationsWidget.h"
#include "Widgets/SBasicWidget.h"
#include "Widgets/SDetailsViewWidget.h"
#include "Widgets/SSceneOutlinerWidget.h"

static const FName StyleGuideTabName("StyleGuideSlateGuide");

#define LOCTEXT_NAMESPACE "FSlateGuideModule"

void FSlateGuideModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FSlateGuideStyle::Initialize();
	FSlateGuideStyle::ReloadTextures();

	FSlateGuideCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FSlateGuideCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FSlateGuideModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	//Register our Slate Modal Window in the Window dropdown of Unreal.
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FSlateGuideModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}

	//Register our Slate Modal Window in the main toolbar beside Settings.
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FSlateGuideModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(StyleGuideTabName, FOnSpawnTab::CreateRaw(this, &FSlateGuideModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FSlateGuideTabName", "Slate Guide Modal Window"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	DetailSettings = NewObject<USlateGuideDetailsViewSettings>();
	DetailSettings->AddToRoot();
}

void FSlateGuideModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FSlateGuideStyle::Shutdown();

	FSlateGuideCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(StyleGuideTabName);
}

TSharedRef<SDockTab> FSlateGuideModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText ExampleText = LOCTEXT("ExampleWidgetText", "Slate Guide");

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.WidthOverride(100.0f)
			.HeightOverride(300.f)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.FillHeight(0.1f)
				.MaxHeight(32.0f)
				.Padding(FMargin(10.0f))
				[
					SNew(STextBlock)
					.Text(ExampleText)
					.Font(FCoreStyle::GetDefaultFontStyle("Regular", 18))
				]

				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(FMargin(4.0f))
				[
					SAssignNew(BasicWidget, SBasicWidget)
				]

				+ SVerticalBox::Slot()
				.FillHeight(1.0f)
				.MaxHeight(32.0f)
				.Padding(FMargin(4.0f))
				[
					SAssignNew(NotificationWidget, SNotificationsWidget)
				]

				+ SVerticalBox::Slot()
				.FillHeight(1.0f)
					.VAlign(VAlign_Fill)
					.Padding(FMargin(4.0f))
				[

					SNew(SBorder)
					.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
					.Padding(FMargin(4.0f))
					[

						SNew(SHorizontalBox)
						+SHorizontalBox::Slot()
						.FillWidth(1.0f)
						.Padding(FMargin(4.0f))
						[
							SAssignNew(DetailsViewWidget, SDetailsViewWidget)
						]

						+SHorizontalBox::Slot()
						.FillWidth(1.0f)
						.Padding(FMargin(4.0f))
						[
							SAssignNew(SceneOutlinerWidget, SSceneOutlinerWidget)
						]

					]
				
				]	

			]
		];
}

void FSlateGuideModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(StyleGuideTabName);
}

void FSlateGuideModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FSlateGuideCommands::Get().OpenPluginWindow);
}

void FSlateGuideModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FSlateGuideCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSlateGuideModule, SlateGuide)