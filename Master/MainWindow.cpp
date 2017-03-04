#include "MainWindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mRobot("/dev/ttyACM0"),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFocus();
    mRobot.Start();
}


MainWindow::~MainWindow() {
    mRobot.Stop();
    delete ui;
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
        mRobot.Action(STOP);
    }
    else {
        mRobot.Action((RobotRequest) control_code);
    }

    if (ui->lblState->text() != state_text) {
        ui->lblState->setText(state_text);
    }
}


void MainWindow::on_sldSpeed_sliderReleased() {
    int speed_rate = ui->sldSpeed->value();
    if (speed_rate != ui->lcdSpeed->intValue()) {
        ui->lcdSpeed->display(speed_rate);

        mRobot.Speed(speed_rate);
    }
}
