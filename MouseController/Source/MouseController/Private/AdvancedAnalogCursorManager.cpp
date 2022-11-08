#include "AdvancedAnalogCursorManager.h"
#include "Framework/Application/SlateApplication.h"
#include "Engine/Engine.h"

void UAdvancedAnalogCursorManager::Deinitialize()
{
	Super::Deinitialize();
	// When the local player is ending, cleanup the analog cursor
	UnregisterAdvancedAnalogCursor();
}

void UAdvancedAnalogCursorManager::CreateAdvancedAnalogCursor()
{
	AdvancedAnalogCursor = MakeShareable(new FAdvancedAnalogCursor);
}

void UAdvancedAnalogCursorManager::RegisterAdvancedAnalogCursor()
{
	// Ensure that slate and the world is valid
	if (FSlateApplication::IsInitialized() && GetWorld())
	{
		// If the shared ptr isnt tied to a valid obj then create one and connect the two
		if (!IsAdvancedAnalogCursorValid())
		{
			AdvancedAnalogCursor = MakeShareable(new FAdvancedAnalogCursor);
		}
		// Check that we're not re-adding it(which counts as a duplicate)
		if (!ContainsAdvancedAnalogCursorInputProcessor())
		{
			FSlateApplication::Get().RegisterInputPreProcessor(AdvancedAnalogCursor);
		}
	}
}

void UAdvancedAnalogCursorManager::UnregisterAdvancedAnalogCursor()
{
	if (FSlateApplication::IsInitialized())
	{
		// Dont try to remove it if we already removed it, you may say overkill I say ensuring safeguards
		if (ContainsAdvancedAnalogCursorInputProcessor())
		{
			FSlateApplication::Get().UnregisterInputPreProcessor(AdvancedAnalogCursor);
		}
	}
}

bool UAdvancedAnalogCursorManager::IsAdvancedAnalogCursorValid() const
{
	return AdvancedAnalogCursor.IsValid();
}

bool UAdvancedAnalogCursorManager::ContainsAdvancedAnalogCursorInputProcessor() const
{
	if (FSlateApplication::IsInitialized())
	{
		// Continue if we're using a valid cursor
		if (IsAdvancedAnalogCursorValid())
		{
			// Returns true if index is greater than -1, false if less than/equal to -1
			const int32 FoundIndex = FSlateApplication::Get().FindInputPreProcessor(AdvancedAnalogCursor);
			return (FoundIndex > -1);
		}
	}
	return false;
}

bool UAdvancedAnalogCursorManager::SimulateMouseButtonPressed(class APlayerController* PlayerController, TEnumAsByte <EMCMouseButton> InMouseButton)
{
	if (IsAdvancedAnalogCursorValid())
	{
		return AdvancedAnalogCursor.Get()->SimulateMouseButtonPressed(PlayerController, InMouseButton);
	}
	return false;
}

bool UAdvancedAnalogCursorManager::SimulateMouseButtonReleased(class APlayerController* PlayerController, TEnumAsByte <EMCMouseButton> InMouseButton)
{
	if (IsAdvancedAnalogCursorValid())
	{
		return AdvancedAnalogCursor.Get()->SimulateMouseButtonReleased(PlayerController, InMouseButton);
	}
	return false;
}

bool UAdvancedAnalogCursorManager::SimulateMouseAxis(class APlayerController* PlayerController, TEnumAsByte <EMCMouseAxis> InMouseButton, float InAnalogValue, float InScale)
{
	if (IsAdvancedAnalogCursorValid())
	{
		return AdvancedAnalogCursor.Get()->SimulateMouseAxis(PlayerController, InMouseButton, InAnalogValue, InScale);
	}
	return false;
}

float UAdvancedAnalogCursorManager::GetAcceleration()
{
	if (IsAdvancedAnalogCursorValid())
	{
		return AdvancedAnalogCursor.Get()->GetAcceleration();
	}
	return -1;
}

void UAdvancedAnalogCursorManager::SetAcceleration(float NewAcceleration)
{
	if (IsAdvancedAnalogCursorValid())
	{
		AdvancedAnalogCursor.Get()->SetAcceleration(NewAcceleration);
	}
}

float UAdvancedAnalogCursorManager::GetMaxSpeed()
{
	if (IsAdvancedAnalogCursorValid())
	{
		return AdvancedAnalogCursor.Get()->GetMaxSpeed();
	}
	return -1;
}

void UAdvancedAnalogCursorManager::SetMaxSpeed(float NewMaxSpeed)
{
	if (IsAdvancedAnalogCursorValid())
	{
		AdvancedAnalogCursor.Get()->SetMaxSpeed(NewMaxSpeed);
	}
}

float UAdvancedAnalogCursorManager::GetStickySlowdown()
{
	if (IsAdvancedAnalogCursorValid())
	{
		return AdvancedAnalogCursor.Get()->GetStickySlowdown();
	}
	return -1;
}

void UAdvancedAnalogCursorManager::SetStickySlowdown(float NewStickySlowdown)
{
	if (IsAdvancedAnalogCursorValid())
	{
		AdvancedAnalogCursor.Get()->SetStickySlowdown(NewStickySlowdown);
	}
}

float UAdvancedAnalogCursorManager::GetDeadZone()
{
	if (IsAdvancedAnalogCursorValid())
	{
		return AdvancedAnalogCursor.Get()->GetDeadZone();
	}
	return -1;
}

void UAdvancedAnalogCursorManager::SetDeadZone(float NewDeadZone)
{
	if (IsAdvancedAnalogCursorValid())
	{
		AdvancedAnalogCursor.Get()->SetDeadZone(NewDeadZone);
	}
}

TEnumAsByte <EMCAnalogCursorMode> UAdvancedAnalogCursorManager::GetMode()
{
	if (IsAdvancedAnalogCursorValid())
	{
		return ConvertAnalogCursorModeToEMCAnalogCursorMode(AdvancedAnalogCursor.Get()->GetMode());
	}
	return EMCAnalogCursorMode::AcceleratedMovement;
}

void UAdvancedAnalogCursorManager::SetMode(TEnumAsByte <EMCAnalogCursorMode> NewMode)
{
	if (IsAdvancedAnalogCursorValid())
	{
		AdvancedAnalogCursor.Get()->SetMode(ConvertEMCAnalogCursorModeToAnalogCursorMode(NewMode));
	}
}

bool UAdvancedAnalogCursorManager::GetInputAllowed()
{
	if (IsAdvancedAnalogCursorValid())
	{
		return AdvancedAnalogCursor.Get()->GetInputAllowed();
	}
	return false;
}

void UAdvancedAnalogCursorManager::SetInputAllowed(bool InInputAllowed)
{
	if (IsAdvancedAnalogCursorValid())
	{
		return AdvancedAnalogCursor.Get()->SetInputAllowed(InInputAllowed);
	}
}

TMap <FInputActionKey, TEnumAsByte <EMCMouseButton>> UAdvancedAnalogCursorManager::GetInputActionKeyMap()
{
	if (IsAdvancedAnalogCursorValid())
	{
		return AdvancedAnalogCursor.Get()->GetInputActionKeyMap();
	}
	return {};
}

void UAdvancedAnalogCursorManager::SetInputActionKeyMap(TMap <FInputActionKey, TEnumAsByte <EMCMouseButton>> InMap)
{
	if (IsAdvancedAnalogCursorValid())
	{
		AdvancedAnalogCursor.Get()->SetInputActionKeyMap(InMap);
	}
}

void UAdvancedAnalogCursorManager::AddInputActionKey(FInputActionKey InKey, TEnumAsByte <EMCMouseButton> InMouseButton)
{
	 AdvancedAnalogCursor.Get()->AddInputActionKey(InKey, InMouseButton);
}

void UAdvancedAnalogCursorManager::ClearInputActionKeyMap()
{
	if (IsAdvancedAnalogCursorValid())
	{
		AdvancedAnalogCursor.Get()->ClearInputActionKeyMap();
	}
}

bool UAdvancedAnalogCursorManager::ContainsInputActionKey(FInputActionKey InKey)
{
	if (IsAdvancedAnalogCursorValid())
	{
		return AdvancedAnalogCursor.Get()->ContainsInputActionKey(InKey);
	}
	return false;
}

void UAdvancedAnalogCursorManager::FindInputActionKey(FInputActionKey InKey, TEnumAsByte <EMCMouseButton>& OutMouseButton, bool& OutReturn)
{
	if (IsAdvancedAnalogCursorValid())
	{
		std::pair <EMCMouseButton, bool> TempReturn = AdvancedAnalogCursor.Get()->FindInputActionKey(InKey);
		OutMouseButton = TempReturn.first;
		OutReturn = TempReturn.second;
		return;
	}
	OutMouseButton = EMCMouseButton::LeftMouseButton;
	OutReturn = false;
}

TArray <FInputActionKey> UAdvancedAnalogCursorManager::InputActionKeyMapKeys()
{
	if (IsAdvancedAnalogCursorValid())
	{
		return AdvancedAnalogCursor.Get()->InputActionKeyMapKeys();
	}
	return {};
}

int UAdvancedAnalogCursorManager::InputActionKeyMapLength()
{
	if (IsAdvancedAnalogCursorValid())
	{
		return AdvancedAnalogCursor.Get()->InputActionKeyMapLength();
	}
	return 0;
}

bool UAdvancedAnalogCursorManager::RemoveInputActionKey(FInputActionKey InKey)
{
	if (IsAdvancedAnalogCursorValid())
	{
		return AdvancedAnalogCursor.Get()->RemoveInputActionKey(InKey);
	}
	return false;
}

TArray <TEnumAsByte <EMCMouseButton>> UAdvancedAnalogCursorManager::InputActionKeyMapValues()
{
	if (IsAdvancedAnalogCursorValid())
	{
		TArray <TEnumAsByte <EMCMouseButton>> NewValues;
		TArray <TEnumAsByte <EMCMouseButton>> OldValues = AdvancedAnalogCursor.Get()->InputActionKeyMapValues();
		TEnumAsByte <EMCMouseButton> TempMouseButton;
		for (int32 i = 0; i != OldValues.Num(); ++i)
		{
			TempMouseButton = OldValues[i];
			NewValues.Add(TempMouseButton);
		}
		return NewValues;
	}
	return {};
}

TMap <FInputAxisKey, TEnumAsByte <EMCMouseAxis>> UAdvancedAnalogCursorManager::GetInputAxisKeyMap()
{
	if (IsAdvancedAnalogCursorValid())
	{
		return AdvancedAnalogCursor.Get()->GetInputAxisKeyMap();
	}
	return {};
}

void UAdvancedAnalogCursorManager::SetInputAxisKeyMap(TMap <FInputAxisKey, TEnumAsByte <EMCMouseAxis>> InMap)
{
	if (IsAdvancedAnalogCursorValid())
	{
		AdvancedAnalogCursor.Get()->SetInputAxisKeyMap(InMap);
	}
}

void UAdvancedAnalogCursorManager::AddInputAxisKey(FInputAxisKey InKey, TEnumAsByte <EMCMouseAxis> InMouseAxis)
{
	AdvancedAnalogCursor.Get()->AddInputAxisKey(InKey, InMouseAxis);
}

void UAdvancedAnalogCursorManager::ClearInputAxisKeyMap()
{
	if (IsAdvancedAnalogCursorValid())
	{
		AdvancedAnalogCursor.Get()->ClearInputAxisKeyMap();
	}
}

bool UAdvancedAnalogCursorManager::ContainsInputAxisKey(FInputAxisKey InKey)
{
	if (IsAdvancedAnalogCursorValid())
	{
		return AdvancedAnalogCursor.Get()->ContainsInputAxisKey(InKey);
	}
	return false;
}

void UAdvancedAnalogCursorManager::FindInputAxisKey(FInputAxisKey InKey, TEnumAsByte <EMCMouseAxis>& OutMouseAxis, bool& OutReturn)
{
	if (IsAdvancedAnalogCursorValid())
	{
		std::pair <EMCMouseAxis, bool> TempReturn = AdvancedAnalogCursor.Get()->FindInputAxisKey(InKey);
		OutMouseAxis = TempReturn.first;
		OutReturn = TempReturn.second;
		return;
	}
	OutMouseAxis = EMCMouseAxis::MouseXAxis;
	OutReturn = false;
}

TArray <FInputAxisKey> UAdvancedAnalogCursorManager::InputAxisKeyMapKeys()
{
	if (IsAdvancedAnalogCursorValid())
	{
		return AdvancedAnalogCursor.Get()->InputAxisKeyMapKeys();
	}
	return {};
}

int UAdvancedAnalogCursorManager::InputAxisKeyMapLength()
{
	if (IsAdvancedAnalogCursorValid())
	{
		return AdvancedAnalogCursor.Get()->InputAxisKeyMapLength();
	}
	return 0;
}

bool UAdvancedAnalogCursorManager::RemoveInputAxisKey(FInputAxisKey InKey)
{
	if (IsAdvancedAnalogCursorValid())
	{
		return AdvancedAnalogCursor.Get()->RemoveInputAxisKey(InKey);
	}
	return false;
}

TArray <TEnumAsByte <EMCMouseAxis>> UAdvancedAnalogCursorManager::InputAxisKeyMapValues()
{
	if (IsAdvancedAnalogCursorValid())
	{
		TArray <TEnumAsByte <EMCMouseAxis>> NewValues;
		TArray <TEnumAsByte <EMCMouseAxis>> OldValues = AdvancedAnalogCursor.Get()->InputAxisKeyMapValues();
		TEnumAsByte <EMCMouseAxis> TempMouseButton;
		for (int32 i = 0; i != OldValues.Num(); ++i)
		{
			TempMouseButton = OldValues[i];
			NewValues.Add(TempMouseButton);
		}
		return NewValues;
	}
	return {};
}

TEnumAsByte <EMCAnalogCursorMode> UAdvancedAnalogCursorManager::ConvertAnalogCursorModeToEMCAnalogCursorMode(AnalogCursorMode::Type Mode)
{
	switch (Mode)
	{
		case AnalogCursorMode::Direct:
			return EMCAnalogCursorMode::DirectMovement;
		case AnalogCursorMode::Accelerated:
			return EMCAnalogCursorMode::AcceleratedMovement;	
	}
	return EMCAnalogCursorMode::DirectMovement;
}

AnalogCursorMode::Type UAdvancedAnalogCursorManager::ConvertEMCAnalogCursorModeToAnalogCursorMode(TEnumAsByte <EMCAnalogCursorMode> Mode)
{
	switch (Mode)
	{
	case EMCAnalogCursorMode::DirectMovement:
		return AnalogCursorMode::Direct;
	case EMCAnalogCursorMode::AcceleratedMovement:
		return AnalogCursorMode::Accelerated;
	}
	return AnalogCursorMode::Direct;
}