using System;
using System.Collections;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System;
using System.Collections;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.IO;
using TwinCAT.Ads.Server;
using TwinCAT.Ads;
using Microsoft.Extensions.Logging;
using System.Threading;
using System.Threading.Tasks;
using System.Buffers.Binary;

namespace TwinCAT_XBox_Controller_Service
{
    /*
     * Extend the TcAdsServer class to implement ADS Server
     */
    public class AdsControllerServer : AdsServer
    {
        /* XBox/ADS Input Variable Struct */
        private struct ADS_XBox_Inputs
        {
            public int ControllerNumber;
            public float LeftStick_Y;
            public float LeftStick_X;
            public float RightStick_Y;
            public float RightStick_X;
            public float LeftTrigger;
            public float RightTrigger;
            public short Buttons;
            public short States;
        }

        /* Constants */
        const int MAXIMUM_CONTROLLERS = 4;

        /* Private Variables */
        private IServerLogger serverLogger;
        private XBoxController[] xBoxControllers = new XBoxController[MAXIMUM_CONTROLLERS];

        /* Instanstiate an ADS server with a fix ADS port assigned by the ADS router.
        */
        public AdsControllerServer(ushort port, string portName, ILogger logger) : base(port, portName, logger)
        {
            serverLogger = new ServerLogger(logger);
            for (int i = 0; i < MAXIMUM_CONTROLLERS; ++i)
            {
                xBoxControllers[i] = new XBoxController(i+1);
            }
        }

        ~AdsControllerServer()
        {

        }


        /* Diagnostics output for the server
        */
        protected override void OnConnected()
        {
            serverLogger.Logger.LogInformation($"Server '{this.GetType()}', Address: {base.ServerAddress} connected!");
        }

        /* Writing values from the client to this server
         */
        protected override Task<ResultWrite> OnWriteAsync(uint indexGroup, uint indexOffset, ReadOnlyMemory<byte> writeData, CancellationToken cancel)
        {
            ResultWrite result = ResultWrite.CreateError(AdsErrorCode.DeviceServiceNotSupported);

            for (int i = 0; i < MAXIMUM_CONTROLLERS; ++i)
            {
                xBoxControllers[i].Update();
            }

            /* use index group (and offset) to distinguish between the servicesof this server */
            switch (indexGroup + indexOffset) 
            {
                case 0x10010:
                    if (writeData.Length == 8 && xBoxControllers[0].Connected)
                    {
                        byte[] _dataBuffer = new byte[8];
                        writeData.CopyTo(_dataBuffer.AsMemory(0, 8));
                        float left_Motor = System.BitConverter.ToSingle(_dataBuffer, 0);
                        float right_Motor = System.BitConverter.ToSingle(_dataBuffer, 4);
                        xBoxControllers[0].Rumble(left_Motor, right_Motor);
                        result = ResultWrite.CreateSuccess();
                    }
                    else
                    {
                        result = ResultWrite.CreateError(AdsErrorCode.DeviceInvalidParam);
                    }
                    break;
                case 0x20010:
                    if (writeData.Length == 8 && xBoxControllers[1].Connected)
                    {
                        byte[] _dataBuffer = new byte[8];
                        writeData.CopyTo(_dataBuffer.AsMemory(0, 8));
                        float left_Motor = System.BitConverter.ToSingle(_dataBuffer, 0);
                        float right_Motor = System.BitConverter.ToSingle(_dataBuffer, 4);
                        xBoxControllers[1].Rumble(left_Motor, right_Motor);
                        result = ResultWrite.CreateSuccess();
                    }
                    else
                    {
                        result = ResultWrite.CreateError(AdsErrorCode.DeviceInvalidParam);
                    }
                    break;
                case 0x30010:
                    if (writeData.Length == 8 && xBoxControllers[2].Connected)
                    {
                        byte[] _dataBuffer = new byte[8];
                        writeData.CopyTo(_dataBuffer.AsMemory(0, 8));
                        float left_Motor = System.BitConverter.ToSingle(_dataBuffer, 0);
                        float right_Motor = System.BitConverter.ToSingle(_dataBuffer, 4);
                        xBoxControllers[2].Rumble(left_Motor, right_Motor);
                        result = ResultWrite.CreateSuccess();
                    }
                    else
                    {
                        result = ResultWrite.CreateError(AdsErrorCode.DeviceInvalidParam);
                    }
                    break;
                case 0x40010:
                    if (writeData.Length == 8 && xBoxControllers[3].Connected)
                    {
                        byte[] _dataBuffer = new byte[8];
                        writeData.CopyTo(_dataBuffer.AsMemory(0, 8));
                        float left_Motor = System.BitConverter.ToSingle(_dataBuffer, 0);
                        float right_Motor = System.BitConverter.ToSingle(_dataBuffer, 4);
                        xBoxControllers[3].Rumble(left_Motor, right_Motor);
                        result = ResultWrite.CreateSuccess();
                    }
                    else
                    {
                        result = ResultWrite.CreateError(AdsErrorCode.DeviceInvalidParam);
                    }
                    break;
                default: /* other services are not supported */
                    result = ResultWrite.CreateError(AdsErrorCode.DeviceServiceNotSupported);
                    break;
            }
            return Task.FromResult(result);
        }

        /* Reading values from the server to a client
        */
        protected override Task<ResultReadBytes> OnReadAsync(uint indexGroup, uint indexOffset, int readLength, CancellationToken cancel)
        {
            ResultReadBytes result;
            /* use index group (and offset) to distinguish between the servicesof this server */
            switch (indexGroup) 
            {
                case 0x10000:
                    result = ResultReadBytes.CreateSuccess(ConvertXBoxInputBytes(GetXboxValues(xBoxControllers[0])).AsMemory());
                    break;
                case 0x20000:
                    result = ResultReadBytes.CreateSuccess(ConvertXBoxInputBytes(GetXboxValues(xBoxControllers[1])).AsMemory());
                    break;
                case 0x30000:
                    result = ResultReadBytes.CreateSuccess(ConvertXBoxInputBytes(GetXboxValues(xBoxControllers[2])).AsMemory());
                    break;
                case 0x40000:
                    result = ResultReadBytes.CreateSuccess(ConvertXBoxInputBytes(GetXboxValues(xBoxControllers[3])).AsMemory());
                    break;
                default: /* other services are not supported */
                    result = ResultReadBytes.CreateError(AdsErrorCode.DeviceInvalidGroup);        
                    break;
            }
            return Task.FromResult(result);
        }

        /* Converts the XBox Data Structure to byte array
         */
        private byte[] ConvertXBoxInputBytes(ADS_XBox_Inputs xbox_input_data)
        {
            int size = Marshal.SizeOf(xbox_input_data);
            byte[] arr = new byte[size];

            IntPtr ptr = Marshal.AllocHGlobal(size);
            Marshal.StructureToPtr(xbox_input_data, ptr, true);
            Marshal.Copy(ptr, arr, 0, size);
            Marshal.FreeHGlobal(ptr);
            return arr;
        }


        /* Call the XInput methods to get the Gamepad status
        */
        private ADS_XBox_Inputs GetXboxValues(XBoxController xBoxController)
        {
            ADS_XBox_Inputs xBoxInputs = new ADS_XBox_Inputs();
            xBoxController.Update();
            if (xBoxController.Connected)
            {
                
                xBoxInputs.ControllerNumber = xBoxController.ControllerNumber;
                xBoxInputs.LeftStick_Y = xBoxController.LeftStick_Y;
                xBoxInputs.LeftStick_X = xBoxController.LeftStick_X;
                xBoxInputs.RightStick_Y = xBoxController.RightStick_Y;
                xBoxInputs.RightStick_X = xBoxController.RightStick_X;
                xBoxInputs.LeftTrigger = xBoxController.LeftTrigger;
                xBoxInputs.RightTrigger = xBoxController.RightTrigger;

                /* Set the different bits for the short */
                if (xBoxController.Buttons.DPad_Up)
                    xBoxInputs.Buttons = (short)(xBoxInputs.Buttons | (1 << 0));
                if (xBoxController.Buttons.DPad_Down)
                    xBoxInputs.Buttons = (short)(xBoxInputs.Buttons | (1 << 1));
                if (xBoxController.Buttons.DPad_Left)
                    xBoxInputs.Buttons = (short)(xBoxInputs.Buttons | (1 << 2));
                if (xBoxController.Buttons.DPad_Right)
                    xBoxInputs.Buttons = (short)(xBoxInputs.Buttons | (1 << 3));
                if (xBoxController.Buttons.Start)
                    xBoxInputs.Buttons = (short)(xBoxInputs.Buttons | (1 << 4));
                if (xBoxController.Buttons.Back)
                    xBoxInputs.Buttons = (short)(xBoxInputs.Buttons | (1 << 5));
                if (xBoxController.Buttons.L_Thumstick)
                    xBoxInputs.Buttons = (short)(xBoxInputs.Buttons | (1 << 6));
                if (xBoxController.Buttons.R_Thumstick)
                    xBoxInputs.Buttons = (short)(xBoxInputs.Buttons | (1 << 7));
                if (xBoxController.Buttons.L_Shoulder)
                    xBoxInputs.Buttons = (short)(xBoxInputs.Buttons | (1 << 8));
                if (xBoxController.Buttons.R_Shoulder)
                    xBoxInputs.Buttons = (short)(xBoxInputs.Buttons | (1 << 9));
                if (xBoxController.Buttons.A)
                    xBoxInputs.Buttons = (short)(xBoxInputs.Buttons | (1 << 12));
                if (xBoxController.Buttons.B)
                    xBoxInputs.Buttons = (short)(xBoxInputs.Buttons | (1 << 13));
                if (xBoxController.Buttons.X)
                    xBoxInputs.Buttons = (short)(xBoxInputs.Buttons | (1 << 14));
                if (xBoxController.Buttons.Y)
                    xBoxInputs.Buttons = (short)(xBoxInputs.Buttons | (1 << 15));

                /* Set the different bits for the short */
                if (xBoxController.Connected)
                    xBoxInputs.States = (short)(xBoxInputs.States | (1 << 0));
                if (xBoxController.Battery.Type_Disconnected)
                    xBoxInputs.States = (short)(xBoxInputs.States | (1 << 1));
                if (xBoxController.Battery.Type_Wired)
                    xBoxInputs.States = (short)(xBoxInputs.States | (1 << 2));
                if (xBoxController.Battery.Type_Alkaline)
                    xBoxInputs.States = (short)(xBoxInputs.States | (1 << 3));
                if (xBoxController.Battery.Type_NIMH)
                    xBoxInputs.States = (short)(xBoxInputs.States | (1 << 4));
                if (xBoxController.Battery.Type_Unknown)
                    xBoxInputs.States = (short)(xBoxInputs.States | (1 << 5));
                if (xBoxController.Battery.Level_Empty)
                    xBoxInputs.States = (short)(xBoxInputs.States | (1 << 6));
                if (xBoxController.Battery.Level_Low)
                    xBoxInputs.States = (short)(xBoxInputs.States | (1 << 7));
                if (xBoxController.Battery.Level_Medium)
                    xBoxInputs.States = (short)(xBoxInputs.States | (1 << 8));
                if (xBoxController.Battery.Level_Full)
                    xBoxInputs.States = (short)(xBoxInputs.States | (1 << 9));

            }
            return xBoxInputs;
        }
    }
}