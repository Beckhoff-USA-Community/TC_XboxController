using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace TwinCAT_Xbox_Controller_Service
{
    internal class XboxController
    {
        // Button Structure from XInput
        [StructLayout(LayoutKind.Sequential)]
        public struct XInput_Gamepad
        {
            [MarshalAs(UnmanagedType.I1)]
            public bool A;
            [MarshalAs(UnmanagedType.I1)]
            public bool B;
            [MarshalAs(UnmanagedType.I1)]
            public bool X;
            [MarshalAs(UnmanagedType.I1)]
            public bool Y;
            [MarshalAs(UnmanagedType.I1)]
            public bool DPad_Up;
            [MarshalAs(UnmanagedType.I1)]
            public bool DPad_Down;
            [MarshalAs(UnmanagedType.I1)]
            public bool DPad_Left;
            [MarshalAs(UnmanagedType.I1)]
            public bool DPad_Right;
            [MarshalAs(UnmanagedType.I1)]
            public bool L_Shoulder;
            [MarshalAs(UnmanagedType.I1)]
            public bool R_Shoulder;
            [MarshalAs(UnmanagedType.I1)]
            public bool L_Thumstick;
            [MarshalAs(UnmanagedType.I1)]
            public bool R_Thumstick;
            [MarshalAs(UnmanagedType.I1)]
            public bool Start;
            [MarshalAs(UnmanagedType.I1)]
            public bool Back;
        };

        // Battery Info Structure from XInput
        // Charge value is only valid for wireless devices with a known battery type.
        [StructLayout(LayoutKind.Sequential)]
        public struct XInput_BatteryInfo
        {
            [MarshalAs(UnmanagedType.I1)]
            public bool Type_Disconnected;
            [MarshalAs(UnmanagedType.I1)]
            public bool Type_Wired;
            [MarshalAs(UnmanagedType.I1)]
            public bool Type_Alkaline;
            [MarshalAs(UnmanagedType.I1)]
            public bool Type_NIMH;
            [MarshalAs(UnmanagedType.I1)]
            public bool Type_Unknown;
            [MarshalAs(UnmanagedType.I1)]
            public bool Level_Empty;
            [MarshalAs(UnmanagedType.I1)]
            public bool Level_Low;
            [MarshalAs(UnmanagedType.I1)]
            public bool Level_Medium;
            [MarshalAs(UnmanagedType.I1)]
            public bool Level_Full;
        };

        // Capabilities Info Structure from XInput
        // These have been implemented per the Microsoft spec, but do not seem to function with Xbox 360 or Xbox One Controllers.
        // Only the Gamepad Device Type status seems to report properly
        [StructLayout(LayoutKind.Sequential)]
        public struct XInput_Capabilities
        {
            // Device is game controller
            [MarshalAs(UnmanagedType.I1)]
            public bool DevType_Gamepad;
            // Device is an integrated voice device
            [MarshalAs(UnmanagedType.I1)]
            public bool VoiceSupported;
            // Rumble is supported
            [MarshalAs(UnmanagedType.I1)]
            public bool ForceFeedbackSupported;
            // Device is wireless
            [MarshalAs(UnmanagedType.I1)]
            public bool Wireless;
            // Device supports plugin modules
            [MarshalAs(UnmanagedType.I1)]
            public bool PluginModulesSupported;
            // Device lacks navigation buttons (Start, Back, DPad)
            [MarshalAs(UnmanagedType.I1)]
            public bool NoNavigation;
        };

        // DLL call for the creation of an Xbox Controller object
        [DllImport("XInputNativeLibrary.dll")]
        private static extern IntPtr CreateXboxController(int playerNumber);

        // DLL call for the destory of Xbox Controller object
        [DllImport("XInputNativeLibrary.dll")]
        private static extern void DeleteXboxController(IntPtr xBoxControllerPointer);

        // DLL call for the update of controller I/O
        [DllImport("XInputNativeLibrary.dll")]
        private static extern void UpdateWrapper(IntPtr xBoxControllerPointer);

        // DLL call for the return of Controller Index
        [DllImport("XInputNativeLibrary.dll")]
        private static extern int GetIndexWrapper(IntPtr xBoxControllerPointer);

        // DLL call for the return of Controller Connected status
        [DllImport("XInputNativeLibrary.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        private static extern bool GetConnectedWrapper(IntPtr xBoxControllerPointer);

        // DLL call for the return of Controller Left Joystick Y Value
        [DllImport("XInputNativeLibrary.dll")]
        private static extern float GetLeftStick_YWrapper(IntPtr xBoxControllerPointer);

        // DLL call for the return of Controller Left Joystick X Value
        [DllImport("XInputNativeLibrary.dll")]
        private static extern float GetLeftStick_XWrapper(IntPtr xBoxControllerPointer);

        // DLL call for the return of Controller Right Joystick Y Value
        [DllImport("XInputNativeLibrary.dll")]
        private static extern float GetRightStick_YWrapper(IntPtr xBoxControllerPointer);

        // DLL call for the return of Controller Right Joystick X Value
        [DllImport("XInputNativeLibrary.dll")]
        private static extern float GetRightStick_XWrapper(IntPtr xBoxControllerPointer);

        // DLL call for the return of Controller Left Trigger Value
        [DllImport("XInputNativeLibrary.dll")]
        private static extern float GetLeftTriggerWrapper(IntPtr xBoxControllerPointer);

        // DLL call for the return of Controller Right Trigger Value
        [DllImport("XInputNativeLibrary.dll")]
        private static extern float GetRightTriggerWrapper(IntPtr xBoxControllerPointer);

        // DLL call for the return of Controller Button Input Values
        [DllImport("XInputNativeLibrary.dll")]
        private static extern XInput_Gamepad GetButtonsWrapper(IntPtr xBoxControllerPointer);

        // DLL call for the return of Controller Battery Values
        [DllImport("XInputNativeLibrary.dll")]
        private static extern XInput_BatteryInfo GetBatteryWrapper(IntPtr xBoxControllerPointer);

        // DLL call for the return of Controller Capabilites
        [DllImport("XInputNativeLibrary.dll")]
        private static extern XInput_Capabilities GetCapabilitesWrapper(IntPtr xBoxControllerPointer);

        // DLL call for the set function for Controller Rumble
        [DllImport("XInputNativeLibrary.dll")]
        private static extern void SetRumbleWrapper(IntPtr xBoxControllerPointer, float fLeftMotor, float fRightMotor);

        // Internal pointer to the Xbox Controller object
        private readonly IntPtr _xBoxControllerPointer;


        // Constructor
        public XboxController(int playerNumber)
        {
            _xBoxControllerPointer = CreateXboxController(playerNumber);
        }
        // Destructor
        ~XboxController()
        {
            DeleteXboxController(_xBoxControllerPointer);
        }
        // Updates the controller I/O
        public void Update()
        {
            UpdateWrapper(_xBoxControllerPointer);
        }
        // Returns the controller number
        public int ControllerNumber
        {
            get
            {
                // Add 1 because the XInput Index starts at 0
                return GetIndexWrapper(_xBoxControllerPointer) + 1;
            }
        }
        // Returns the connected status
        public bool Connected
        {
            get
            {
                return GetConnectedWrapper(_xBoxControllerPointer);
            }
        }
        // Returns the left sticks Y value
        public float LeftStick_Y
        {
            get
            {
                return GetLeftStick_YWrapper(_xBoxControllerPointer);
            }
        }
        // Returns the left sticks X value
        public float LeftStick_X
        {
            get
            {
                return GetLeftStick_XWrapper(_xBoxControllerPointer);
            }
        }
        // Returns the right sticks Y value
        public float RightStick_Y
        {
            get
            {
                return GetRightStick_YWrapper(_xBoxControllerPointer);
            }
        }
        // Returns the right sticks X value
        public float RightStick_X
        {
            get
            {
                return GetRightStick_XWrapper(_xBoxControllerPointer);
            }
        }
        // Returns the left trigger value
        public float LeftTrigger
        {
            get
            {
                return GetLeftTriggerWrapper(_xBoxControllerPointer);
            }
        }
        // Returns the right trigger value
        public float RightTrigger
        {
            get
            {
                return GetRightTriggerWrapper(_xBoxControllerPointer);
            }
        }
        // Returns a struct of buttons status values
        public XInput_Gamepad Buttons
        {
            get
            {
                return GetButtonsWrapper(_xBoxControllerPointer);
            }
        }
        // Returns a struct of battery status values
        public XInput_BatteryInfo Battery
        {
            get
            {
                return GetBatteryWrapper(_xBoxControllerPointer);
            }
        }
        // Returns a struct of device capabilities
        public XInput_Capabilities Capabilites
        {
            get
            {
                return GetCapabilitesWrapper(_xBoxControllerPointer);
            }
        }
        // Set the rumble on the controller
        public void Rumble(float leftMotor, float rightMotor)
        {
            SetRumbleWrapper(_xBoxControllerPointer, leftMotor, rightMotor);
        }
    }
}
