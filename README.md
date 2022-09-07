# TwinCAT XBox Controller Service



## Project Description -

This service connects to XBox controllers attached to the PC, and then hosts the data for the PLC to access. TwinCAT XBox Controller Service is designed to be a system service for TwinCAT Windows systems using .Net 6.



## System Requirements -

The driver for the Xbox Common Controller class (XUSB) on Windows implements the kernel-mode interface for the XINPUT DLL. With this in mind, there are only certain Xbox controller models that are supported within the C++ driver. These are the available options:

- Xbox 360 controllers 

- Xbox One controllers

- Xbox Series X|S controllers

Other controller types are supported by the XInput driver for Windows, however they have not been tested to work with this project. 



#### PC Requirements:

- Windows 10 or higher
- .Net Runtime 6.0.7 (If connected to the internet, the installer will download it for you)
- The system running the TwinCAT XBox Controller Service needs the TwinCAT ADS Service



#### Wireless connectivity:

For wireless connectivity, you can test out using an off-the-shelf Bluetooth USB adapter. For the best results you should use the [Microsoft official XBox USB dongle](https://www.amazon.com/Microsoft-Xbox-Wireless-Adapter-Windows-one/dp/B00ZB7W4QU?ref_=ast_sto_dp), as it allows four controllers per dongle and is relatively easy to configure.

To use the Microsoft dongle on a Beckhoff controller, you will need to install the driver manually or have the system updates enabled. Since Beckhoff controllers ship with updates disabled, [here is the driver package](http://download.windowsupdate.com/c/msdownload/update/driver/drvs/2017/07/8d560b9e-a5ee-41c6-81b9-03abaef1429e_bbaf9811ab6e5bd7f4172eb5d4abca8b7ca37277.cab) and install instructions.

1. Extract the CAB file (using 7-zip or other tool)
2. Right-click -> Install on the driver
3. Plugin dongle



## Installing the TwinCAT XBox Controller Service -

Within this repo, you will find that there is an MSI installer located in the [Releases area](https://github.com/Beckhoff-USA-Community/TwinCAT-XBox-Controller-Service/releases). For ease of use, it's recommended to use this installer as opposed to building the project from scratch. This installer will install the .Net Core components, ADS server project, and also install the PLC library needed.

To import the PLC library, the file will be located in <u>C:\Program Files\TcXBoxServiceProvider\TC XBox Controller Service\TwinCAT Files</u>



>Note: If building from source will require VS 2022 Professional with C++, .Net Core 6, and Microsoft Package Installer plugin. Since there are various kernel mode drivers, you might need to also run the package installer as Release. You will receive DLL errors for the service if distributing the setup.exe while in Debug mode.





## Using The Service -

Throughout any period of the project you should be able to plugin and enable/connect the controller. To change the player order of the controllers, you will need to disable them all and re-enable them in the order you would like.



#### 1. Start the service inside Windows

- Start the service, and keep it running in the background

<img src="Images\image-20220602081200295.png" alt="AppStart" style="zoom:120%;" />


  <img src="Images\image-20220602081056315.png" alt="Service" style="zoom:100%;" />

  

#### 2. Create a PLC instance

To bring the XBox controller into PLC land, we first need to create an instance of ``` FB_XBox_Controller```. The function block is initialized with the AMS NetID of the Beckhoff IPC running the TwinCAT XBox Service, and also the controller number. You will need one of these for each of the controllers you want to use in the project.



An example of initializing a controller that is connected as player one:

```reStructuredText
fbXBoxController	:	FB_XBox_Controller(NetID := '', iControllerNumber := 1);
```



#### 3. Using the XBox controller

The controller API currently allows all mappable inputs to be used in the PLC, and also the two rumble output motors. There is however, one mandatory command to get things running. 



Required to be called cyclically:

```
// Reaches out to the ADS service and updates I/O
fbXBoxController.Cycle();
```



## API

Retrieving Inputs:

```c++
// Reaches out to the ADS service and updates I/O
fbXBoxController.Cycle();

// Gets a structure of buttons
stButtons := fbXBoxController.P_Buttons;

// Gets a single button
IF fbXBoxController.P_Buttons.bA_Button THEN
	//Do something....
END_IF

// Gets joysticks
stLeftJoystick := fbXBoxController.P_Left_Joytick;
stRightJoystick := fbXBoxController.P_Right_Joytick;

// Gets triggers
fLeftTrigger := fbXBoxController.P_Left_Trigger;
fRightTrigger := fbXBoxController.P_Right_Trigger;



// Sets rumble
IF bSetRumble THEN
    fbXBoxController.SetRumble(fLeftMotor := 50.0, fRightMotor := 25.0);
	// Check if the rumble has been set
	IF fbXBoxController.P_SetRumble.Done THEN
        bSetRumble := FALSE;
    END_IF
END_IF
```





## How It Works -

Unlike other XBox-to-TwinCAT projects that use an ADS Client, TwinCAT XBox Controller Service is running as an ADS Server and hosting data on customer port 25733. This gives the user significant advantages in not only configuration ease, but also flexibility. Once the service is started, it begins monitoring the PC's XBox controller connections via a C++ based XBox-XInput DLL, and this data is then hosted to ADS clients upon request. The user accesses the data easily via PLC function block that is located inside the XBoxControllerUtilites.library.

Most projects are limited to 4 controllers maximum, due to the maximum count allowed on a PC by the XInput service. However, due to the way this is architected, the amount of controllers is theoretically based on the maximum ADS traffic. You can host 4 controllers per PC, but you can connect many different PCs to the PLC via different ADS routes. This has also been successfully tested with ADS-over-MQTT from 2 different "service hosters" and has demonstrated good results.



## Future Feature List:

- Eventually a Unix based branch for TC/BSD systems using .Net 6
  - The rumble effect will not be functional, but the inputs are readable
- Implement Battery status
- Implement Wireless vs Wire status
- Build into constant Windows System Service, no console launch
- Additional PLC FB features, including easy to use Axis control features
