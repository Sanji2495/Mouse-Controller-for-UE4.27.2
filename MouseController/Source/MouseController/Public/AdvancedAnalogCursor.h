#pragma once
#include "Framework/Application/AnalogCursor.h"
#include "AdvancedAnalogCursor.generated.h"

UENUM(BlueprintType)
enum EMCAnalogCursorMode
{
	DirectMovement		UMETA(DisplayName = "Direct Movement"),
	AcceleratedMovement UMETA(DisplayName = "Accelerated Movement"),
};

UENUM(BlueprintType)
enum EMCMouseButton
{
	LeftMouseButton		UMETA(DisplayName = "Left Mouse Button"),
	MiddleMouseButton	UMETA(DisplayName = "Middle Mouse Button"),
	RightMouseButton	UMETA(DisplayName = "Right Mouse Button"),
	ThumbMouseButton1	UMETA(DisplayName = "Thumb Mouse Button 1"),
	ThumbMouseButton2	UMETA(DisplayName = "Thumb Mouse Button 2"),
	MouseWheelDown		UMETA(DisplayName = "Mouse Wheel Down"),
	MouseWheelUp		UMETA(DisplayName = "Mouse Wheel Up"),
	MouseLeft			UMETA(DisplayName = "Mouse Left"),
	MouseRight			UMETA(DisplayName = "Mouse Right"),
	MouseUp				UMETA(DisplayName = "Mouse Up"),
	MouseDown			UMETA(DisplayName = "Mouse Down"),
};

UENUM(BlueprintType)
enum EMCMouseAxis
{
	MouseXAxis		UMETA(DisplayName = "Mouse X Axis"),
	MouseYAxis		UMETA(DisplayName = "Mouse Y Axis"),
	MouseWheelAxis	UMETA(DisplayName = "Mouse Wheel Axis"),
};

USTRUCT(BlueprintType, Blueprintable)
struct FInputActionKey
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "Key"))
	FKey Key = EKeys::Invalid;
	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "Shift"))
	bool bShift = false;
	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "Ctrl"))
	bool bCtrl = false;
	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "Alt"))
	bool bAlt = false;
	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "Cmd"))
	bool bCmd = false;

	friend bool operator==(const FInputActionKey& KeyA, const FInputActionKey& KeyB) { return KeyA.Key.GetFName() == KeyB.Key.GetFName(); }
	friend bool operator!=(const FInputActionKey& KeyA, const FInputActionKey& KeyB) { return KeyA.Key.GetFName() != KeyB.Key.GetFName(); }
	friend bool operator<(const FInputActionKey& KeyA, const FInputActionKey& KeyB) { return KeyA.Key.GetFName().LexicalLess(KeyB.Key.GetFName()); }
	friend uint32 GetTypeHash(const FInputActionKey& Key) { return GetTypeHash(Key.Key.GetFName()); }
};

USTRUCT(BlueprintType, Blueprintable)
struct FInputAxisKey
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "Key"))
	FKey Key = EKeys::Invalid;
	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "Scale"))
	float Scale = 1.0f;

	friend bool operator==(const FInputAxisKey& KeyA, const FInputAxisKey& KeyB) { return KeyA.Key.GetFName() == KeyB.Key.GetFName(); }
	friend bool operator!=(const FInputAxisKey& KeyA, const FInputAxisKey& KeyB) { return KeyA.Key.GetFName() != KeyB.Key.GetFName(); }
	friend bool operator<(const FInputAxisKey& KeyA, const FInputAxisKey& KeyB) { return KeyA.Key.GetFName().LexicalLess(KeyB.Key.GetFName()); }
	friend uint32 GetTypeHash(const FInputAxisKey& Key) { return GetTypeHash(Key.Key.GetFName()); }
};

class MOUSECONTROLLER_API FAdvancedAnalogCursor : public FAnalogCursor
{

public:

	FAdvancedAnalogCursor()
	{
		Acceleration = 1000.0f;
		MaxSpeed = 1500.0f;
		StickySlowdown = 0.5f;
		DeadZone = 0.25f;
		Mode = AnalogCursorMode::Direct;

		//Variables for MouseCapture
		//IsMouseCaptured = false;
		//MouseCapturePosition = { 0.0f, 0.0f };

		CurrentAnalogValue = { 0.0f ,0.0f };
		CurrentDigitalValue = FVector4({ 0.0f ,0.0f ,0.0f }, 0.0f);

		InputActionKeyMap = {};
		bIsInputAllowed = false;
	}

	virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override;

	//virtual void UpdateCursorPosition(FSlateApplication& SlateApp, TSharedRef<FSlateUser> SlateUser, const FVector2D& NewPosition, bool bForce = false) override;

	virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override;
	virtual bool HandleKeyUpEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override;
	virtual bool HandleAnalogInputEvent(FSlateApplication& SlateApp, const FAnalogInputEvent& InAnalogInputEvent) override;

	bool SimulateMouseButtonPressed(class APlayerController* PlayerController, TEnumAsByte <EMCMouseButton> InMouseButton);
	bool SimulateMouseButtonReleased(class APlayerController* PlayerController, TEnumAsByte <EMCMouseButton> InMouseButton);
	bool SimulateMouseAxis(class APlayerController* PlayerController, TEnumAsByte <EMCMouseAxis> InMouseButton, float InAnalogValue, float InScale);

	float GetAcceleration();
	float GetMaxSpeed();
	float GetStickySlowdown();
	float GetDeadZone();
	AnalogCursorMode::Type GetMode();

	bool GetInputAllowed();
	void SetInputAllowed(bool InInputAllowed);

	TMap <FInputActionKey, TEnumAsByte <EMCMouseButton>> GetInputActionKeyMap();
	void SetInputActionKeyMap(TMap <FInputActionKey, TEnumAsByte <EMCMouseButton>> InMap);

	void AddInputActionKey(FInputActionKey InKey, TEnumAsByte <EMCMouseButton> InMouseButton);
	void ClearInputActionKeyMap();
	bool ContainsInputActionKey(FInputActionKey InKey);
	std::pair <TEnumAsByte <EMCMouseButton>, bool> FindInputActionKey(FInputActionKey InKey);
	TArray <FInputActionKey> InputActionKeyMapKeys();
	int InputActionKeyMapLength();
	bool RemoveInputActionKey(FInputActionKey InKey);
	TArray <TEnumAsByte <EMCMouseButton>> InputActionKeyMapValues();

	TMap <FInputAxisKey, TEnumAsByte <EMCMouseAxis>> GetInputAxisKeyMap();
	void SetInputAxisKeyMap(TMap <FInputAxisKey, TEnumAsByte <EMCMouseAxis>> InMap);

	void AddInputAxisKey(FInputAxisKey InKey, TEnumAsByte <EMCMouseAxis> InMouseAxis);
	void ClearInputAxisKeyMap();
	bool ContainsInputAxisKey(FInputAxisKey InKey);
	std::pair <TEnumAsByte <EMCMouseAxis>, bool> FindInputAxisKey(FInputAxisKey InKey);
	TArray <FInputAxisKey> InputAxisKeyMapKeys();
	int InputAxisKeyMapLength();
	bool RemoveInputAxisKey(FInputAxisKey InKey);
	TArray <TEnumAsByte <EMCMouseAxis>> InputAxisKeyMapValues();

protected:

	//bool IsMouseCaptured;
	//FVector2D MouseCapturePosition;

	FVector2D CurrentAnalogValue;
	FVector4 CurrentDigitalValue;

	FKey ConvertMouseButtonToKey(TEnumAsByte <EMCMouseButton> InMouseButton);

	TMap <FInputActionKey, TEnumAsByte <EMCMouseButton>> InputActionKeyMap;
	TMap <FInputAxisKey, TEnumAsByte <EMCMouseAxis>> InputAxisKeyMap;
	
private:

	bool bIsInputAllowed;
	
};