#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP


#include <atomic>
#include <string>
#include <thread>
#include <mutex>


enum RobotRequest {
    FORWARD         = 0x01,
    BACKWARD        = 0x02,
    RIGHT           = 0x04,
    LEFT            = 0x08,
    STOP            = 0x0F,

    RIGHT_FORWARD   = RIGHT | FORWARD,
    RIGHT_BACKWARD  = RIGHT | BACKWARD,
    LEFT_FORWARD    = LEFT | FORWARD,
    LEFT_BACKWARD   = LEFT | BACKWARD,

    PING            = 0x10,
    ACK             = 0x11,
    NACK            = 0x12,
    ENGINE_SPEED    = 0x13,
};


class Controller {
private:
    std::string                 mDevice;
    std::atomic<unsigned char>  mRequest;
    std::mutex                  mLock;

    unsigned char               mState      = (unsigned char) RobotRequest::STOP;

    std::thread         mController;
    bool                mStopFlag   = true;

public:
    Controller(void) = default;

    Controller(const std::string & pDevice);

    Controller(const Controller & pOther) = delete;

    Controller(Controller & pOther) = default;

    virtual ~Controller(void) = default;

public:
    void Speed(const unsigned char pSpeed);

    void Action(const RobotRequest pRequest);

    void Start(void);

    void Stop(void);

private:
    void ThreadRunner(void);
};


#endif
