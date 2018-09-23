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
                DistanceFront = BitConverter.ToInt32(p_bytes, offset),
                DistanceBack = BitConverter.ToInt32(p_bytes, offset + 4),
                Angle = BitConverter.ToInt16(p_bytes, offset + 8)
            };

            return result;
        }
    }
}
