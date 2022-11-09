#pragma once
#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "AdvancedAnalogCursor.h"
#include "AdvancedAnalogCursorManager.generated.h"

UCLASS()
class MOUSECONTROLLER_API UAdvancedAnalogCursorManager : public ULocalPlayerSubsystem
{

	GENERATED_BODY()

public:

	virtual void Deinitialize() override;

	UFUNCTION()
	void CreateAdvancedAnalogCursor();

	UFUNCTION()
	void RegisterAdvancedAnalogCursor();
	
	UFUNCTION()
	void UnregisterAdvancedAnalogCursor();
	
	UFUNCTION()
	bool IsAdvancedAnalogCursorValid() const;
	
	UFUNCTION()
	bool ContainsAdvancedAnalogCursorInputProcessor() const;

	UFUNCTION()
	bool SimulateMouseButtonPressed(class APlayerController* PlayerController, TEnumAsByte <EMCMouseButton> InMouseButton);
	
	UFUNCTION()
	bool SimulateMouseButtonReleased(class APlayerController* PlayerController, TEnumAsByte <EMCMouseButton> InMouseButton);
	
	UFUNCTION()
	bool SimulateMouseAxis(class APlayerController* PlayerController, TEnumAsByte <EMCMouseAxis> InMouseButton, float InAnalogValue, float InScale);

	UFUNCTION()
	float GetAcceleration();
	
	UFUNCTION()
	void SetAcceleration(float NewAcceleration);

	UFUNCTION()
	float GetMaxSpeed();
	
	UFUNCTION()
	void SetMaxSpeed(float NewMaxSpeed);

	UFUNCTION()
	float GetStickySlowdown();
	
	UFUNCTION()
	void SetStickySlowdown(float NewStickySlowdown);

	UFUNCTION()
	float GetDeadZone();
	
	UFUNCTION()
	void SetDeadZone(float NewDeadZone);

	UFUNCTION()
	bool GetInputAllowed();

	UFUNCTION()
	void SetInputAllowed(bool InInputAllowed);

	UFUNCTION()
	TEnumAsByte <EMCAnalogCursorMode> GetMode();
	
	UFUNCTION()
	void SetMode(TEnumAsByte <EMCAnalogCursorMode> NewMode);

	UFUNCTION()
	TMap <FInputActionKey, TEnumAsByte <EMCMouseButton>> GetInputActionKeyMap();
	
	UFUNCTION()
	void SetInputActionKeyMap(TMap <FInputActionKey, TEnumAsByte <EMCMouseButton>> InMap);

	UFUNCTION()
	void AddInputActionKey(FInputActionKey InKey, TEnumAsByte <EMCMouseButton> InMouseButton);
	
	UFUNCTION()
	void ClearInputActionKeyMap();
	
	UFUNCTION()
	bool ContainsInputActionKey(FInputActionKey InKey);
	
	UFUNCTION()
	void FindInputActionKey(FInputActionKey InKey, TEnumAsByte <EMCMouseButton>& OutMouseButton, bool& OutReturn);
	
	UFUNCTION()
	TArray <FInputActionKey> InputActionKeyMapKeys();
	
	UFUNCTION()
	int InputActionKeyMapLength();
	
	UFUNCTION()
	bool RemoveInputActionKey(FInputActionKey InKey);
	
	UFUNCTION()
	TArray <TEnumAsByte <EMCMouseButton>> InputActionKeyMapValues();

	UFUNCTION()
	TMap <FInputAxisKey, TEnumAsByte <EMCMouseAxis>> GetInputAxisKeyMap();

	UFUNCTION()
	void SetInputAxisKeyMap(TMap <FInputAxisKey, TEnumAsByte <EMCMouseAxis>> InMap);

	UFUNCTION()
	void AddInputAxisKey(FInputAxisKey InKey, TEnumAsByte <EMCMouseAxis> InMouseAxis);

	UFUNCTION()
	void ClearInputAxisKeyMap();

	UFUNCTION()
	bool ContainsInputAxisKey(FInputAxisKey InKey);

	UFUNCTION()
	void FindInputAxisKey(FInputAxisKey InKey, TEnumAsByte <EMCMouseAxis>& OutMouseAxis, bool& OutReturn);

	UFUNCTION()
	TArray <FInputAxisKey> InputAxisKeyMapKeys();

	UFUNCTION()
	int InputAxisKeyMapLength();

	UFUNCTION()
	bool RemoveInputAxisKey(FInputAxisKey InKey);

	UFUNCTION()
	TArray <TEnumAsByte <EMCMouseAxis>> InputAxisKeyMapValues();

protected:

	TEnumAsByte <EMCAnalogCursorMode> ConvertAnalogCursorModeToEMCAnalogCursorMode(AnalogCursorMode::Type Mode);
	AnalogCursorMode::Type ConvertEMCAnalogCursorModeToAnalogCursorMode(TEnumAsByte <EMCAnalogCursorMode> Mode);

private:

	TSharedPtr <FAdvancedAnalogCursor> AdvancedAnalogCursor;

};
