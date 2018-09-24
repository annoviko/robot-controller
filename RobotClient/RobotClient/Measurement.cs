using System;

namespace RobotClient
{
    public class Measurement
    {
        public Int32 DistanceFront { get; set; }
        public Int32 DistanceBack { get; set; }
        public Int16 Angle { get; set; }

        static public int Length()
        {
            return sizeof(Int32) * 2 + sizeof(Int16);
        }

        static public Measurement Parse(byte[] p_bytes, int offset)
        {
            Measurement result = new Measurement
            {
                DistanceFront = SwapEndianness(BitConverter.ToInt32(p_bytes, offset)),
                DistanceBack = SwapEndianness(BitConverter.ToInt32(p_bytes, offset + 4)),
                Angle = BitConverter.ToInt16(p_bytes, offset + 8)
            };

            return result;
        }

        private static int SwapEndianness(Int32 value)
        {
            var b1 = (value >> 0) & 0xff;
            var b2 = (value >> 8) & 0xff;
            var b3 = (value >> 16) & 0xff;
            var b4 = (value >> 24) & 0xff;

            return b1 << 24 | b2 << 16 | b3 << 8 | b4 << 0;
        }
    }
}
