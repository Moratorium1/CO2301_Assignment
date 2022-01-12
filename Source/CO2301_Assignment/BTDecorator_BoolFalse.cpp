// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_BoolFalse.h"

UBTDecorator_BoolFalse::UBTDecorator_BoolFalse()
{
	NodeName = "Bool is False";
}

void UBTDecorator_BoolFalse::OnNodeActivation(FBehaviorTreeSearchData& SearchData)
{
	Super::OnNodeActivation(SearchData);
}
