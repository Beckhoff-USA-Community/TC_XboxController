# XPlanar Helper Functions

This documentation is to serve as a reference for the XPlanar Helper function blocks that are included with the XboxControllerUtilities PLC library. Please visit the Getting Started section for the installation of the PLC library.

## Prerequisites

To use the XPlanar helper function blocks, the latest version of Tc3_XPlanarStandard needs to be installed.

## <span style="color:red">CAUTION!</span>
The blocks below use ExternalSetPoint commands under the hood, <span style="color:red">use at your own risk</span>. 

## Mover Controls

The following blocks are to control an FB_XPlanarMoverStandard from the Tc3_XPlanarStandardLibrary.

### **FB_Xbox_2D_Joystick_XPlanar**

The 2D Joystick block uses a single Xbox controller joystick to move an XPlanar mover in the X and Y direction. There is an optional E_Xbox_XPlanar_JogMode input to allow Fast or Slow jogging. The Fast jogging can also be commanded via button press (instantaneous) or trigger press (ramped).

```javascript
VAR
    // Xbox Controller Instance
    XboxController : FB_Xbox_Controller(NetID := '', iControllerNumber := 1);

	// FB_Xbox_2D_Joystick_XPlanar Instance
	fbXbox_2D_Joystick_XPlanar	: FB_Xbox_2D_Joystick_XPlanar;
    // Options for FB_Xbox_2D_Joystick_XPlanar
	stOptions					: ST_Xbox_2D_Joystick_XPlanar_Options;
    // Jog mode for the Mover
	eJogMode					: E_Xbox_XPlanar_JogMode;
    // Enable the jog feature
	bEnableJog					: BOOL;

    // Mover Object
	XPlanarMover				: FB_XPlanarMoverStandard;
    // Command Mover to Enable
	bEnableMover				: BOOL := TRUE;
END_VAR
```
```javascript
//Update the mover
XPlanarMover.Cycle();
//Update the Xbox controller
XboxController.Cycle();

// Enable the mover
IF bEnableMover THEN
	XPlanarMover.Enable(slogMessage := 'Enabling Mover');
	IF XPlanarMover.P_Enable.Done THEN
		bEnableMover := FALSE;
	END_IF
END_IF

// Set some jog options
stOptions.eJog_Mode 		:= eJogMode;
stOptions.fFastJog_Trigger 	:= XboxController.P_Left_Trigger;
stOptions.bFastJog_Button	:= XboxController.P_Buttons.bA_Button;

// Jog command for mover
fbXbox_2D_Joystick_XPlanar.Jog(
								bEnable:= bEnableJog AND XboxController.P_Status.bConnected, 
								stJoystick:= XboxController.P_Left_Joystick, 
								xpMover:= XPlanarMover, 
								stOptions:= stOptions);
```

| Parameter         | Type                                      | Description|
| --------------    | ----------------------------------------- | ----------------------------------------- |
| bEnable		    | BOOL                                      | Enable the jog command                    |
| stJoystick        | REFERENCE TO ST_Xbox_Controller_Joystick  | Reference to Xbox controller joystick     |
| xpMover	        | REFERENCE TO FB_XPlanarMoverStandard      | Reference to XPlanar Standard Mover       |
| stOptions			| ST_Xbox_2D_Joystick_XPlanar_Options       | Options for jogging the mover             |


---

## DUTs

### **ST_Xbox_2D_Joystick_XPlanar_Options**

| Name                    | Type                      | Default Value                       | Description                                                           |
| ----------------------- | ------------------------- | ----------------------------------- | --------------------------------------------------------------------- |
| eJog_Mode               | E_Xbox_XPlanar_JogMode    | E_Xbox_XPlanar_JogMode.Slow         | Jog mode for the mover                                                |
| fFeedrate               | LREAL                     | 100.0                               | Feedrate of the mover for jogging                                     |
| bFastJog_Button         | BOOL                      | FALSE                               | Button that is used for Fast Jogging                                  |
| fFastJog_Trigger        | REAL                      | 0.00                                | Trigger that is used for Fast Jogging                                 |


### **E_Xbox_XPlanar_JogMode**

| Name               Value | Description                   |
| -----------------  ----- | ----------------------------- |
| Slow               0     | Slow Mode Jog                 |
| FastWithButton     1     | Fast Mode with button press   |
| FastWithTrigger    2     | Fast Mode with trigger press  |