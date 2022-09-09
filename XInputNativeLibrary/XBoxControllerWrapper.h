#pragma once
#include "XboxController.h"


/*********************************************
* Marshalling Functions for External DDL Calls
**********************************************/

// Wrapper function for marshalling the creation of an Xbox Controller object
extern "C" __declspec(dllexport) XboxController * CreateXboxController(int controllerNumber);

// Wrapper function for marshalling the destory of Xbox Controller object
extern "C" __declspec(dllexport) void DeleteXboxController(XboxController * xBoxController);

// Wrapper function for marshalling the update of controller I/O
extern "C" __declspec(dllexport) void UpdateWrapper(XboxController * xBoxController);

// Wrapper function for marshalling the return of Controller Index
extern "C" __declspec(dllexport) int GetIndexWrapper(XboxController * xBoxController);

// Wrapper function for marshalling the return of Controller Connected status
extern "C" __declspec(dllexport) bool GetConnectedWrapper(XboxController * xBoxController);

// Wrapper function for marshalling the return of Controller Left Joystick Y Value
extern "C" __declspec(dllexport) float GetLeftStick_YWrapper(XboxController * xBoxController);

// Wrapper function for marshalling the return of Controller Left Joystick X Value
extern "C" __declspec(dllexport) float GetLeftStick_XWrapper(XboxController * xBoxController);

// Wrapper function for marshalling the return of Controller Right Joystick Y Value
extern "C" __declspec(dllexport) float GetRightStick_YWrapper(XboxController * xBoxController);

// Wrapper function for marshalling the return of Controller Right Joystick X Value
extern "C" __declspec(dllexport) float GetRightStick_XWrapper(XboxController * xBoxController);

// Wrapper function for marshalling the return of Controller Left Trigger Value
extern "C" __declspec(dllexport) float GetLeftTriggerWrapper(XboxController * xBoxController);

// Wrapper function for marshalling the return of Controller Right Trigger Value
extern "C" __declspec(dllexport) float GetRightTriggerWrapper(XboxController * xBoxController);

// Wrapper function for marshalling the return of Controller Button Input Values
extern "C" __declspec(dllexport) XboxController::XInput_Gamepad GetButtonsWrapper(XboxController * xBoxController);

// Wrapper function for marshalling the return of Controller Battery Values
extern "C" __declspec(dllexport) XboxController::XInput_BatteryInfo GetBatteryWrapper(XboxController * xBoxController);

// Wrapper function for marshalling the return of Controller Capabilites
extern "C" __declspec(dllexport) XboxController::XInput_Capabilities GetCapabilitesWrapper(XboxController * xBoxController);

// Wrapper function for marshalling the set function for Controller Rumble
extern "C" __declspec(dllexport) void SetRumbleWrapper(XboxController* xBoxController, float fLeftMotor, float fRightMotor);