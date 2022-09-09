
### Hello Xbox Controller

Now you are ready to start using the TwinCAT Xbox Controller Service!

Make sure that the Xbox controller is plugged in, PLC library installed, and the service is running.To create an Xbox controller connection inside the PLC, you'll instantiate a new controller like this.

```javascript
VAR
    // Create a new controller
    XboxController : FB_Xbox_Controller(NetID := '', iControllerNumber := 1);

    // Status of controller connection
    bIsConnected   : BOOL;
END_VAR
```

```javascript
// Update all the controller I/O
XboxController.Cycle();

// Check if controller is connected
bIsConnected := XboxController.P_Status.bConnected;;
```

---

The **NetID** is the PC running the service application. This can be remote and supply an ADS address, or it can be left as '' for local.

The **iControllerNumber** is the controller ID you would like to access. Each time a controller is connected to Windows, it is given a number. The service currently supports up to 4 controllers per system due to Windows XInput, but you can also have multiple PCs hosting data to a single PLC.

---

**MANDATORY!!!**

You must call the Cycle method to update the inputs and outputs of the controller. Without this, you will see no data coming across. This Cycle method works similar to the XPlanar Standard library as it updates all the internals.
