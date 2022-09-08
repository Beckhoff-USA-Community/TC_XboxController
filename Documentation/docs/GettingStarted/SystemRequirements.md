
# Getting Started


## PC/IPC/CX Requirements

- Windows 10 or higher
- Microsoft .Net 6.0.7 Runtime (Installer will auto-download if connected to internet)
- TwinCAT XAR

## XBox Controller Requirements

The TwinCAT XBox Controller Service uses a Microsoft XInput based DLL to access the XBox controller. This DLL is light weight and C++ based, but it there are specific controllers that it supports.

Controllers Supported:

- Xbox Elite Controller Series
- Xbox Series X|S controllers
- Xbox One controllers
- Xbox 360 controllers

## Wireless or Wired Connectivity

For wired connectivity the configuration is straightforward. As of initial testing, the controllers listed above all function with a simple USB-C to USB-A cable between the IPC and XBox controller.

For wireless connectivity, it is recommended to use the [Microsoft official XBox USB dongle.](https://www.xbox.com/en-US/accessories/adapters/wireless-adapter-windows) This dongle allows connection to 4 controllers simultaneously. To use the Microsoft dongle, you will need to install the driver manually or have the system updates enabled. Since Beckhoff CXs/IPCs have updates disabled, there is a provided driver in the MSI installer of the TwinCAT XBox Controller Service project. Follow these steps to install the driver.

1. Install the project MSI
2. Locate the CAB file at *C:\Program Files\Beckhoff Community\TwinCAT XBox Controller Service\Offline Installers\Wireless Drivers*
3. Extract the CAB file (using 7-zip or other tool)
4. Right-click -> Install on the driver
5. Plugin dongle

---
**NOTE**

You can attempt to use an off the shelf USB bluetooth dongle to connect the controller wirelessly, however results in testing have been mixed. Due to the way Microsoft handles the connection to the USB dongle, it's best to use their officially supported dongle.

---

