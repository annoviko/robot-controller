namespace RobotClient
{
    public enum RequestHeader
    {
        FORWARD = 0x01,
        BACKWARD = 0x02,
        RIGHT = 0x04,
        LEFT = 0x08,
        STOP = 0x0F,

        RIGHT_FORWARD = RIGHT | FORWARD,
        RIGHT_BACKWARD = RIGHT | BACKWARD,
        LEFT_FORWARD = LEFT | FORWARD,
        LEFT_BACKWARD = LEFT | BACKWARD,

        PING = 0x10,
        ENGINE_SPEED = 0x11,
        MEASUREMENT = 0x12,
        SERVO_STOP = 0x13,
        SERVO_START = 0x14
    }

    public class Request
    {
        protected RequestHeader m_header;

        public Request(RequestHeader p_header)
        {
            m_header = p_header;
        }

        public virtual byte[] GetBytes()
        {
            byte[] result = { (byte)m_header };
            return result;
        }
    }

    public class RequestSpeed : Request
    {
        protected byte m_speed;

        public RequestSpeed(byte p_speed) : base(RequestHeader.ENGINE_SPEED)
        {
            m_speed = p_speed;
        }

        public override byte[] GetBytes()
        {
            byte[] result = { (byte) m_header, m_speed };
            return result;
        }
    }
}
