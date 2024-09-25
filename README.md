# TwinCAT Xbox Controller Service



### Project Description:

This service connects Xbox controllers attached to PCs/IPCs/CXs and then hosts the data for the PLC to access. TwinCAT Xbox Controller Service is designed to be a system service for TwinCAT Windows systems using .Net 6.



### Installers and Releases:

Please visit [the Releases section of the GitHub page](https://github.com/Beckhoff-USA-Community/TwinCAT-Xbox-Controller-Service/releases) to find the latest version of the MSI installer and the latest PLC Library. The latest copy of the PLC library will be included with the MSI installer, but it will also be included as a separate download if you only need to update the PLC Library.



### Documentation:

For the latest documentation on installing the service and using the API, [please visit the documentation website](https://beckhoff-usa-community.github.io/TC_XboxController/).



[<img src=".\Images\PLCDocScreenshot.png" alt="DocScreenshot" style="zoom: 75%;" />](https://beckhoff-usa-community.github.io/TwinCAT-Xbox-Controller-Service/)



### Future Feature List:

- Eventually a Unix based branch for TC/BSD systems using .Net 6
  - The rumble effect will not be functional, but the inputs are readable
- Build into constant Windows System Service, no console launch
- Additional PLC FB Helper Blocks

### Disclaimer:

All sample code provided by Beckhoff Automation LLC are for illustrative purposes only and are provided “as is” and without any warranties, express or implied. Actual implementations in applications will vary significantly. Beckhoff Automation LLC shall have no liability for, and does not waive any rights in relation to, any code samples that it provides or the use of such code samples for any purpose.
