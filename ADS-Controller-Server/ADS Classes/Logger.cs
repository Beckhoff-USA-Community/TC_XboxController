using Microsoft.Extensions.Logging;
using System;
using TwinCAT.Ads;
using TwinCAT.Ads.Server;


namespace TwinCAT_Xbox_Controller_Service
{
    public interface IServerLogger
    {
        ILogger Logger { get; }
    }

    public class ServerLoggerBase : IServerLogger
    {
        ILogger _logger = null;

        public ILogger Logger
        {
            get { return _logger; }
        }

        protected ServerLoggerBase(ILogger logger)
        {
            _logger = logger;
        }
    }

    public class ServerLogger : ServerLoggerBase
    {
        public ServerLogger(ILogger logger) : base(logger)
        {
        }

    }
}