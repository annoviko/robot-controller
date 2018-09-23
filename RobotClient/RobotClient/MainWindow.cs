using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RobotClient
{
    public partial class MainWindow : Form
    {
        private HashSet<Keys> m_pressed;
        private Controller m_controller;

        static private HashSet<Keys> PERMITTED_KEYS = new HashSet<Keys>{ Keys.Up, Keys.Down, Keys.Left, Keys.Right };

        public MainWindow()
        {
            InitializeComponent();

            lblEngineSpeed.Text = trackSpeed.Value.ToString();
        }

        private void btnUp_Click(object sender, EventArgs e)
        {
            m_pressed.Add(Keys.Up);
            ProcessKeyCode();
        }

        private void btnLeft_Click(object sender, EventArgs e)
        {
            m_pressed.Add(Keys.Left);
            ProcessKeyCode();
        }

        private void btnDown_Click(object sender, EventArgs e)
        {
            m_pressed.Add(Keys.Down);
            ProcessKeyCode();
        }

        private void btnRight_Click(object sender, EventArgs e)
        {
            m_pressed.Add(Keys.Right);
            ProcessKeyCode();
        }

        private void MainWindow_KeyDown(object sender, KeyEventArgs e)
        {
            if (PERMITTED_KEYS.Contains(e.KeyCode))
            {
                m_pressed.Add(e.KeyCode);
                ProcessKeyCode();
            }
        }

        private void MainWindow_KeyUp(object sender, KeyEventArgs e)
        {
            if (PERMITTED_KEYS.Contains(e.KeyCode))
            {
                m_pressed.Remove(e.KeyCode);
                ProcessKeyCode();
            }
        }

        private void ProcessKeyCode()
        {
            Direction direction = 0;
            string state_text = "";

            foreach(Keys key in m_pressed)
            {
                switch (key)
                {
                    case Keys.Up:
                        direction &= ~Direction.BACKWARD;
                        direction |= Direction.FORWARD;
                        state_text += " Up";
                        break;

                    case Keys.Down:
                        direction &= ~Direction.FORWARD;
                        direction |= Direction.BACKWARD;
                        state_text += " Down";
                        break;

                    case Keys.Left:
                        direction &= ~Direction.RIGHT;
                        direction |= Direction.LEFT;
                        state_text += " Left";
                        break;

                    case Keys.Right:
                        direction &= ~Direction.LEFT;
                        direction |= Direction.RIGHT;
                        state_text += " Right";
                        break;

                    default:
                        break;
                }
            }

            if (m_pressed.Count == 0)
            {
                m_controller.SetDirection(Direction.STOP);
            }
            else
            {
                m_controller.SetDirection(direction);
            }

            lblEngineState.Text = state_text;
        }

        private void trackSpeed_DragDrop(object sender, DragEventArgs e)
        {
            int speed = trackSpeed.Value;

            m_controller.SetSpeed((byte)speed);
            lblEngineSpeed.Text = speed.ToString();
        }

        private void UpdateMeasurement(Measurement p_measurement)
        {
            lblDistanceFront.Text = p_measurement.DistanceFront.ToString();
            lblDistanceBack.Text = p_measurement.DistanceBack.ToString();
            lblAngleServo.Text = p_measurement.Angle.ToString();
        }
    }
}
