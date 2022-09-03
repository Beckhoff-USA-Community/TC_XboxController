#pragma once
#include "XBoxController.h"


/*********************************************
* Marshalling Functions for External DDL Calls
**********************************************/

// Wrapper function for marshalling the creation of an XBox Controller object
extern "C" __declspec(dllexport) XBoxController * CreateXboxController(int controllerNumber);

// Wrapper function for marshalling the destory of XBox Controller object
extern "C" __declspec(dllexport) void DeleteXboxController(XBoxController * xBoxController);

// Wrapper function for marshalling the update of controller I/O
extern "C" __declspec(dllexport) void UpdateWrapper(XBoxController * xBoxController);

// Wrapper function for marshalling the return of Controller Index
extern "C" __declspec(dllexport) int GetIndexWrapper(XBoxController * xBoxController);

// Wrapper function for marshalling the return of Controller Connected status
extern "C" __declspec(dllexport) bool GetConnectedWrapper(XBoxController * xBoxController);

// Wrapper function for marshalling the return of Controller Left Joystick Y Value
extern "C" __declspec(dllexport) float GetLeftStick_YWrapper(XBoxController * xBoxController);

// Wrapper function for marshalling the return of Controller Left Joystick X Value
extern "C" __declspec(dllexport) float GetLeftStick_XWrapper(XBoxController * xBoxController);

// Wrapper function for marshalling the return of Controller Right Joystick Y Value
extern "C" __declspec(dllexport) float GetRightStick_YWrapper(XBoxController * xBoxController);

// Wrapper function for marshalling the return of Controller Right Joystick X Value
extern "C" __declspec(dllexport) float GetRightStick_XWrapper(XBoxController * xBoxController);

// Wrapper function for marshalling the return of Controller Left Trigger Value
extern "C" __declspec(dllexport) float GetLeftTriggerWrapper(XBoxController * xBoxController);

// Wrapper function for marshalling the return of Controller Right Trigger Value
extern "C" __declspec(dllexport) float GetRightTriggerWrapper(XBoxController * xBoxController);

// Wrapper function for marshalling the return of Controller Button Input Values
extern "C" __declspec(dllexport) XBoxController::XInput_Gamepad GetButtonsWrapper(XBoxController * xBoxController);

// Wrapper function for marshalling the return of Controller Battery Values
extern "C" __declspec(dllexport) XBoxController::XInput_BatteryInfo GetBatteryWrapper(XBoxController * xBoxController);

// Wrapper function for marshalling the return of Controller Capabilites
extern "C" __declspec(dllexport) XBoxController::XInput_Capabilities GetCapabilitesWrapper(XBoxController * xBoxController);

// Wrapper function for marshalling the set function for Controller Rumble
extern "C" __declspec(dllexport) void SetRumbleWrapper(XBoxController* xBoxController, float fLeftMotor, float fRightMotor);