// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SSceneOutlinerWidget.h"
#include <Widgets/SBoxPanel.h>
#include <EditorStyleSet.h>
#include "SlateOptMacros.h"
#include <Widgets/Input/SButton.h>
#include <PropertyEditorModule.h>
#include "Settings/SlateGuideDetailsViewSettings.h"
#include "SceneOutliner/Public/SceneOutlinerModule.h"

#define LOCTEXT_NAMESPACE "FSlateGuideModule"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSceneOutlinerWidget::Construct(const FArguments& InArgs)
{
	FSceneOutlinerModule& SceneOutlinerModule = FModuleManager::Get().LoadModuleChecked<FSceneOutlinerModule>(TEXT("SceneOutliner"));
	
	SceneOutliner::FInitializationOptions InitOptions;
	InitOptions.Mode = ESceneOutlinerMode::ActorBrowsing;
	InitOptions.bShowHeaderRow = false;

	TSharedRef<SWidget> MenuContent = 
		SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew( SBorder )
			.BorderImage( FEditorStyle::GetBrush("Menu.Background") )
			[
				SceneOutlinerModule.CreateSceneOutliner(InitOptions, FOnActorPicked::CreateSP(this, &SSceneOutlinerWidget::OnActorSelectedFromOutliner))
			]
		];

	ChildSlot
	[
		SNew(SVerticalBox)
		+SVerticalBox::Slot()
		.AutoHeight()
		.Padding(FMargin(4.0f))
		[
			SNew(STextBlock)
			.Text(LOCTEXT("SceneOutlinerTitle", "Scene Outliner Example: "))
			.Font(FCoreStyle::GetDefaultFontStyle("Regular", 13))
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.VAlign(VAlign_Fill)
		[
			MenuContent
		]
	];
}

void SSceneOutlinerWidget::OnActorSelectedFromOutliner(AActor* SelectedActor)
{

}

FReply SSceneOutlinerWidget::OnCreateDetailsView()
{
	return FReply::Handled();
}

FReply SSceneOutlinerWidget::OnCreateCustomSceneOutliner()
{
	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
#undef LOCTEXT_NAMESPACE
