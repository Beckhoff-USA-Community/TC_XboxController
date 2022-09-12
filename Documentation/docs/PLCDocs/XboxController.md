
# FB_Xbox_Controller

This documentation is to serve as a reference for the FB_Xbox_Controller function block that is included with the XboxControllerUtilities PLC library. Please visit the Getting Started section for the installation of the PLC library.

## Accessing a controller

```javascript
VAR
    // Create a new controller
    XboxController : FB_Xbox_Controller(NetID := '', iControllerNumber := 1);
END_VAR
```

| Parameter         | Type       | Description                                                                                                                                                      |
| --------------    | ---------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| NetID             | T_AMSNETID | This is the AMS NetID of the controller that is hosting the TwinCAT Xbox Controller Service. For local, you can leave it as the default **NetID := ' '**.        |
| iControllerNumber | UINT(1..4) | This is the controller number you would like to access. Windows allocated the controllers based on the order connected. These controllers are numbered 1 to 4.   |


---

## Cycle Method

The cycle method is a must have for using the XboxControllerUtilities library. This method polls the server to read/write data from the controller. Similar to other TwinCAT libraries like the XPlanar, it is necessary to call this method to retrieve/set I/O cyclically. In addition to this, you can stop calling the Cycle method to quit all ADS communication to the Controller Service.

```javascript
// Update IO
XboxController.Cycle();
```

---

## Accessing Inputs

With the controller inputs the developer is given a choice to return the individual values, or a complex data structure. See the Button Inputs section below as a reference to each approach.

### **Button Inputs**
Access Individual Boolean Values

```javascript
IF XboxController.P_Buttons.bA_Button THEN
    // Do Something
END_IF
```
Alternatively, you can retrieve a full structure of all buttons

```javascript
// Returns ST_Xbox_Controller_Buttons
stControllerButtons := XboxController.P_Buttons;
```

### **Joystick Inputs**

```javascript
// Returns ST_Xbox_Controller_Joystick
stLeftJoystick := XboxController.P_Left_Joystick;
```

```javascript
// Returns ST_Xbox_Controller_Joystick
stRightJoystick := XboxController.P_Right_Joystick;
```
```javascript
// Returns REAL
fLeftJoystick_Y := XboxController.P_Left_Joystick.fX;
fLeftJoystick_X := XboxController.P_Left_Joystick.fY;
```

### **Trigger Inputs**

```javascript
// Returns REAL
fLeftTrigger := XboxController.P_Left_Trigger;
```

```javascript
// Returns REAL
fRightTrigger := XboxController.P_Right_Trigger;
```


---

## Accessing Status Bits

The status bits include auxiliary inputs such as the controllers connection status, battery type, and battery level.

```javascript
// Returns ST_Xbox_Controller_Status
stControllerStatus := XboxController.P_Status;
```

### **Connection Status**

```javascript
// Returns BOOL
bConnected := XboxController.P_Status.bConnected;
```

```javascript
// Returns BOOL
bDisconnected := XboxController.P_Status.bDisconnected;
```

### **Controller Number**

```javascript
// Returns INT
iControllerNumber := XboxController.P_Status.iControllerNumber;
```

### **Battery Type**

With the battery functions such as Level and Type, the status is not instant upon first call. The controller expects some buttons to be pressed or joysticks to be moved to update to the latest status. This is due to the way the Microsoft XInput DLL handles battery information updates.

```javascript
// Returns E_Xbox_Controller_Battery_Types
eBatteryType := XboxController.P_Status.Battery_Type;
```

### **Battery Level**

Battery level is only available if the battery type is a known type

```javascript
// Returns E_Xbox_Controller_Battery_Levels
eBatteryLevel := XboxController.P_Status.Battery_Level;
```


---

## Setting Outputs

### Controller Rumble

For the Force Feedback (Rumble) feature, you can continuously call the method and it will set it internally upon new value. Alternatively, you can call the set method and wait for feedback that the rumble values have actually been set.

```javascript
// Sets rumble
IF bSetRumble THEN
    XboxController.SetRumble(fLeftMotor := 50.0, fRightMotor := 25.0);
	// Check if the rumble has been set
	IF XboxController.P_SetRumble.Done THEN
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

### **ST_Xbox_Controller_Buttons**

| Name              | Type                      | Description               |
| ----------------- | ------------------------- | ------------------------- |
| DPad              | ST_Xbox_Controller_DPad   | Directional Pad Structure |
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

### **ST_Xbox_Controller_DPad**

| Name              | Type                      | Description                   |
| ----------------- | ------------------------- | ----------------------------- |
| bUp               | BOOL                      | Status of Up button on DPad   |
| bDown             | BOOL                      | Status of Down button on DPad |
| bLeft             | BOOL                      | Status of Left button on DPad |
| bRight            | BOOL                      | Status of Right button on DPad|

### **ST_Xbox_Controller_Joystick**

| Name              | Type                      | Description                        |
| ----------------- | ------------------------- | ---------------------------------- |
| fX                | REAL                      | Joystick's X Value (-100...100%)   |
| fY                | REAL                      | Joystick's Y Value (-100...100%)   |


### **ST_Xbox_Controller_Status**

| Name              | Type                              | Description                              |
| ----------------- | --------------------------------- | ---------------------------------------- |
| iControllerNumber | BOOL                              | Controller's ID                          |
| bConnected        | BOOL                              | Controller is connected to the PC        |
| bDisconnected     | BOOL                              | Controller is disconnected from the PC   |
| eBattery_Type     | E_Xbox_Controller_Battery_Types   | Battery Type                             |
| eBattery_Level    | E_Xbox_Controller_Battery_Levels  | Battery Level                            |

### **E_Xbox_Controller_Battery_Types**

| Name              | Value | Description                       |
| ----------------- | ----- | --------------------------------- |
| Disconnected      | 0     | Battery is disconnected           |
| Wired             | 1     | Controller is wired type          |
| Alkaline          | 2     | Battery is alkaline               |
| NIMH              | 3     | Battery is nickel-metal hydride   |
| Unknown           | 4     | Battery is unknown                |

### **E_Xbox_Controller_Battery_Levels**

| Name              | Value | Description                   |
| ----------------- | ----- | ----------------------------- |
| Empty             | 0     | Battery is Empty or Unknown   |
| Low               | 1     | Battery is at low level       |
| Medium            | 2     | Battery is at medium level    |
| Full              | 3     | Battery is at full level      |