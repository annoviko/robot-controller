using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace RobotClient
{
    public delegate void Subscriber(Measurement measurement);

    public enum Direction
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
    }

    public class Controller
    {
        private Thread m_controller;
        private bool m_stop;

        private Connection m_connection;

        private Mutex m_request_mutex;
        private Direction m_direction;

        private List<Subscriber> m_subscribers;

        public Controller()
        {
            m_connection = new Connection("COM5");
            m_subscribers = new List<Subscriber>();
            m_request_mutex = new Mutex();
        }

        public void Start()
        {
            m_stop = false;
            m_controller = new Thread(Run);
            m_controller.Start();
        }

        public void Stop()
        {
            m_stop = true;
            m_controller.Join();
        }

        public void Subscribe(Subscriber p_subscriber)
        {
            m_subscribers.Add(p_subscriber);
        }

        private Response ExecuteCommand(Request p_request)
        {
            m_request_mutex.WaitOne();

            m_connection.SendRequest(p_request);
            Response response = m_connection.ReceiveResponse();

            m_request_mutex.ReleaseMutex();

            return response;
        }

        public void SetSpeed(byte p_speed)
        {
            ExecuteCommand(new RequestSpeed(p_speed));
        }

        public void SetDirection(Direction p_direction)
        {
            if (p_direction != m_direction)
            {
                ExecuteCommand(new Request((RequestHeader) p_direction));
                m_direction = p_direction;
            }
        }

        public void StartServo()
        {
            ExecuteCommand(new Request(RequestHeader.SERVO_START));
        }

        public void StopServo()
        {
            ExecuteCommand(new Request(RequestHeader.SERVO_STOP));
        }

        public void Run()
        {
            while(!m_stop)
            {
                try
                {
                    ResponseMeasurement response = (ResponseMeasurement)ExecuteCommand(new Request(RequestHeader.MEASUREMENT));
                    if (response != null)
                    {
                        foreach (Subscriber client in m_subscribers)
                        {
                            client(response.Statistic);
                        }
                    }
                }
                catch(Exception)
                {
                    Console.WriteLine("ERROR: Impossible to get response.");
                }

                Thread.Sleep(100);
            }
        }
    }
}
