
namespace RobotClient
{
    public enum Header
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
        ACK = 0x11,
        NACK = 0x12,
        ENGINE_SPEED = 0x13,
        MEASUREMENT = 0x14
    }
}
