#pragma once

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/EditableTextBox.h"
#include "Components/Border.h"
#include "Components/ScrollBox.h"
#include "Components/CanvasPanelSlot.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"

UENUM(BlueprintType)
enum class ESlotType : uint8
{
	Inventory,
	Skill,
	Quick
};

