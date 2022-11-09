#include "AdvancedAnalogCursor.h"
#include "Framework/Application/AnalogCursor.h"
#include "InputCoreTypes.h"
#include "Input/Events.h"
#include "Widgets/SWidget.h"
#include "Layout/ArrangedChildren.h"
#include "Layout/WidgetPath.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/Application/SlateUser.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Engine/UserInterfaceSettings.h"
#include "Kismet/KismetMathLibrary.h"

void FAdvancedAnalogCursor::Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor>)
{
	if (bIsInputAllowed)
	{
		if (TSharedPtr<FSlateUser> SlateUser = SlateApp.GetUser(GetOwnerUserIndex()))
		{
			const FVector2D OldPosition = SlateUser->GetCursorPosition();

			float SpeedMult = 1.0f; // Used to do a speed multiplication before adding the delta to the position to make widgets sticky
			FVector2D AdjAnalogVals = CurrentAnalogValue; // A copy of the analog values so I can modify them based being over a widget, not currently doing this

			// Adjust analog values according to dead zone
			const float AnalogValsSize = AdjAnalogVals.Size();

			if (AnalogValsSize > 0.0f)
			{
				const float TargetSize = FMath::Max(AnalogValsSize - DeadZone, 0.0f) / (1.0f - DeadZone);
				AdjAnalogVals /= AnalogValsSize;
				AdjAnalogVals *= TargetSize;
			}

			//Adjust digital values and combine them with the analog values
			FVector2D AdjDigitalVals = { CurrentDigitalValue.X + CurrentDigitalValue.Y, CurrentDigitalValue.Z + CurrentDigitalValue.W };
			AdjDigitalVals.Normalize();
			FVector2D AdjVals;
			if (AdjDigitalVals.Size() > 0.5)
			{
				AdjVals = AdjAnalogVals + AdjDigitalVals;
			}
			else
			{
				AdjVals = AdjAnalogVals;
			}

			if (AdjVals.Size() > 1.0f) { AdjVals.Normalize(); }

			// Check if there is a sticky widget beneath the cursor
			FWidgetPath WidgetPath = SlateApp.LocateWindowUnderMouse(OldPosition, SlateApp.GetInteractiveTopLevelWindows(), false, SlateUser->GetUserIndex());
			if (WidgetPath.IsValid())
			{
				const FArrangedChildren::FArrangedWidgetArray& AllArrangedWidgets = WidgetPath.Widgets.GetInternalArray();
				for (const FArrangedWidget& ArrangedWidget : AllArrangedWidgets)
				{
					TSharedRef<SWidget> Widget = ArrangedWidget.Widget;
					if (Widget->IsInteractable())
					{
						SpeedMult = StickySlowdown;
						//FVector2D Adjustment = WidgetsAndCursors.Last().Geometry.Position - OldPosition; // example of calculating distance from cursor to widget center
						break;
					}
				}
			}

			switch (Mode)
			{
				case AnalogCursorMode::Accelerated:
				{
					const float DesiredVelocity = AdjVals.Size() * MaxSpeed;
					const float CurrentVelocity = CurrentSpeed.Size();
					CurrentSpeed = AdjVals.GetSafeNormal() * FGenericPlatformMath::Min(UKismetMathLibrary::SelectFloat(CurrentVelocity + (Acceleration * DeltaTime), DesiredVelocity, DesiredVelocity > CurrentVelocity), MaxSpeed);
					break;
				}

				case AnalogCursorMode::Direct:
				{
					CurrentSpeed = AdjVals * MaxSpeed;
					break;
				}
			}
			
			const FVector2D NewPosition = OldPosition + CurrentOffset + (CurrentSpeed.GetSafeNormal() * (CurrentSpeed.Size() * SpeedMult * DeltaTime));

			// save the remaining sub-pixel offset 
			CurrentOffset.X = FGenericPlatformMath::Frac(NewPosition.X);
			CurrentOffset.Y = FGenericPlatformMath::Frac(NewPosition.Y);

			// update the cursor position
			UpdateCursorPosition(SlateApp, SlateUser.ToSharedRef(), NewPosition);
		}
	}
	else
	{
		CurrentSpeed = { 0,0 };
		CurrentOffset = { 0,0 };
	}
}

//void FAdvancedAnalogCursor::UpdateCursorPosition(FSlateApplication& SlateApp, TSharedRef<FSlateUser> SlateUser, const FVector2D& NewPosition, bool bForce)
//{
//	//grab the old position
//	const FVector2D OldPosition = SlateUser->GetCursorPosition();
//
//	//make sure we are actually moving
//	int32 NewIntPosX = NewPosition.X;
//	int32 NewIntPosY = NewPosition.Y;
//	int32 OldIntPosX = OldPosition.X;
//	int32 OldIntPosY = OldPosition.Y;
//	if (bForce || OldIntPosX != NewIntPosX || OldIntPosY != NewIntPosY)
//	{
//		//put the cursor in the correct spot
//		SlateUser->SetCursorPosition(NewIntPosX, NewIntPosY);
//
//		// Since the cursor may have been locked and its location clamped, get the actual new position
//		const FVector2D UpdatedPosition = SlateUser->GetCursorPosition();
//		//create a new mouse event
//		const bool bIsPrimaryUser = FSlateApplication::CursorUserIndex == SlateUser->GetUserIndex();
//		
//		if (SlateApp.HasUserMouseCapture(SlateUser->GetUserIndex()))
//		{
//			if (!IsMouseCaptured)
//			{
//				MouseCapturePosition = OldPosition;
//				IsMouseCaptured = true;
//			}
//		}
//		else
//		{
//			if (IsMouseCaptured)
//			{
//				IsMouseCaptured = false;
//			}
//
//			MouseCapturePosition = OldPosition;
//		}
//
//		FString OldPosString = MouseCapturePosition.ToString();
//		FString NewPosString = UpdatedPosition.ToString();
//		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, OldPosString);
//		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, NewPosString);
//		
//		FPointerEvent MouseEvent(
//			SlateUser->GetUserIndex(),
//			UpdatedPosition,
//			MouseCapturePosition,
//			bIsPrimaryUser ? SlateApp.GetPressedMouseButtons() : TSet<FKey>(),
//			EKeys::Invalid,
//			0,
//			bIsPrimaryUser ? SlateApp.GetModifierKeys() : FModifierKeysState()
//		);
//
//		//process the event
//		SlateApp.ProcessMouseMoveEvent(MouseEvent);
//	}
//}

bool FAdvancedAnalogCursor::HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent)
{
	if (bIsInputAllowed)
	{
		if (IsRelevantInput(InKeyEvent))
		{
			FKey Key = InKeyEvent.GetKey();

			// Check all existing Input Action Keys for processing the corresponding Mouse Button Click
			for (const TPair <FInputActionKey, TEnumAsByte <EMCMouseButton>>& TempInputActionKeyMap : InputActionKeyMap)
			{
				if (Key == TempInputActionKeyMap.Key.Key
					&& InKeyEvent.IsShiftDown() == TempInputActionKeyMap.Key.bShift
					&& InKeyEvent.IsControlDown() == TempInputActionKeyMap.Key.bCtrl
					&& InKeyEvent.IsAltDown() == TempInputActionKeyMap.Key.bAlt
					&& InKeyEvent.IsCommandDown() == TempInputActionKeyMap.Key.bCmd)
				{
					if (!InKeyEvent.IsRepeat())
					{
						if (TSharedPtr<FSlateUser> SlateUser = SlateApp.GetUser(InKeyEvent))
						{
							if (!(TempInputActionKeyMap.Value == EMCMouseButton::MouseLeft || TempInputActionKeyMap.Value == EMCMouseButton::MouseRight || TempInputActionKeyMap.Value == EMCMouseButton::MouseUp || TempInputActionKeyMap.Value == EMCMouseButton::MouseDown))
							{
								const bool bIsPrimaryUser = FSlateApplication::CursorUserIndex == SlateUser->GetUserIndex();
								FPointerEvent MouseEvent(
									SlateUser->GetUserIndex(),
									FSlateApplication::CursorPointerIndex,
									SlateUser->GetCursorPosition(),
									SlateUser->GetPreviousCursorPosition(),
									bIsPrimaryUser ? SlateApp.GetPressedMouseButtons() : TSet<FKey>(),
									ConvertMouseButtonToKey(TempInputActionKeyMap.Value),
									0,
									bIsPrimaryUser ? SlateApp.GetModifierKeys() : FModifierKeysState(InKeyEvent.IsShiftDown(), InKeyEvent.IsShiftDown(), InKeyEvent.IsControlDown(), InKeyEvent.IsControlDown(), InKeyEvent.IsAltDown(), InKeyEvent.IsAltDown(), InKeyEvent.IsCommandDown(), InKeyEvent.IsCommandDown(), InKeyEvent.AreCapsLocked())
								);

								TSharedPtr<FGenericWindow> GenWindow;
								return SlateApp.ProcessMouseButtonDownEvent(GenWindow, MouseEvent);
							}
							else
							{
								switch (TempInputActionKeyMap.Value)
								{
									case EMCMouseButton::MouseLeft:
									{
										CurrentDigitalValue.X = -1.0f;
										return true;
									}
									case EMCMouseButton::MouseRight:
									{
										CurrentDigitalValue.Y = 1.0f;
										return true;
									}
									case EMCMouseButton::MouseUp:
									{
										CurrentDigitalValue.Z = -1.0f;
										return true;
									}
									case EMCMouseButton::MouseDown:
									{
										CurrentDigitalValue.W = 1.0f;
										return true;
									}
								}
							}
						}
					}
					return true;
				}
			}
		}
	}
	return false;
}

bool FAdvancedAnalogCursor::HandleKeyUpEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent)
{
	if (bIsInputAllowed)
	{
		if (IsRelevantInput(InKeyEvent))
		{
			FKey Key = InKeyEvent.GetKey();

			// Check all existing Input Action Keys for processing the corresponding Mouse Button Click
			for (const TPair <FInputActionKey, TEnumAsByte <EMCMouseButton>>& TempInputActionKeyMap : InputActionKeyMap)
			{
				if (Key == TempInputActionKeyMap.Key.Key && !InKeyEvent.IsRepeat()
					&& InKeyEvent.IsShiftDown() == TempInputActionKeyMap.Key.bShift
					&& InKeyEvent.IsControlDown() == TempInputActionKeyMap.Key.bCtrl
					&& InKeyEvent.IsAltDown() == TempInputActionKeyMap.Key.bAlt
					&& InKeyEvent.IsCommandDown() == TempInputActionKeyMap.Key.bCmd)
				{
					if (TSharedPtr<FSlateUser> SlateUser = SlateApp.GetUser(InKeyEvent))
					{
						if (!(TempInputActionKeyMap.Value == EMCMouseButton::MouseLeft || TempInputActionKeyMap.Value == EMCMouseButton::MouseRight || TempInputActionKeyMap.Value == EMCMouseButton::MouseUp || TempInputActionKeyMap.Value == EMCMouseButton::MouseDown))
						{
							const bool bIsPrimaryUser = FSlateApplication::CursorUserIndex == SlateUser->GetUserIndex();

							TSet<FKey> EmptySet;
							FPointerEvent MouseEvent(
								SlateUser->GetUserIndex(),
								FSlateApplication::CursorPointerIndex,
								SlateUser->GetCursorPosition(),
								SlateUser->GetPreviousCursorPosition(),
								bIsPrimaryUser ? SlateApp.GetPressedMouseButtons() : EmptySet,
								ConvertMouseButtonToKey(TempInputActionKeyMap.Value),
								0,
								bIsPrimaryUser ? SlateApp.GetModifierKeys() : FModifierKeysState(InKeyEvent.IsShiftDown(), InKeyEvent.IsShiftDown(), InKeyEvent.IsControlDown(), InKeyEvent.IsControlDown(), InKeyEvent.IsAltDown(), InKeyEvent.IsAltDown(), InKeyEvent.IsCommandDown(), InKeyEvent.IsCommandDown(), InKeyEvent.AreCapsLocked())
							);

							return SlateApp.ProcessMouseButtonUpEvent(MouseEvent);
						}
						else
						{
							switch (TempInputActionKeyMap.Value)
							{
								case EMCMouseButton::MouseLeft:
								{
									CurrentDigitalValue.X = 0.0f;
									return true;
								}
								case EMCMouseButton::MouseRight:
								{
									CurrentDigitalValue.Y = 0.0f;
									return true;
								}
								case EMCMouseButton::MouseUp:
								{
									CurrentDigitalValue.Z = 0.0f;
									return true;
								}
								case EMCMouseButton::MouseDown:
								{
									CurrentDigitalValue.W = 0.0f;
									return true;
								}
							}
						}
					}
					break;
				}
			}
		}
	}
	return false;
}

bool FAdvancedAnalogCursor::HandleAnalogInputEvent(FSlateApplication& SlateApp, const FAnalogInputEvent& InAnalogInputEvent)
{
	if (bIsInputAllowed)
	{
		if (IsRelevantInput(InAnalogInputEvent))
		{
			FKey Key = InAnalogInputEvent.GetKey();
			float AnalogValue = InAnalogInputEvent.GetAnalogValue();

			for (const TPair <FInputAxisKey, TEnumAsByte <EMCMouseAxis>>& TempInputAxisKeyMap : InputAxisKeyMap)
			{
				if (Key == TempInputAxisKeyMap.Key.Key)
				{
					switch (TempInputAxisKeyMap.Value)
					{
					case EMCMouseAxis::MouseXAxis:
					{
						CurrentAnalogValue.X = AnalogValue * TempInputAxisKeyMap.Key.Scale;
						return true;
					}
					case EMCMouseAxis::MouseYAxis:
					{
						CurrentAnalogValue.Y = AnalogValue * TempInputAxisKeyMap.Key.Scale;
						return true;
					}
					case EMCMouseAxis::MouseWheelAxis:
					{
						FAnalogInputEvent TempAnalogInputEvent(EKeys::MouseWheelAxis, InAnalogInputEvent.GetModifierKeys(), InAnalogInputEvent.GetUserIndex(), InAnalogInputEvent.IsRepeat(), InAnalogInputEvent.GetCharacter(), InAnalogInputEvent.GetKeyCode(), InAnalogInputEvent.GetAnalogValue() * TempInputAxisKeyMap.Key.Scale);
						return SlateApp.ProcessAnalogInputEvent(TempAnalogInputEvent);
					}
					}
				}
			}
		}
	}
	return true;
}

bool FAdvancedAnalogCursor::SimulateMouseButtonPressed(class APlayerController* PlayerController, TEnumAsByte <EMCMouseButton> InMouseButton)
{
	if (bIsInputAllowed && PlayerController && FSlateApplication::IsInitialized())
	{
		if (TSharedPtr<FSlateUser> SlateUser = FSlateApplication::Get().GetUser(PlayerController->NetPlayerIndex))
		{
			if (!(InMouseButton == EMCMouseButton::MouseLeft || InMouseButton == EMCMouseButton::MouseRight || InMouseButton == EMCMouseButton::MouseUp || InMouseButton == EMCMouseButton::MouseDown))
			{
				const bool bIsPrimaryUser = FSlateApplication::CursorUserIndex == SlateUser->GetUserIndex();
				FPointerEvent MouseEvent(
					SlateUser->GetUserIndex(),
					FSlateApplication::CursorPointerIndex,
					SlateUser->GetCursorPosition(),
					SlateUser->GetPreviousCursorPosition(),
					bIsPrimaryUser ? FSlateApplication::Get().GetPressedMouseButtons() : TSet<FKey>(),
					ConvertMouseButtonToKey(InMouseButton),
					0,
					bIsPrimaryUser ? FSlateApplication::Get().GetModifierKeys() : FModifierKeysState()
				);

				TSharedPtr<FGenericWindow> GenWindow;
				return FSlateApplication::Get().ProcessMouseButtonDownEvent(GenWindow, MouseEvent);
			}
			else
			{
				switch (InMouseButton)
				{
					case EMCMouseButton::MouseLeft:
					{
						CurrentDigitalValue.X = -1.0f;
						return true;
					}
					case EMCMouseButton::MouseRight:
					{
						CurrentDigitalValue.Y = 1.0f;
						return true;
					}
					case EMCMouseButton::MouseUp:
					{
						CurrentDigitalValue.Z = -1.0f;
						return true;
					}
					case EMCMouseButton::MouseDown:
					{
						CurrentDigitalValue.W = 1.0f;
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool FAdvancedAnalogCursor::SimulateMouseButtonReleased(class APlayerController* PlayerController, TEnumAsByte <EMCMouseButton> InMouseButton)
{
	if (bIsInputAllowed && PlayerController && FSlateApplication::IsInitialized())
	{
		if (TSharedPtr<FSlateUser> SlateUser = FSlateApplication::Get().GetUser(PlayerController->NetPlayerIndex))
		{
			if (!(InMouseButton == EMCMouseButton::MouseLeft || InMouseButton == EMCMouseButton::MouseRight || InMouseButton == EMCMouseButton::MouseUp || InMouseButton == EMCMouseButton::MouseDown))
			{
				const bool bIsPrimaryUser = FSlateApplication::CursorUserIndex == SlateUser->GetUserIndex();

				TSet<FKey> EmptySet;
				FPointerEvent MouseEvent(
					SlateUser->GetUserIndex(),
					FSlateApplication::CursorPointerIndex,
					SlateUser->GetCursorPosition(),
					SlateUser->GetPreviousCursorPosition(),
					bIsPrimaryUser ? FSlateApplication::Get().GetPressedMouseButtons() : EmptySet,
					ConvertMouseButtonToKey(InMouseButton),
					0,
					bIsPrimaryUser ? FSlateApplication::Get().GetModifierKeys() : FModifierKeysState()
				);

				return FSlateApplication::Get().ProcessMouseButtonUpEvent(MouseEvent);
			}
			else
			{
				switch (InMouseButton)
				{
					case EMCMouseButton::MouseLeft:
					{
						CurrentDigitalValue.X = 0.0f;
						return true;
					}
					case EMCMouseButton::MouseRight:
					{
						CurrentDigitalValue.Y = 0.0f;
						return true;
					}
					case EMCMouseButton::MouseUp:
					{
						CurrentDigitalValue.Z = 0.0f;
						return true;
					}
					case EMCMouseButton::MouseDown:
					{
						CurrentDigitalValue.W = 0.0f;
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool FAdvancedAnalogCursor::SimulateMouseAxis(class APlayerController* PlayerController, TEnumAsByte <EMCMouseAxis> InMouseButton, float InAnalogValue, float InScale)
{
	if (bIsInputAllowed && PlayerController && FSlateApplication::IsInitialized())
	{
		switch (InMouseButton)
		{
			case EMCMouseAxis::MouseXAxis:
			{
				CurrentAnalogValue.X = InAnalogValue * InScale;
				return true;
			}
			case EMCMouseAxis::MouseYAxis:
			{
				CurrentAnalogValue.Y = InAnalogValue * InScale;
				return true;
			}
			case EMCMouseAxis::MouseWheelAxis:
			{
				uint32 TempKeyCode;
				uint32 TempCharCode;
				const uint32* TempPtrKeyCode = &TempKeyCode;
				const uint32* TempPtrCharCode = &TempCharCode;
				FInputKeyManager::Get().GetCodesFromKey(EKeys::MouseWheelAxis, TempPtrKeyCode, TempPtrCharCode);
				FAnalogInputEvent TempAnalogInputEvent(EKeys::MouseWheelAxis, {}, PlayerController->NetPlayerIndex, 0 /*IsRepeat has to be handled manually*/, TempCharCode, TempKeyCode, InAnalogValue * InScale);
				return FSlateApplication::Get().ProcessAnalogInputEvent(TempAnalogInputEvent);
			}
		}
	}
	return false;
}

float FAdvancedAnalogCursor::GetAcceleration()
{
	return Acceleration;
}

float FAdvancedAnalogCursor::GetMaxSpeed()
{
	return MaxSpeed;
}

float FAdvancedAnalogCursor::GetStickySlowdown()
{
	return StickySlowdown;
}

float FAdvancedAnalogCursor::GetDeadZone()
{
	return DeadZone;
}

AnalogCursorMode::Type FAdvancedAnalogCursor::GetMode()
{
	return Mode;
}

bool FAdvancedAnalogCursor::GetInputAllowed()
{
	return bIsInputAllowed;
}

void FAdvancedAnalogCursor::SetInputAllowed(bool InInputAllowed)
{
	bIsInputAllowed = InInputAllowed;
}

TMap <FInputActionKey, TEnumAsByte <EMCMouseButton>> FAdvancedAnalogCursor::GetInputActionKeyMap()
{
	return InputActionKeyMap;
}

void FAdvancedAnalogCursor::SetInputActionKeyMap(TMap <FInputActionKey, TEnumAsByte <EMCMouseButton>> InMap)
{
	InputActionKeyMap = InMap;
}

void FAdvancedAnalogCursor::AddInputActionKey(FInputActionKey InKey, TEnumAsByte <EMCMouseButton> InMouseButton)
{
	InputActionKeyMap.Add(InKey, InMouseButton);
}

void FAdvancedAnalogCursor::ClearInputActionKeyMap()
{
	InputActionKeyMap.Empty();
}

bool FAdvancedAnalogCursor::ContainsInputActionKey(FInputActionKey InKey)
{
	return InputActionKeyMap.Contains(InKey);
}

std::pair <TEnumAsByte <EMCMouseButton>, bool> FAdvancedAnalogCursor::FindInputActionKey(FInputActionKey InKey)
{
	TEnumAsByte <EMCMouseButton>* TempFind = InputActionKeyMap.Find(InKey);
	return { *TempFind, TempFind != NULL };
}

TArray <FInputActionKey> FAdvancedAnalogCursor::InputActionKeyMapKeys()
{
	TArray <FInputActionKey> TempKeys;
	InputActionKeyMap.GenerateKeyArray(TempKeys);
	return TempKeys;
}

int FAdvancedAnalogCursor::InputActionKeyMapLength()
{
	return InputActionKeyMap.Num();
}

bool FAdvancedAnalogCursor::RemoveInputActionKey(FInputActionKey InKey)
{
	if (InputActionKeyMap.Contains(InKey))
	{
		InputActionKeyMap.Remove(InKey);
		return true;
	}
	return false;
}

TArray <TEnumAsByte <EMCMouseButton>> FAdvancedAnalogCursor::InputActionKeyMapValues()
{
	TArray <TEnumAsByte <EMCMouseButton>> TempValues;
	InputActionKeyMap.GenerateValueArray(TempValues);
	return TempValues;
}

TMap <FInputAxisKey, TEnumAsByte <EMCMouseAxis>> FAdvancedAnalogCursor::GetInputAxisKeyMap()
{
	return InputAxisKeyMap;
}

void FAdvancedAnalogCursor::SetInputAxisKeyMap(TMap <FInputAxisKey, TEnumAsByte <EMCMouseAxis>> InMap)
{
	InputAxisKeyMap = InMap;
}

void FAdvancedAnalogCursor::AddInputAxisKey(FInputAxisKey InKey, TEnumAsByte <EMCMouseAxis> InMouseAxis)
{
	InputAxisKeyMap.Add(InKey, InMouseAxis);
}

void FAdvancedAnalogCursor::ClearInputAxisKeyMap()
{
	InputAxisKeyMap.Empty();
}

bool FAdvancedAnalogCursor::ContainsInputAxisKey(FInputAxisKey InKey)
{
	return InputAxisKeyMap.Contains(InKey);
}

std::pair <TEnumAsByte <EMCMouseAxis>, bool> FAdvancedAnalogCursor::FindInputAxisKey(FInputAxisKey InKey)
{
	TEnumAsByte <EMCMouseAxis>* TempFind = InputAxisKeyMap.Find(InKey);
	return { *TempFind, TempFind != NULL };
}

TArray <FInputAxisKey> FAdvancedAnalogCursor::InputAxisKeyMapKeys()
{
	TArray <FInputAxisKey> TempKeys;
	InputAxisKeyMap.GenerateKeyArray(TempKeys);
	return TempKeys;
}

int FAdvancedAnalogCursor::InputAxisKeyMapLength()
{
	return InputAxisKeyMap.Num();
}

bool FAdvancedAnalogCursor::RemoveInputAxisKey(FInputAxisKey InKey)
{
	if (InputAxisKeyMap.Contains(InKey))
	{
		InputAxisKeyMap.Remove(InKey);
		return true;
	}
	return false;
}

TArray <TEnumAsByte <EMCMouseAxis>> FAdvancedAnalogCursor::InputAxisKeyMapValues()
{
	TArray <TEnumAsByte <EMCMouseAxis>> TempValues;
	InputAxisKeyMap.GenerateValueArray(TempValues);
	return TempValues;
}

FKey FAdvancedAnalogCursor::ConvertMouseButtonToKey(TEnumAsByte <EMCMouseButton> InMouseButton)
{
	switch (InMouseButton)
	{
	case EMCMouseButton::LeftMouseButton:
		return EKeys::LeftMouseButton;
	case EMCMouseButton::MiddleMouseButton:
		return EKeys::MiddleMouseButton;
	case EMCMouseButton::RightMouseButton:
		return EKeys::RightMouseButton;
	case EMCMouseButton::ThumbMouseButton1:
		return EKeys::ThumbMouseButton;
	case EMCMouseButton::ThumbMouseButton2:
		return EKeys::ThumbMouseButton2;
	case EMCMouseButton::MouseWheelDown:
		return EKeys::MouseScrollDown;
	case EMCMouseButton::MouseWheelUp:
		return EKeys::MouseScrollUp;
	case EMCMouseButton::MouseLeft:
		return EKeys::MouseX;
	case EMCMouseButton::MouseRight:
		return EKeys::MouseX;
	case EMCMouseButton::MouseUp:
		return EKeys::MouseY;
	case EMCMouseButton::MouseDown:
		return EKeys::MouseY;
	}
	return EKeys::Invalid;
}