
# API Overview

This documentation is to serve as a reference for the TwinCAT Xbox Controller Service and it's common PLC function blocks. Within this documentation you will find the **Primary Functions Blocks** and the **Helper Function Blocks**. Both are within the XboxControllerUtilities library for PLC. Please visit the Getting Started section for the installation of the PLC library.

## Primary Functions Blocks

These PLC function blocks are the core interface blocks for connecting an Xbox controller to the PLC. They will enable you to connect multiple controllers, retrieve status bits, stream button values, read battery data, and set force feedback (rumble).

---

## Helper Function Blocks

The helper function blocks are designed to make connection of an Xbox controller to other TwinCAT items easier. They are mostly wrapper blocks with many different operations happening within. At the moment, there are two helper function block categories supported.

### NC Axis FBs

These help with tasks such as attaching a two axis joystick to two independent NC Axis within TwinCAT. There are FBs to help with attaching a simple button pushes, analog triggers, and joysticks to drive an axis.

### XPlanar Mover FBs

These help with controlling an XPlanar Mover. Instead of needing to write a bunch of setpoint code, the blocks are designed to expedite the connection process and allow you to start driving a mover quickly.

---

## Under The Hood

**How does the TwinCAT Xbox Controller Service work?**

It's simple! The communication mechanism is TwinCAT's native ADS protocol. 

You may have seen other joystick or controller connection projects within the GitHub community. This project is special due to it being an **ADS Server** application. With the most recent update of ADS, there is support for ADS Servers based in .Net Core. Most of the commonly discovered projects within the community are using the **ADS CLient** connection.

**Why does Server vs. Client matter?**

With the Server, you simply need to start the service to begin hosting ADS data. When the PLC reaches out to the service on port **25733**, the service then reaches out to the Xbox controller via XInput to retrieve the latest data. This creates a very easy to use mechanism within the TwinCAT environment. The future road-map of the project (after V1.0) is to create a Windows background service to allow the application to run in the background continuously upon startup. 

In contrast, the ADS Client applications that are commonly developed are a little more cumbersome to get running. Usually there is a C# application that has to be built and deployed. There might also be the need to modify some PLC variable names within the C# application to insure everything matches on the PLC side. Once the variables are connected within the PLC, they cannon't move and must sit where they were originally configured.

**Limitations**

At the moment the project is aimed for Windows IPC/CX support. In the future there are plans to also support TC/BSD, however it will require a different C++ driver within the application to connect to the controller. This is already under development, but it is not the primary focus.

Due to XInput, there is a maximum controller count of 4 per TwinCAT Xbox Controller Service. However, this will not stop you from connecting 4+ controllers. Due to the ADS servers nature, you can have the Controller Service running on many IPCs and connect to them remotely from a single PLC. This has been tested with up to 8 controllers, and it even works successfully with an ADS connection via AWS Cloud using ADS-over-MQTT.