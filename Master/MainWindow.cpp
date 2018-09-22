#include "MainWindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mRobot("COM5"),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFocus();

    Controller::Subscriber func = std::bind(&MainWindow::notifyMeasurementEvent, this, std::placeholders::_1);
    mRobot.subscribe(func);
    mRobot.start();
}


MainWindow::~MainWindow() {
    mRobot.stop();
    delete ui;
}


void MainWindow::notifyMeasurementEvent(Measurement & p_measurement) {
    ui->lblDistanceBack->setText(QString::number(p_measurement.m_range_back));
    ui->lblDistanceFront->setText(QString::number(p_measurement.m_range_front));
    ui->lblServoAngle->setText(QString::number(p_measurement.m_servo_angle));
}


void MainWindow::keyPressEvent(QKeyEvent * event) {
    if (!event->isAutoRepeat()) {
        mPressedButton += (Qt::Key) event->key();
        processKeyCode();
    }
}


void MainWindow::keyReleaseEvent(QKeyEvent * event) {
    if (!event->isAutoRepeat()) {
        mPressedButton -= (Qt::Key) event->key();
        processKeyCode();
    }
}


void MainWindow::mousePressEvent(QMouseEvent * event) {
    (void) event;
    setFocus();
}


void MainWindow::processKeyCode(void) {
    if (!mRobot.ready()) {
        return;
    }

    unsigned char control_code = 0x00;
    QString state_text = "";

    for (auto & key : mPressedButton) {
        switch(key) {
            case Qt::Key_Up: {
                control_code &= ~RobotRequest::BACKWARD;
                control_code |= RobotRequest::FORWARD;

                state_text += " Up";
                break;
            }

            case Qt::Key_Down: {
                control_code &= ~RobotRequest::FORWARD;
                control_code |= RobotRequest::BACKWARD;

                state_text += " Down";
                break;
            }

            case Qt::Key_Left: {
                control_code &= ~RobotRequest::RIGHT;
                control_code |= RobotRequest::LEFT;

                state_text += " Left";
                break;
            }

            case Qt::Key_Right: {
                control_code &= ~RobotRequest::LEFT;
                control_code |= RobotRequest::RIGHT;

                state_text += " Right";
                break;
            }

            default: break;
        }
    }

    if (mPressedButton.empty()) {
        mRobot.action(STOP);
    }
    else {
        mRobot.action((RobotRequest) control_code);
    }

    if (ui->lblState->text() != state_text) {
        ui->lblState->setText(state_text);
    }
}


void MainWindow::on_sldSpeed_sliderReleased() {
    int speed_rate = ui->sldSpeed->value();
    if (speed_rate != ui->lcdSpeed->intValue()) {
        ui->lcdSpeed->display(speed_rate);

        mRobot.speed(speed_rate);
    }
}

