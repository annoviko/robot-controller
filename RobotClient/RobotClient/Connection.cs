using System.IO.Ports;

namespace RobotClient
{
    class Connection
    {
        private SerialPort m_port;

        public Connection() { }

        public Connection(string p_port)
        {
            m_port.PortName = p_port;
            m_port.BaudRate = 9600;
            m_port.DataBits = 8;
            m_port.Parity = System.IO.Ports.Parity.None;
            m_port.StopBits = System.IO.Ports.StopBits.One;
            m_port.ReadTimeout = 1000;
            m_port.WriteTimeout = 1000;

            m_port.Open();
        }

        ~Connection()
        {
            m_port.Close();
        }

        public void SendRequest(Request p_request)
        {
            byte[] request_buffer = p_request.GetBytes();
            m_port.Write(request_buffer, 0, request_buffer.Length);
        }

        public Response ReceiveResponse()
        {
            byte[] response_buffer = new byte[64];
            m_port.Read(response_buffer, 0, 1);

            switch((ResponseHeader) response_buffer[0])
            {
                case ResponseHeader.ACK:
                case ResponseHeader.NACK:
                    return ResponseParser.Parse(response_buffer);
                case ResponseHeader.MEASUREMENT:
                    m_port.Read(response_buffer, 1, Measurement.Length());
                    return ResponseParser.Parse(response_buffer);
                default:
                    return null;
            }
        }
    }
}
