namespace RobotClient
{
    partial class MainWindow
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnUp = new System.Windows.Forms.Button();
            this.btnDown = new System.Windows.Forms.Button();
            this.btnLeft = new System.Windows.Forms.Button();
            this.btnRight = new System.Windows.Forms.Button();
            this.grpBoxControl = new System.Windows.Forms.GroupBox();
            this.lblTextEngineState = new System.Windows.Forms.Label();
            this.checkBoxRadarServo = new System.Windows.Forms.CheckBox();
            this.lblTextEngineSpeed = new System.Windows.Forms.Label();
            this.trackSpeed = new System.Windows.Forms.TrackBar();
            this.grpMeasurements = new System.Windows.Forms.GroupBox();
            this.lblAngleServo = new System.Windows.Forms.Label();
            this.lblDistanceBack = new System.Windows.Forms.Label();
            this.lblDistanceFront = new System.Windows.Forms.Label();
            this.lblTextServoAngle = new System.Windows.Forms.Label();
            this.lblTextBackDistance = new System.Windows.Forms.Label();
            this.lblTextFrontDistance = new System.Windows.Forms.Label();
            this.lblEngineState = new System.Windows.Forms.Label();
            this.lblEngineSpeed = new System.Windows.Forms.Label();
            this.grpBoxControl.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackSpeed)).BeginInit();
            this.grpMeasurements.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnUp
            // 
            this.btnUp.Location = new System.Drawing.Point(94, 19);
            this.btnUp.Name = "btnUp";
            this.btnUp.Size = new System.Drawing.Size(75, 70);
            this.btnUp.TabIndex = 0;
            this.btnUp.Text = "Up";
            this.btnUp.UseVisualStyleBackColor = true;
            this.btnUp.Click += new System.EventHandler(this.btnUp_Click);
            // 
            // btnDown
            // 
            this.btnDown.Location = new System.Drawing.Point(94, 95);
            this.btnDown.Name = "btnDown";
            this.btnDown.Size = new System.Drawing.Size(75, 70);
            this.btnDown.TabIndex = 1;
            this.btnDown.Text = "Down";
            this.btnDown.UseVisualStyleBackColor = true;
            this.btnDown.Click += new System.EventHandler(this.btnDown_Click);
            // 
            // btnLeft
            // 
            this.btnLeft.Location = new System.Drawing.Point(13, 95);
            this.btnLeft.Name = "btnLeft";
            this.btnLeft.Size = new System.Drawing.Size(75, 70);
            this.btnLeft.TabIndex = 2;
            this.btnLeft.Text = "Left";
            this.btnLeft.UseVisualStyleBackColor = true;
            this.btnLeft.Click += new System.EventHandler(this.btnLeft_Click);
            // 
            // btnRight
            // 
            this.btnRight.Location = new System.Drawing.Point(175, 95);
            this.btnRight.Name = "btnRight";
            this.btnRight.Size = new System.Drawing.Size(75, 70);
            this.btnRight.TabIndex = 3;
            this.btnRight.Text = "Right";
            this.btnRight.UseVisualStyleBackColor = true;
            this.btnRight.Click += new System.EventHandler(this.btnRight_Click);
            // 
            // grpBoxControl
            // 
            this.grpBoxControl.Controls.Add(this.lblEngineSpeed);
            this.grpBoxControl.Controls.Add(this.lblEngineState);
            this.grpBoxControl.Controls.Add(this.lblTextEngineState);
            this.grpBoxControl.Controls.Add(this.checkBoxRadarServo);
            this.grpBoxControl.Controls.Add(this.lblTextEngineSpeed);
            this.grpBoxControl.Controls.Add(this.trackSpeed);
            this.grpBoxControl.Controls.Add(this.btnUp);
            this.grpBoxControl.Controls.Add(this.btnRight);
            this.grpBoxControl.Controls.Add(this.btnDown);
            this.grpBoxControl.Controls.Add(this.btnLeft);
            this.grpBoxControl.Location = new System.Drawing.Point(12, 6);
            this.grpBoxControl.Name = "grpBoxControl";
            this.grpBoxControl.Size = new System.Drawing.Size(265, 289);
            this.grpBoxControl.TabIndex = 4;
            this.grpBoxControl.TabStop = false;
            this.grpBoxControl.Text = "Control";
            // 
            // lblTextEngineState
            // 
            this.lblTextEngineState.AutoSize = true;
            this.lblTextEngineState.Location = new System.Drawing.Point(10, 168);
            this.lblTextEngineState.Name = "lblTextEngineState";
            this.lblTextEngineState.Size = new System.Drawing.Size(71, 13);
            this.lblTextEngineState.TabIndex = 7;
            this.lblTextEngineState.Text = "Engine State:";
            // 
            // checkBoxRadarServo
            // 
            this.checkBoxRadarServo.AutoSize = true;
            this.checkBoxRadarServo.Checked = true;
            this.checkBoxRadarServo.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxRadarServo.Location = new System.Drawing.Point(13, 265);
            this.checkBoxRadarServo.Name = "checkBoxRadarServo";
            this.checkBoxRadarServo.Size = new System.Drawing.Size(129, 17);
            this.checkBoxRadarServo.TabIndex = 4;
            this.checkBoxRadarServo.Text = "Radar Servo Rotation";
            this.checkBoxRadarServo.UseVisualStyleBackColor = true;
            // 
            // lblTextEngineSpeed
            // 
            this.lblTextEngineSpeed.AutoSize = true;
            this.lblTextEngineSpeed.Location = new System.Drawing.Point(10, 198);
            this.lblTextEngineSpeed.Name = "lblTextEngineSpeed";
            this.lblTextEngineSpeed.Size = new System.Drawing.Size(77, 13);
            this.lblTextEngineSpeed.TabIndex = 6;
            this.lblTextEngineSpeed.Text = "Engine Speed:";
            // 
            // trackSpeed
            // 
            this.trackSpeed.Location = new System.Drawing.Point(13, 214);
            this.trackSpeed.Maximum = 255;
            this.trackSpeed.Name = "trackSpeed";
            this.trackSpeed.Size = new System.Drawing.Size(237, 45);
            this.trackSpeed.TabIndex = 5;
            this.trackSpeed.Value = 200;
            this.trackSpeed.DragDrop += new System.Windows.Forms.DragEventHandler(this.trackSpeed_DragDrop);
            // 
            // grpMeasurements
            // 
            this.grpMeasurements.Controls.Add(this.lblAngleServo);
            this.grpMeasurements.Controls.Add(this.lblDistanceBack);
            this.grpMeasurements.Controls.Add(this.lblDistanceFront);
            this.grpMeasurements.Controls.Add(this.lblTextServoAngle);
            this.grpMeasurements.Controls.Add(this.lblTextBackDistance);
            this.grpMeasurements.Controls.Add(this.lblTextFrontDistance);
            this.grpMeasurements.Location = new System.Drawing.Point(284, 6);
            this.grpMeasurements.Name = "grpMeasurements";
            this.grpMeasurements.Size = new System.Drawing.Size(218, 289);
            this.grpMeasurements.TabIndex = 5;
            this.grpMeasurements.TabStop = false;
            this.grpMeasurements.Text = "Measurements";
            // 
            // lblAngleServo
            // 
            this.lblAngleServo.AutoSize = true;
            this.lblAngleServo.Location = new System.Drawing.Point(114, 76);
            this.lblAngleServo.Name = "lblAngleServo";
            this.lblAngleServo.Size = new System.Drawing.Size(0, 13);
            this.lblAngleServo.TabIndex = 11;
            // 
            // lblDistanceBack
            // 
            this.lblDistanceBack.AutoSize = true;
            this.lblDistanceBack.Location = new System.Drawing.Point(114, 48);
            this.lblDistanceBack.Name = "lblDistanceBack";
            this.lblDistanceBack.Size = new System.Drawing.Size(0, 13);
            this.lblDistanceBack.TabIndex = 11;
            // 
            // lblDistanceFront
            // 
            this.lblDistanceFront.AutoSize = true;
            this.lblDistanceFront.Location = new System.Drawing.Point(114, 19);
            this.lblDistanceFront.Name = "lblDistanceFront";
            this.lblDistanceFront.Size = new System.Drawing.Size(0, 13);
            this.lblDistanceFront.TabIndex = 11;
            // 
            // lblTextServoAngle
            // 
            this.lblTextServoAngle.AutoSize = true;
            this.lblTextServoAngle.Location = new System.Drawing.Point(6, 76);
            this.lblTextServoAngle.Name = "lblTextServoAngle";
            this.lblTextServoAngle.Size = new System.Drawing.Size(68, 13);
            this.lblTextServoAngle.TabIndex = 10;
            this.lblTextServoAngle.Text = "Servo Angle:";
            // 
            // lblTextBackDistance
            // 
            this.lblTextBackDistance.AutoSize = true;
            this.lblTextBackDistance.Location = new System.Drawing.Point(6, 48);
            this.lblTextBackDistance.Name = "lblTextBackDistance";
            this.lblTextBackDistance.Size = new System.Drawing.Size(103, 13);
            this.lblTextBackDistance.TabIndex = 9;
            this.lblTextBackDistance.Text = "Back Distance (cm):";
            // 
            // lblTextFrontDistance
            // 
            this.lblTextFrontDistance.AutoSize = true;
            this.lblTextFrontDistance.Location = new System.Drawing.Point(6, 19);
            this.lblTextFrontDistance.Name = "lblTextFrontDistance";
            this.lblTextFrontDistance.Size = new System.Drawing.Size(102, 13);
            this.lblTextFrontDistance.TabIndex = 8;
            this.lblTextFrontDistance.Text = "Front Distance (cm):";
            // 
            // lblEngineState
            // 
            this.lblEngineState.AutoSize = true;
            this.lblEngineState.Location = new System.Drawing.Point(106, 168);
            this.lblEngineState.Name = "lblEngineState";
            this.lblEngineState.Size = new System.Drawing.Size(0, 13);
            this.lblEngineState.TabIndex = 8;
            // 
            // lblEngineSpeed
            // 
            this.lblEngineSpeed.AutoSize = true;
            this.lblEngineSpeed.Location = new System.Drawing.Point(107, 198);
            this.lblEngineSpeed.Name = "lblEngineSpeed";
            this.lblEngineSpeed.Size = new System.Drawing.Size(0, 13);
            this.lblEngineSpeed.TabIndex = 9;
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(841, 304);
            this.Controls.Add(this.grpMeasurements);
            this.Controls.Add(this.grpBoxControl);
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(857, 343);
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(857, 343);
            this.Name = "MainWindow";
            this.Text = "frmMain";
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.MainWindow_KeyDown);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.MainWindow_KeyUp);
            this.grpBoxControl.ResumeLayout(false);
            this.grpBoxControl.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackSpeed)).EndInit();
            this.grpMeasurements.ResumeLayout(false);
            this.grpMeasurements.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnUp;
        private System.Windows.Forms.Button btnDown;
        private System.Windows.Forms.Button btnLeft;
        private System.Windows.Forms.Button btnRight;
        private System.Windows.Forms.GroupBox grpBoxControl;
        private System.Windows.Forms.Label lblTextEngineState;
        private System.Windows.Forms.CheckBox checkBoxRadarServo;
        private System.Windows.Forms.Label lblTextEngineSpeed;
        private System.Windows.Forms.TrackBar trackSpeed;
        private System.Windows.Forms.GroupBox grpMeasurements;
        private System.Windows.Forms.Label lblAngleServo;
        private System.Windows.Forms.Label lblDistanceBack;
        private System.Windows.Forms.Label lblDistanceFront;
        private System.Windows.Forms.Label lblTextServoAngle;
        private System.Windows.Forms.Label lblTextBackDistance;
        private System.Windows.Forms.Label lblTextFrontDistance;
        private System.Windows.Forms.Label lblEngineSpeed;
        private System.Windows.Forms.Label lblEngineState;
    }
}

