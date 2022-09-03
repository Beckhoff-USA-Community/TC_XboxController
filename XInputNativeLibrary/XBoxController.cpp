#include "XBoxController.h"

// Link the 'Xinput' library - Important!
#pragma comment(lib, "Xinput.lib")

// Overloaded constructor
XBoxController::XBoxController(int a_iIndex)
{
    // Set gamepad index
    m_iGamepadIndex = a_iIndex - 1;
}

// Update gamepad state
void XBoxController::Update()
{
    m_State = _GetState(); // Obtain current gamepad state
}

// Return gamepad state
XINPUT_STATE XBoxController::_GetState()
{
    // Temporary XINPUT_STATE to return
    XINPUT_STATE GamepadState;

    // Zero memory
    ZeroMemory(&GamepadState, sizeof(XINPUT_STATE));

    // Get the state of the gamepad
    DWORD Result = XInputGetState(m_iGamepadIndex, &GamepadState);

    if (Result == ERROR_SUCCESS)
        // Return the gamepad state
        return GamepadState;
    else {
        // Zero memory
        ZeroMemory(&GamepadState, sizeof(XINPUT_STATE));
        return GamepadState;
    }
}

// Return gamepad index
int XBoxController::GetIndex()
{
    return m_iGamepadIndex;
}

// Return true if the gamepad is connected
bool XBoxController::GetConnected()
{  
    // Get the state
    DWORD Result = XInputGetState(m_iGamepadIndex, &m_State);

    if (Result == ERROR_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Return value of Left Joystick Y-Axis
float XBoxController::GetLeftJoystick_Y() {

    // Obtain value of the stick axis
    short axisValue = m_State.Gamepad.sThumbLY;
    // Check if axis is outside of deadzone
    if (axisValue > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || axisValue < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
    {
        // Return axis value, converted to a float
        return (static_cast<float>(axisValue) / 32768.0f) * 100.0f;
    }
    return 0.00f;
}

// Return value of Left Joystick X-Axis
float XBoxController::GetLeftJoystick_X() {

    // Obtain value of the stick axis
    short axisValue = m_State.Gamepad.sThumbLX;
    // Check if axis is outside of deadzone
    if (axisValue > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || axisValue < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
    {
        // Return axis value, converted to a float
        return (static_cast<float>(axisValue) / 32768.0f) * 100.0f;
    }
    return 0.00f;
}

// Return value of Right Joystick Y-Axis
float XBoxController::GetRightJoystick_Y() {

    // Obtain value of the stick axis
    short axisValue = m_State.Gamepad.sThumbRY;
    // Check if axis is outside of deadzone
    if (axisValue > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || axisValue < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
    {
        // Return axis value, converted to a float
        return (static_cast<float>(axisValue) / 32768.0f) * 100.0f;
    }
    return 0.00f;
}

// Return value of Right Joystick X-Axis
float XBoxController::GetRightJoystick_X() {

    // Obtain value of the stick axis
    short axisValue = m_State.Gamepad.sThumbRX;
    // Check if axis is outside of deadzone
    if (axisValue > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || axisValue < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
    {
        // Return axis value, converted to a float
        return (static_cast<float>(axisValue) / 32768.0f) * 100.0f;
    }
    return 0.00f;
}

// Return value of left trigger
float XBoxController::GetLeftTrigger()
{

    // Obtain value of left trigger
    BYTE Trigger = m_State.Gamepad.bLeftTrigger;

    if (Trigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
        return (Trigger / 255.0f) * 100.0f;

    return 0.0f; // Trigger was not pressed
}

// Return value of right trigger
float XBoxController::GetRightTrigger()
{

    // Obtain value of right trigger
    BYTE Trigger = m_State.Gamepad.bRightTrigger;

    if (Trigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
        return (Trigger / 255.0f) * 100.0f;

    return 0.0f; // Trigger was not pressed
}

// Return the values of the buttons
XBoxController::XInput_Gamepad XBoxController::GetButtons()
{
    // Zero memory
    ZeroMemory(&m_Buttons, sizeof(XInput_Gamepad));
    m_Buttons.A             = (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_A) ? true : false;
    m_Buttons.B             = (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_B) ? true : false;
    m_Buttons.X             = (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_X) ? true : false;
    m_Buttons.Y             = (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_Y) ? true : false;
    m_Buttons.DPad_Up       = (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) ? true : false;
    m_Buttons.DPad_Down     = (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) ? true : false;
    m_Buttons.DPad_Left     = (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) ? true : false;
    m_Buttons.DPad_Right    = (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) ? true : false;
    m_Buttons.L_Shoulder    = (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) ? true : false;
    m_Buttons.R_Shoulder    = (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) ? true : false;
    m_Buttons.L_Thumstick   = (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) ? true : false;
    m_Buttons.R_Thumstick   = (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) ? true : false;
    m_Buttons.Start         = (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_START) ? true : false;
    m_Buttons.Back          = (m_State.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) ? true : false;
    return m_Buttons;
}

// Return the values of the battery
XBoxController::XInput_BatteryInfo XBoxController::GetBattery()
{
    // Temporary XINPUT_STATE to return
    XINPUT_BATTERY_INFORMATION BatteryInfo;

    // Zero memory
    ZeroMemory(&BatteryInfo, sizeof(XINPUT_BATTERY_INFORMATION));

    // Get the state of the gamepad
    DWORD Result = XInputGetBatteryInformation(m_iGamepadIndex, BATTERY_DEVTYPE_GAMEPAD, &BatteryInfo);

    // Zero memory
    ZeroMemory(&m_BatteryInfo, sizeof(XInput_BatteryInfo));

    if (Result == ERROR_SUCCESS) {
        m_BatteryInfo.Type_Disconnected     = (BatteryInfo.BatteryType == BATTERY_TYPE_DISCONNECTED) ? true : false;
        m_BatteryInfo.Type_Wired            = (BatteryInfo.BatteryType == BATTERY_TYPE_WIRED) ? true : false;
        m_BatteryInfo.Type_Alkaline         = (BatteryInfo.BatteryType == BATTERY_TYPE_ALKALINE) ? true : false;
        m_BatteryInfo.Type_NIMH             = (BatteryInfo.BatteryType == BATTERY_TYPE_NIMH) ? true : false;
        m_BatteryInfo.Type_Unknown          = (BatteryInfo.BatteryType == BATTERY_TYPE_UNKNOWN) ? true : false;
        m_BatteryInfo.Level_Empty           = (BatteryInfo.BatteryLevel == BATTERY_LEVEL_EMPTY) ? true : false;
        m_BatteryInfo.Level_Low             = (BatteryInfo.BatteryLevel == BATTERY_LEVEL_LOW) ? true : false;
        m_BatteryInfo.Level_Medium          = (BatteryInfo.BatteryLevel == BATTERY_LEVEL_MEDIUM) ? true : false;
        m_BatteryInfo.Level_Full            = (BatteryInfo.BatteryLevel == BATTERY_LEVEL_FULL) ? true : false;
    }
    return m_BatteryInfo;
}

// Return the values of the capabilites
XBoxController::XInput_Capabilities XBoxController::GetCapabilites()
{
    // Temporary XINPUT_STATE to return
    XINPUT_CAPABILITIES Capabilites;

    // Zero memory
    ZeroMemory(&Capabilites, sizeof(XINPUT_CAPABILITIES));

    // Get the state of the gamepad
    DWORD Result = XInputGetCapabilities(m_iGamepadIndex, XINPUT_FLAG_GAMEPAD, &Capabilites);

    // Zero memory
    ZeroMemory(&m_Capabilites, sizeof(XInput_Capabilities));

    if (Result == ERROR_SUCCESS) {
        m_Capabilites.DevType_Gamepad        = (Capabilites.Type == XINPUT_DEVTYPE_GAMEPAD) ? true : false;
        m_Capabilites.VoiceSupported         = (Capabilites.Flags == XINPUT_CAPS_VOICE_SUPPORTED) ? true : false;
        m_Capabilites.ForceFeedbackSupported = (Capabilites.Flags == XINPUT_CAPS_FFB_SUPPORTED) ? true : false;
        m_Capabilites.Wireless               = (Capabilites.Flags == XINPUT_CAPS_WIRELESS) ? true : false;
        m_Capabilites.PluginModulesSupported = (Capabilites.Flags == XINPUT_CAPS_PMD_SUPPORTED) ? true : false;
        m_Capabilites.NoNavigation           = (Capabilites.Flags == XINPUT_CAPS_NO_NAVIGATION) ? true : false;
    }
    return m_Capabilites;
}


// Vibrate the gamepad (values of 0.0f to 100.0f only)
void XBoxController::SetRumble(float fLeftMotor, float fRightMotor)
{
    // Vibration state
    XINPUT_VIBRATION VibrationState;

    // Zero memory
    ZeroMemory(&VibrationState, sizeof(XINPUT_VIBRATION));

    // Calculate vibration values
    int iLeftMotor = int((fLeftMotor/100.0f) * 65535.0f);
    int iRightMotor = int((fRightMotor/100.0f) * 65535.0f);

    // Set vibration values
    VibrationState.wLeftMotorSpeed = iLeftMotor;
    VibrationState.wRightMotorSpeed = iRightMotor;

    // Set the vibration state
    XInputSetState(m_iGamepadIndex, &VibrationState);
}

