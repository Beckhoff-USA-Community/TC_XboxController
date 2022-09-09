#include "XboxControllerWrapper.h"


// Wrapper function for marshalling the creation of an Xbox Controller object
XboxController* CreateXboxController(int controllerNumber) {
	return new XboxController(controllerNumber);
}

// Wrapper function for marshalling the destory of Xbox Controller object
void DeleteXboxController(XboxController* xBoxController) {
	delete xBoxController;
}

// Wrapper function for marshalling the update of controller I/O
void UpdateWrapper(XboxController* xBoxController) {
	xBoxController->Update();
}

// Wrapper function for marshalling the return of Controller Index
int GetIndexWrapper(XboxController* xBoxController) {
	return xBoxController->GetIndex();
}

// Wrapper function for marshalling the return of Controller Connected status
bool GetConnectedWrapper(XboxController* xBoxController) {
	return xBoxController->GetConnected();
}

// Wrapper function for marshalling the return of Controller Left Joystick Y Value
float GetLeftStick_YWrapper(XboxController* xBoxController) {
	if (xBoxController->GetConnected())
		return xBoxController->GetLeftJoystick_Y();
	return 0.00f;
}

// Wrapper function for marshalling the return of Controller Left Joystick X Value
float GetLeftStick_XWrapper(XboxController* xBoxController) {
	if (xBoxController->GetConnected())
		return xBoxController->GetLeftJoystick_X();
	return 0.00f;
}

// Wrapper function for marshalling the return of Controller Right Joystick Y Value
float GetRightStick_YWrapper(XboxController* xBoxController) {
	if (xBoxController->GetConnected())
		return xBoxController->GetRightJoystick_Y();
	return 0.00f;
}

// Wrapper function for marshalling the return of Controller Right Joystick X Value
float GetRightStick_XWrapper(XboxController* xBoxController) {
	if (xBoxController->GetConnected())
		return xBoxController->GetRightJoystick_X();
	return 0.00f;
}

// Wrapper function for marshalling the return of Controller Left Trigger Value
float GetLeftTriggerWrapper(XboxController* xBoxController) {
	if (xBoxController->GetConnected())
		return xBoxController->GetLeftTrigger();
	return 0.00f;
}

// Wrapper function for marshalling the return of Controller Right Trigger Value
float GetRightTriggerWrapper(XboxController* xBoxController) {
	if (xBoxController->GetConnected())
		return xBoxController->GetRightTrigger();
	return 0.00f;
}

// Wrapper function for marshalling the return of Controller Button Input Values
XboxController::XInput_Gamepad GetButtonsWrapper(XboxController* xBoxController) {
	if (xBoxController->GetConnected())
		return xBoxController->GetButtons();
	else {
		XboxController::XInput_Gamepad buttons;
		ZeroMemory(&buttons, sizeof(XboxController::XInput_Gamepad));
		return buttons;
	}
}

// Wrapper function for marshalling the return of Controller Battery Values
extern "C" __declspec(dllexport) XboxController::XInput_BatteryInfo GetBatteryWrapper(XboxController * xBoxController) {
	if (xBoxController->GetConnected())
		return xBoxController->GetBattery();
	else {
		XboxController::XInput_BatteryInfo battery;
		ZeroMemory(&battery, sizeof(XboxController::XInput_BatteryInfo));
		return battery;
	}
}

// Wrapper function for marshalling the return of Controller Capabilites
extern "C" __declspec(dllexport) XboxController::XInput_Capabilities GetCapabilitesWrapper(XboxController * xBoxController) {
	if (xBoxController->GetConnected())
		return xBoxController->GetCapabilites();
	else {
		XboxController::XInput_Capabilities capabilities;
		ZeroMemory(&capabilities, sizeof(XboxController::XInput_Capabilities));
		return capabilities;
	}
}

// Wrapper function for marshalling the set function for Controller Rumble
void SetRumbleWrapper(XboxController* xBoxController, float fLeftMotor, float fRightMotor) {
	if (xBoxController->GetConnected())
		xBoxController->SetRumble(fLeftMotor, fRightMotor);
}