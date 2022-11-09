#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AdvancedAnalogCursorManager.h"
#include "MouseController.generated.h"

UCLASS()
class MOUSECONTROLLER_API UMouseController : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Mouse Controller", meta = (DisplayName = "Create Mouse Controller"))
	static void CreateMouseController(class APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, Category = "Mouse Controller", meta = (DisplayName = "Enable Mouse Controller"))
	static void EnableMouseController(class APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, Category = "Mouse Controller", meta = (DisplayName = "Disable Mouse Controller"))
	static void DisableMouseController(class APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, Category = "Mouse Controller", meta = (DisplayName = "Set Navigation"))
	static void SetNavigation(bool bNewTabNavigation, bool bNewKeyNavigation, bool bNewAnalogNavigation);
	
	UFUNCTION(BlueprintPure, Category = "Mouse Controller", meta = (DisplayName = "Is Mouse Controller Valid"))
	static bool IsMouseControllerValid(class APlayerController* PlayerController);

	UFUNCTION(BlueprintPure, Category = "Mouse Controller", meta = (DisplayName = "Is Mouse Controller Enabled"))
	static bool IsMouseControllerEnabled(class APlayerController* PlayerController);

	UFUNCTION(BlueprintPure, Category = "Mouse Controller", meta = (DisplayName = "Simulate Mouse Button Pressed"))
	static bool SimulateMouseButtonPressed(class APlayerController* PlayerController, TEnumAsByte <EMCMouseButton> InMouseButton);

	UFUNCTION(BlueprintPure, Category = "Mouse Controller", meta = (DisplayName = "Simulate Mouse Button Released"))
	static bool SimulateMouseButtonReleased(class APlayerController* PlayerController, TEnumAsByte <EMCMouseButton> InMouseButton);

	UFUNCTION(BlueprintPure, Category = "Mouse Controller", meta = (DisplayName = "Simulate Mouse Axis"))
	static bool SimulateMouseAxis(class APlayerController* PlayerController, TEnumAsByte <EMCMouseAxis> InMouseButton, float InAnalogValue, float InScale = 1.0f);

	UFUNCTION(BlueprintPure, Category = "Mouse Controller", meta = (DisplayName = "Get Acceleration"))
	static float GetAcceleration(class APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, Category = "Mouse Controller", meta = (DisplayName = "Set Acceleration"))
	static void SetAcceleration(class APlayerController* PlayerController, float NewAcceleration = 1000.0f);

	UFUNCTION(BlueprintPure, Category = "Mouse Controller", meta = (DisplayName = "Get Max Speed"))
	static float GetMaxSpeed(class APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, Category = "Mouse Controller", meta = (DisplayName = "Set Max Speed"))
	static void SetMaxSpeed(class APlayerController* PlayerController, float NewMaxSpeed = 1500.0f);

	UFUNCTION(BlueprintPure, Category = "Mouse Controller", meta = (DisplayName = "Get Sticky Slowdown"))
	static float GetStickySlowdown(class APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, Category = "Mouse Controller", meta = (DisplayName = "Set Sticky Slowdown"))
	static void SetStickySlowdown(class APlayerController* PlayerController, float NewStickySlowdown = 0.5f);

	UFUNCTION(BlueprintPure, Category = "Mouse Controller", meta = (DisplayName = "Get Dead Zone"))
	static float GetDeadZone(class APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, Category = "Mouse Controller", meta = (DisplayName = "Set Dead Zone"))
	static void SetDeadZone(class APlayerController* PlayerController, float NewDeadZone = 0.25f);

	UFUNCTION(BlueprintPure, Category = "Mouse Controller", meta = (DisplayName = "Get Mode"))
	static TEnumAsByte <EMCAnalogCursorMode> GetMode(class APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, Category = "Mouse Controller", meta = (DisplayName = "Set Mode"))
	static void SetMode(class APlayerController* PlayerController, TEnumAsByte <EMCAnalogCursorMode> NewMode = EMCAnalogCursorMode::DirectMovement);

	UFUNCTION(BlueprintPure, Category = "Mouse Controller|Action Mapping", meta = (CompactNodeTitle = "Get Input Action Key Map"))
	static TMap <FInputActionKey, TEnumAsByte <EMCMouseButton>> GetInputActionKeyMap(class APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, Category = "Mouse Controller|Action Mapping", meta = (CompactNodeTitle = "Set Input Action Key Map"))
	static void SetInputActionKeyMap(class APlayerController* PlayerController, TMap <FInputActionKey, TEnumAsByte <EMCMouseButton>> InMap);

	UFUNCTION(BlueprintCallable, Category = "Mouse Controller|Action Mapping", meta = (CompactNodeTitle = "Add Input Action Key"))
	static void AddInputActionKey(class APlayerController* PlayerController, FInputActionKey InKey, TEnumAsByte <EMCMouseButton> InMouseButton);

	UFUNCTION(BlueprintCallable, Category = "Mouse Controller|Action Mapping", meta = (CompactNodeTitle = "Clear Input Action Key Map"))
	static void ClearInputActionKeyMap(class APlayerController* PlayerController);

	UFUNCTION(BlueprintPure, Category = "Mouse Controller|Action Mapping", meta = (CompactNodeTitle = "Contains Input Action Key"))
	static bool ContainsInputActionKey(class APlayerController* PlayerController, FInputActionKey InKey);

	UFUNCTION(BlueprintPure, Category = "Mouse Controller|Action Mapping", meta = (CompactNodeTitle = "Find Input Action Key"))
	static void FindInputActionKey(class APlayerController* PlayerController, FInputActionKey InKey, TEnumAsByte <EMCMouseButton>& OutMouseButton, bool& OutReturn);

	UFUNCTION(BlueprintCallable, Category = "Mouse Controller|Action Mapping", meta = (CompactNodeTitle = "Input Action Key Map Keys"))
	static TArray <FInputActionKey> InputActionKeyMapKeys(class APlayerController* PlayerController);

	UFUNCTION(BlueprintPure, Category = "Mouse Controller|Action Mapping", meta = (CompactNodeTitle = "Input Action Key Map Length"))
	static int InputActionKeyMapLength(class APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, Category = "Mouse Controller|Action Mapping", meta = (CompactNodeTitle = "Remove Input Action Key"))
	static bool RemoveInputActionKey(class APlayerController* PlayerController, FInputActionKey InKey);

	UFUNCTION(BlueprintCallable, Category = "Mouse Controller|Action Mapping", meta = (CompactNodeTitle = "Input Action Key Map Values"))
	static TArray <TEnumAsByte <EMCMouseButton>> InputActionKeyMapValues(class APlayerController* PlayerController);

	UFUNCTION(BlueprintPure, Category = "Mouse Controller|Axis Mapping", meta = (CompactNodeTitle = "Get Input Axis Key Map"))
	static TMap <FInputAxisKey, TEnumAsByte <EMCMouseAxis>> GetInputAxisKeyMap(class APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, Category = "Mouse Controller|Axis Mapping", meta = (CompactNodeTitle = "Set Input Axis Key Map"))
	static void SetInputAxisKeyMap(class APlayerController* PlayerController, TMap <FInputAxisKey, TEnumAsByte <EMCMouseAxis>> InMap);

	UFUNCTION(BlueprintCallable, Category = "Mouse Controller|Axis Mapping", meta = (CompactNodeTitle = "Add Input Axis Key"))
	static void AddInputAxisKey(class APlayerController* PlayerController, FInputAxisKey InKey, TEnumAsByte <EMCMouseAxis> InMouseAxis);

	UFUNCTION(BlueprintCallable, Category = "Mouse Controller|Axis Mapping", meta = (CompactNodeTitle = "Clear Input Axis Key Map"))
	static void ClearInputAxisKeyMap(class APlayerController* PlayerController);

	UFUNCTION(BlueprintPure, Category = "Mouse Controller|Axis Mapping", meta = (CompactNodeTitle = "Contains Input Axis Key"))
	static bool ContainsInputAxisKey(class APlayerController* PlayerController, FInputAxisKey InKey);

	UFUNCTION(BlueprintPure, Category = "Mouse Controller|Axis Mapping", meta = (CompactNodeTitle = "Find Input Axis Key"))
	static void FindInputAxisKey(class APlayerController* PlayerController, FInputAxisKey InKey, TEnumAsByte <EMCMouseAxis>& OutMouseAxis, bool& OutReturn);

	UFUNCTION(BlueprintCallable, Category = "Mouse Controller|Axis Mapping", meta = (CompactNodeTitle = "Input Axis Key Map Keys"))
	static TArray <FInputAxisKey> InputAxisKeyMapKeys(class APlayerController* PlayerController);

	UFUNCTION(BlueprintPure, Category = "Mouse Controller|Axis Mapping", meta = (CompactNodeTitle = "Input Axis Key Map Length"))
	static int InputAxisKeyMapLength(class APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, Category = "Mouse Controller|Axis Mapping", meta = (CompactNodeTitle = "Remove Input Axis Key"))
	static bool RemoveInputAxisKey(class APlayerController* PlayerController, FInputAxisKey InKey);

	UFUNCTION(BlueprintCallable, Category = "Mouse Controller|Axis Mapping", meta = (CompactNodeTitle = "Input Axis Key Map Values"))
	static TArray <TEnumAsByte <EMCMouseAxis>> InputAxisKeyMapValues(class APlayerController* PlayerController);
};