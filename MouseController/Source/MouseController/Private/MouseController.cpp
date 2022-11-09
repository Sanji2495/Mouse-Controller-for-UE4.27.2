#include "MouseController.h"
#include "AdvancedAnalogCursorManager.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/Application/NavigationConfig.h"
#include "Engine/Engine.h"

void UMouseController::CreateMouseController(class APlayerController* PlayerController)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->CreateAdvancedAnalogCursor();
		}
	}
}

void UMouseController::EnableMouseController(class APlayerController* PlayerController)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->RegisterAdvancedAnalogCursor();
			PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->SetInputAllowed(true);
		}
	}
}

void UMouseController::DisableMouseController(class APlayerController* PlayerController)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->UnregisterAdvancedAnalogCursor();
			PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->SetInputAllowed(false);
		}
	}
}

void UMouseController::SetNavigation(bool bNewTabNavigation, bool bNewKeyNavigation, bool bNewAnalogNavigation)
{
	if (FSlateApplication::IsInitialized())
	{
		TSharedRef <FNavigationConfig> TempConfig = FSlateApplication::Get().GetNavigationConfig();

		TempConfig->bTabNavigation = bNewTabNavigation;
		TempConfig->bKeyNavigation = bNewKeyNavigation;
		TempConfig->bAnalogNavigation = bNewAnalogNavigation;
	}
}

bool UMouseController::IsMouseControllerValid(class APlayerController* PlayerController)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			return PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->IsAdvancedAnalogCursorValid();
		}
	}
	return false;
}

bool UMouseController::IsMouseControllerEnabled(class APlayerController* PlayerController)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			return PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->ContainsAdvancedAnalogCursorInputProcessor();
		}
	}
	return false;
}

bool UMouseController::SimulateMouseButtonPressed(class APlayerController* PlayerController, TEnumAsByte <EMCMouseButton> InMouseButton)
{
	return PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->SimulateMouseButtonPressed(PlayerController, InMouseButton);
}

bool UMouseController::SimulateMouseButtonReleased(class APlayerController* PlayerController, TEnumAsByte <EMCMouseButton> InMouseButton)
{
	return PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->SimulateMouseButtonReleased(PlayerController, InMouseButton);
}

bool UMouseController::SimulateMouseAxis(class APlayerController* PlayerController, TEnumAsByte <EMCMouseAxis> InMouseButton, float InAnalogValue, float InScale)
{
	return PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->SimulateMouseAxis(PlayerController, InMouseButton, InAnalogValue, InScale);
}

float UMouseController::GetAcceleration(class APlayerController* PlayerController)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			return PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->GetAcceleration();
		}
	}
	return -1;
}

void UMouseController::SetAcceleration(class APlayerController* PlayerController, float NewAcceleration)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->SetAcceleration(NewAcceleration);
		}
	}
}

float UMouseController::GetMaxSpeed(class APlayerController* PlayerController)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			return PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->GetMaxSpeed();
		}
	}
	return -1;
}

void UMouseController::SetMaxSpeed(class APlayerController* PlayerController, float NewMaxSpeed)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->SetMaxSpeed(NewMaxSpeed);
		}
	}
}

float UMouseController::GetStickySlowdown(class APlayerController* PlayerController)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			return PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->GetStickySlowdown();
		}
	}
	return -1;
}

void UMouseController::SetStickySlowdown(class APlayerController* PlayerController, float NewStickySlowdown)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->SetStickySlowdown(NewStickySlowdown);
		}
	}
}

float UMouseController::GetDeadZone(class APlayerController* PlayerController)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			return PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->GetDeadZone();
		}
	}
	return -1;
}

void UMouseController::SetDeadZone(class APlayerController* PlayerController, float NewDeadZone)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->SetDeadZone(NewDeadZone);
		}
	}
}

TEnumAsByte <EMCAnalogCursorMode> UMouseController::GetMode(class APlayerController* PlayerController)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			return PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->GetMode();
		}
	}
	return EMCAnalogCursorMode::AcceleratedMovement;
}

void UMouseController::SetMode(class APlayerController* PlayerController, TEnumAsByte <EMCAnalogCursorMode> NewMode)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->SetMode(NewMode);
		}
	}
}

TMap <FInputActionKey, TEnumAsByte <EMCMouseButton>> UMouseController::GetInputActionKeyMap(class APlayerController* PlayerController)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			return PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->GetInputActionKeyMap();
		}
	}
	return {};
}

void UMouseController::SetInputActionKeyMap(class APlayerController* PlayerController, TMap <FInputActionKey, TEnumAsByte <EMCMouseButton>> InMap)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->SetInputActionKeyMap(InMap);
		}
	}
}

void UMouseController::AddInputActionKey(class APlayerController* PlayerController, FInputActionKey InKey, TEnumAsByte <EMCMouseButton> InMouseButton)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->AddInputActionKey(InKey, InMouseButton);
		}
	}
}

void UMouseController::ClearInputActionKeyMap(class APlayerController* PlayerController)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->ClearInputActionKeyMap();
		}
	}
}

bool UMouseController::ContainsInputActionKey(class APlayerController* PlayerController, FInputActionKey InKey)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			return PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->ContainsInputActionKey(InKey);
		}
	}
	return false;
}

void UMouseController::FindInputActionKey(class APlayerController* PlayerController, FInputActionKey InKey, TEnumAsByte <EMCMouseButton>& OutMouseButton, bool& OutReturn)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->FindInputActionKey(InKey, OutMouseButton, OutReturn);
			return;
		}
	}
	OutMouseButton = EMCMouseButton::LeftMouseButton;
	OutReturn = false;
}

TArray <FInputActionKey> UMouseController::InputActionKeyMapKeys(class APlayerController* PlayerController)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			return PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->InputActionKeyMapKeys();
		}
	}
	return {};
}

int UMouseController::InputActionKeyMapLength(class APlayerController* PlayerController)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			return PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->InputActionKeyMapLength();
		}
	}
	return 0;
}

bool UMouseController::RemoveInputActionKey(class APlayerController* PlayerController, FInputActionKey InKey)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			return PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->RemoveInputActionKey(InKey);
		}
	}
	return false;
}

TArray <TEnumAsByte <EMCMouseButton>> UMouseController::InputActionKeyMapValues(class APlayerController* PlayerController)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			return PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->InputActionKeyMapValues();
		}
	}
	return {};
}



TMap <FInputAxisKey, TEnumAsByte <EMCMouseAxis>> UMouseController::GetInputAxisKeyMap(class APlayerController* PlayerController)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			return PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->GetInputAxisKeyMap();
		}
	}
	return {};
}

void UMouseController::SetInputAxisKeyMap(class APlayerController* PlayerController, TMap <FInputAxisKey, TEnumAsByte <EMCMouseAxis>> InMap)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->SetInputAxisKeyMap(InMap);
		}
	}
}

void UMouseController::AddInputAxisKey(class APlayerController* PlayerController, FInputAxisKey InKey, TEnumAsByte <EMCMouseAxis> InMouseAxis)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->AddInputAxisKey(InKey, InMouseAxis);
		}
	}
}

void UMouseController::ClearInputAxisKeyMap(class APlayerController* PlayerController)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->ClearInputAxisKeyMap();
		}
	}
}

bool UMouseController::ContainsInputAxisKey(class APlayerController* PlayerController, FInputAxisKey InKey)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			return PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->ContainsInputAxisKey(InKey);
		}
	}
	return false;
}

void UMouseController::FindInputAxisKey(class APlayerController* PlayerController, FInputAxisKey InKey, TEnumAsByte <EMCMouseAxis>& OutMouseAxis, bool& OutReturn)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->FindInputAxisKey(InKey, OutMouseAxis, OutReturn);
			return;
		}
	}
	OutMouseAxis = EMCMouseAxis::MouseXAxis;
	OutReturn = false;
}

TArray <FInputAxisKey> UMouseController::InputAxisKeyMapKeys(class APlayerController* PlayerController)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			return PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->InputAxisKeyMapKeys();
		}
	}
	return {};
}

int UMouseController::InputAxisKeyMapLength(class APlayerController* PlayerController)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			return PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->InputAxisKeyMapLength();
		}
	}
	return 0;
}

bool UMouseController::RemoveInputAxisKey(class APlayerController* PlayerController, FInputAxisKey InKey)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			return PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->RemoveInputAxisKey(InKey);
		}
	}
	return false;
}

TArray <TEnumAsByte <EMCMouseAxis>> UMouseController::InputAxisKeyMapValues(class APlayerController* PlayerController)
{
	if (PlayerController)
	{
		if (PlayerController->GetLocalPlayer())
		{
			return PlayerController->GetLocalPlayer()->GetSubsystem<UAdvancedAnalogCursorManager>()->InputAxisKeyMapValues();
		}
	}
	return {};
}