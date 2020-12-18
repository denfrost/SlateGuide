// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SDetailsViewWidget.h"
#include "Widgets/SCompoundWidget.h"
#include <IDetailsView.h>

/**
 * 
 */
class SLATEGUIDE_API SDetailsViewWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDetailsViewWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	FReply OnCreateDetailsView();
	FReply OnCreateCustomSceneOutliner();

	TSharedPtr<IDetailsView> DetailsView;
};
