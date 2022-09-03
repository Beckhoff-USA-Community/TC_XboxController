#include "XBoxControllerWrapper.h"


// Wrapper function for marshalling the creation of an XBox Controller object
XBoxController* CreateXboxController(int controllerNumber) {
	return new XBoxController(controllerNumber);
}

// Wrapper function for marshalling the destory of XBox Controller object
void DeleteXboxController(XBoxController* xBoxController) {
	delete xBoxController;
}

// Wrapper function for marshalling the update of controller I/O
void UpdateWrapper(XBoxController* xBoxController) {
	xBoxController->Update();
}

// Wrapper function for marshalling the return of Controller Index
int GetIndexWrapper(XBoxController* xBoxController) {
	return xBoxController->GetIndex();
}

// Wrapper function for marshalling the return of Controller Connected status
bool GetConnectedWrapper(XBoxController* xBoxController) {
	return xBoxController->GetConnected();
}

// Wrapper function for marshalling the return of Controller Left Joystick Y Value
float GetLeftStick_YWrapper(XBoxController* xBoxController) {
	if (xBoxController->GetConnected())
		return xBoxController->GetLeftJoystick_Y();
	return 0.00f;
}

// Wrapper function for marshalling the return of Controller Left Joystick X Value
float GetLeftStick_XWrapper(XBoxController* xBoxController) {
	if (xBoxController->GetConnected())
		return xBoxController->GetLeftJoystick_X();
	return 0.00f;
}

// Wrapper function for marshalling the return of Controller Right Joystick Y Value
float GetRightStick_YWrapper(XBoxController* xBoxController) {
	if (xBoxController->GetConnected())
		return xBoxController->GetRightJoystick_Y();
	return 0.00f;
}

// Wrapper function for marshalling the return of Controller Right Joystick X Value
float GetRightStick_XWrapper(XBoxController* xBoxController) {
	if (xBoxController->GetConnected())
		return xBoxController->GetRightJoystick_X();
	return 0.00f;
}

// Wrapper function for marshalling the return of Controller Left Trigger Value
float GetLeftTriggerWrapper(XBoxController* xBoxController) {
	if (xBoxController->GetConnected())
		return xBoxController->GetLeftTrigger();
	return 0.00f;
}

// Wrapper function for marshalling the return of Controller Right Trigger Value
float GetRightTriggerWrapper(XBoxController* xBoxController) {
	if (xBoxController->GetConnected())
		return xBoxController->GetRightTrigger();
	return 0.00f;
}

// Wrapper function for marshalling the return of Controller Button Input Values
XBoxController::XInput_Gamepad GetButtonsWrapper(XBoxController* xBoxController) {
	if (xBoxController->GetConnected())
		return xBoxController->GetButtons();
	else {
		XBoxController::XInput_Gamepad buttons;
		ZeroMemory(&buttons, sizeof(XBoxController::XInput_Gamepad));
		return buttons;
	}
}

// Wrapper function for marshalling the return of Controller Battery Values
extern "C" __declspec(dllexport) XBoxController::XInput_BatteryInfo GetBatteryWrapper(XBoxController * xBoxController) {
	if (xBoxController->GetConnected())
		return xBoxController->GetBattery();
	else {
		XBoxController::XInput_BatteryInfo battery;
		ZeroMemory(&battery, sizeof(XBoxController::XInput_BatteryInfo));
		return battery;
	}
}

// Wrapper function for marshalling the return of Controller Capabilites
extern "C" __declspec(dllexport) XBoxController::XInput_Capabilities GetCapabilitesWrapper(XBoxController * xBoxController) {
	if (xBoxController->GetConnected())
		return xBoxController->GetCapabilites();
	else {
		XBoxController::XInput_Capabilities capabilities;
		ZeroMemory(&capabilities, sizeof(XBoxController::XInput_Capabilities));
		return capabilities;
	}
}

// Wrapper function for marshalling the set function for Controller Rumble
void SetRumbleWrapper(XBoxController* xBoxController, float fLeftMotor, float fRightMotor) {
	if (xBoxController->GetConnected())
		xBoxController->SetRumble(fLeftMotor, fRightMotor);
}