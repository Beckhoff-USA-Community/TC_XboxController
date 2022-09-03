#ifndef XBOXCONTROLLER_H
#define XBOXCONTROLLER_H

#pragma once

// We need the Windows Header and the XInput Header
#include <Windows.h>
#include <Xinput.h>

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers

#if(_WIN32_WINNT >= _WIN32_WINNT_WIN10)
#pragma deprecated(XInputEnable)
#endif


class XBoxController
{
public:
    // Function prototypes
    //---------------------//

    // Structs
    // 
    // Button Structure from XInput
    struct XInput_Gamepad
    {
        bool A;
        bool B;
        bool X;
        bool Y;
        bool DPad_Up;
        bool DPad_Down;
        bool DPad_Left;
        bool DPad_Right;
        bool L_Shoulder;
        bool R_Shoulder;
        bool L_Thumstick;
        bool R_Thumstick;
        bool Start;
        bool Back;
    };

    // Battery Info Structure
    struct XInput_BatteryInfo
    {

        bool Type_Disconnected;
        bool Type_Wired;
        bool Type_Alkaline;
        bool Type_NIMH;
        bool Type_Unknown;
        bool Level_Empty;
        bool Level_Low;
        bool Level_Medium;
        bool Level_Full;
    };

    // Capabilities Info Structure
    struct XInput_Capabilities
    {
        // Device is game controller
        bool DevType_Gamepad;
        // Device is an integrated voice device
        bool VoiceSupported;
        // Rumble is supported
        bool ForceFeedbackSupported;
        // Device is wireless
        bool Wireless;
        // Device supports plugin modules
        bool PluginModulesSupported;
        // Device lacks navigation buttons (Start, Back, DPad)
        bool NoNavigation;
    };


    // Constructors
    XBoxController(int a_iIndex);

    // Utility functions
    void Update();               // Updates the inputs for the gamepad
    int GetIndex();              // Return gamepad index
    bool GetConnected();         // Return true if gamepad is connected

    // Inputs
    float GetLeftJoystick_Y();    //Return Left Joystick Y Value
    float GetLeftJoystick_X();    //Return Left Joystick X Value
    float GetRightJoystick_Y();   //Return Right Joystick Y Value
    float GetRightJoystick_X();   //Return Right Joystick X Value
    float GetLeftTrigger();       //Return Left Trigger Value
    float GetRightTrigger();      //Return Right Trigger Value
    XInput_Gamepad GetButtons();           //Return the Buttons   
    XInput_BatteryInfo GetBattery();       //Return the Battery Info   
    XInput_Capabilities GetCapabilites();  //Returns the controllers capabilites

    // Outputs
    void SetRumble(float fLeftMotor, float fRightMotor);   //Sets the controller rumble

private:
    // Member variables
    //---------------------//

    XINPUT_STATE m_State; // Current gamepad state
    int m_iGamepadIndex;  // Gamepad index (eg. 1,2,3,4)
    XInput_Gamepad m_Buttons;         // Button Status
    XInput_BatteryInfo m_BatteryInfo; // Battery Info
    XInput_Capabilities m_Capabilites;// Capabilites of device

    // Utility functions
    XINPUT_STATE _GetState();
};
#endif // XBOXCONTROLLER_H