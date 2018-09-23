namespace RobotClient
{
    public enum ResponseHeader
    {
        ACK = 0x80,
        NACK = 0x81,
        MEASUREMENT = 0x82
    }

    public class Response
    {
        private ResponseHeader Header { get; }

        public Response(ResponseHeader p_header)
        {
            Header = p_header;
        }
    }

    public class ResponseMeasurement : Response
    {
        public Measurement Statistic { get; }

        public ResponseMeasurement(Measurement p_statistic) : base(ResponseHeader.MEASUREMENT)
        {
            Statistic = p_statistic;
        }
    }

    public class ResponseParser
    {
        static public Response Parse(byte[] p_bytes)
        {
            if (p_bytes.Length == 0)
            {
                return null;
            }

            ResponseHeader header_value = (ResponseHeader) p_bytes[0];
            switch(header_value)
            {
                case ResponseHeader.ACK:
                case ResponseHeader.NACK:
                    return new Response(header_value);
                case ResponseHeader.MEASUREMENT:
                    return new ResponseMeasurement(Measurement.Parse(p_bytes, 1));
                default:
                    return null;
            }
        }
    }
}
