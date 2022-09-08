
# FB_XBox_Controller

This API Doc is to serve as a reference for the FB_XBox_Controller function block that is included with the XBoxControllerUtilities PLC library. Please visit the Getting Started section for the installation of the PLC library.

## Accessing a controller

```javascript
VAR
    // Create a new controller
    XBoxController : FB_XBox_Controller(NetID := '', iControllerNumber := 1);
END_VAR
```

| Parameter         | Type       | Description                                                                                                                                                      |
| --------------    | ---------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| NetID             | T_AMSNETID | This is the AMS NetID of the controller that is hosting the TwinCAT XBox Controller Service. For local, you can leave it as the default **NetID := ' '**.        |
| iControllerNumber | UINT(1..4) | This is the controller number you would like to access. Windows allocated the controllers based on the order connected. These controllers are numbered 1 to 4.   |


---

## Cycle Method

The cycle method is a must have for using the XBoxControllerUtilities library. This method polls the server to read/write data from the controller. Similar to other TwinCAT libraries like the XPlanar, it is necessary to call this method to retrieve/set I/O cyclically. In addition to this, you can stop calling the Cycle method to quit all ADS communication to the Controller Service.

```javascript
// Update IO
XBoxController.Cycle();
```

---

## Accessing Inputs

With the controller inputs the developer is given a choice to return the individual values, or a complex data structure. See the Button Inputs section below as a reference to each approach.

### **Button Inputs**
Access Individual Boolean Values

```javascript
IF XBoxController.P_Buttons.bA_Button THEN
    // Do Something
END_IF
```
Alternatively, you can retrieve a full structure of all buttons

```javascript
// Returns ST_XBox_Controller_Buttons
stControllerButtons := XBoxController.P_Buttons;
```

### **Joystick Inputs**

```javascript
// Returns ST_XBox_Controller_Joystick
stLeftJoystick := XBoxController.P_Left_Joystick;
```

```javascript
// Returns ST_XBox_Controller_Joystick
stRightJoystick := XBoxController.P_Right_Joystick;
```
```javascript
// Returns REAL
fLeftJoystick_Y := XBoxController.P_Left_Joystick.fX;
fLeftJoystick_X := XBoxController.P_Left_Joystick.fY;
```

### **Trigger Inputs**

```javascript
// Returns REAL
fLeftTrigger := XBoxController.P_Left_Trigger;
```

```javascript
// Returns REAL
fRightTrigger := XBoxController.P_Right_Trigger;
```


---

## Accessing Status Bits

The status bits include auxiliary inputs such as the controllers connection status, battery type, and battery level.

```javascript
// Returns ST_XBox_Controller_Status
stControllerStatus := XBoxController.P_Status;
```

### **Connection Status**

```javascript
// Returns BOOL
bConnected := XBoxController.P_Status.bConnected;
```

```javascript
// Returns BOOL
bDisconnected := XBoxController.P_Status.bDisconnected;
```

### **Controller Number**

```javascript
// Returns INT
iControllerNumber := XBoxController.P_Status.iControllerNumber;
```

### **Battery Type**

With the battery functions such as Level and Type, the status is not instant upon first call. The controller expects some buttons to be pressed or joysticks to be moved to update to the latest status. This is due to the way the Microsoft XInput DLL handles battery information updates.

```javascript
// Returns E_XBox_Controller_Battery_Types
eBatteryType := XBoxController.P_Status.Battery_Type;
```

### **Battery Level**

Battery level is only available if the battery type is a known type

```javascript
// Returns E_XBox_Controller_Battery_Levels
eBatteryLevel := XBoxController.P_Status.Battery_Level;
```


---

## Setting Outputs

### Controller Rumble

For the Force Feedback (Rumble) feature, you can continuously call the method and it will set it internally upon new value. Alternatively, you can call the set method and wait for feedback that the rumble values have actually been set.

```javascript
// Sets rumble
IF bSetRumble THEN
    XBoxController.SetRumble(fLeftMotor := 50.0, fRightMotor := 25.0);
	// Check if the rumble has been set
	IF XBoxController.P_SetRumble.Done THEN
        bSetRumble := FALSE;
    END_IF
END_IF
```

| Parameter              | Type | Description                                         |
| ---------------------- | ---- | --------------------------------------------------- |
| fLeftMotor             | REAL | Value of the left vibration motor speed (0..100%)   |
| fRightMotor            | REAL | Value of the right vibration motor speed (0..100%)  |



---

## DUTs

### **ST_XBox_Controller_Buttons**

| Name              | Type                      | Description               |
| ----------------- | ------------------------- | ------------------------- |
| DPad              | ST_XBox_Controller_DPad   | Directional Pad Structure |
| bStart            | BOOL                      | Status of start button    |
| bBack             | BOOL                      | Status of back button     |
| bLeft_Thumbstick  | BOOL                      | Status of Left Thumbstick |
| bRight_Thumbstick | BOOL                      | Status of Right Thumbstick|
| bLeft_Shoulder    | BOOL                      | Status of Left Shoulder   |
| bRight_Shoulder   | BOOL                      | Status of Right Shoulder  |
| bA_Button         | BOOL                      | Status of A button        |
| bB_Button         | BOOL                      | Status of B button        |
| bX_Button         | BOOL                      | Status of X button        |
| bY_Button         | BOOL                      | Status of Y button        |

### **ST_XBox_Controller_DPad**

| Name              | Type                      | Description                   |
| ----------------- | ------------------------- | ----------------------------- |
| bUp               | BOOL                      | Status of Up button on DPad   |
| bDown             | BOOL                      | Status of Down button on DPad |
| bLeft             | BOOL                      | Status of Left button on DPad |
| bRight            | BOOL                      | Status of Right button on DPad|

### **ST_XBox_Controller_Joystick**

| Name              | Type                      | Description                        |
| ----------------- | ------------------------- | ---------------------------------- |
| fX                | REAL                      | Joystick's X Value (-100...100%)   |
| fY                | REAL                      | Joystick's Y Value (-100...100%)   |


### **ST_XBox_Controller_Status**

| Name              | Type                              | Description                              |
| ----------------- | --------------------------------- | ---------------------------------------- |
| iControllerNumber | BOOL                              | Controller's ID                          |
| bConnected        | BOOL                              | Controller is connected to the PC        |
| bDisconnected     | BOOL                              | Controller is disconnected from the PC   |
| Battery_Type      | E_XBox_Controller_Battery_Types   | Battery Type                             |
| Battery_Level     | E_XBox_Controller_Battery_Levels  | Battery Level                            |

### **E_XBox_Controller_Battery_Types**

| Name              | Type                     | Value | Description                       |
| ----------------- | -------------------------| ----- | --------------------------------- |
| Disconnected      | BOOL                     | 0     | Battery is disconnected           |
| Wired             | BOOL                     | 1     | Controller is wired type          |
| Alkaline          | BOOL                     | 2     | Battery is alkaline               |
| NIMH              | BOOL                     | 3     | Battery is nickel-metal hydride   |
| Unknown           | BOOL                     | 4     | Battery is unknown                |

### **E_XBox_Controller_Battery_Levels**

| Name              | Type                      | Value | Description                   |
| ----------------- | ------------------------- | ----- | ----------------------------- |
| Empty             | BOOL                      | 0     | Battery is Empty or Unknown   |
| Low               | BOOL                      | 1     | Battery is at low level       |
| Medium            | BOOL                      | 2     | Battery is at medium level    |
| Full              | BOOL                      | 3     | Battery is at full level      |