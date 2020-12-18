// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSceneOutlinerWidget.h"
#include "Widgets/SCompoundWidget.h"
#include <IDetailsView.h>

/**
 * 
 */
class SLATEGUIDE_API SSceneOutlinerWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSceneOutlinerWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	void OnActorSelectedFromOutliner(AActor* SelectedActor);

	FReply OnCreateDetailsView();
	FReply OnCreateCustomSceneOutliner();

	TSharedPtr<IDetailsView> DetailsView;
};
