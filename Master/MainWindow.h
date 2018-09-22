#pragma once


#include <QMainWindow>
#include <QKeyEvent>
#include <QSet>

#include "Controller.hpp"


namespace Ui {
    class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
    QSet<Qt::Key>   mPressedButton;

    Controller      mRobot;

public:
    explicit MainWindow(QWidget *parent = nullptr);

    virtual ~MainWindow() override;

private:
    void processKeyCode(void);

    void notifyMeasurementEvent(Measurement & p_measurement);

protected:
    virtual void keyPressEvent(QKeyEvent * event) override;

    virtual void keyReleaseEvent(QKeyEvent * event) override;

    virtual void mousePressEvent (QMouseEvent * event) override;

signals:
    void keyCaught(QKeyEvent *e);

private slots:
    void on_sldSpeed_sliderReleased();

private:
    Ui::MainWindow *ui;
};
