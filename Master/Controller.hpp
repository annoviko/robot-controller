#pragma once

#include <atomic>
#include <string>
#include <thread>
#include <mutex>

#include "Connection.hpp"
#include "Measurement.hpp"


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
    ENGINE_SPEED    = 0x13,
    MEASUREMENT     = 0x14
};


class Controller {
public:
    using Subscriber = std::function<void(Measurement &)>;

private:
    using SubscriberDatabase = std::vector<Subscriber>;

private:
    std::mutex          m_lock;

    std::atomic<char>   m_request;
    char                m_state         = static_cast<char>(RobotRequest::STOP);

    std::thread         m_controller;
    bool                m_stop          = true;

    Connection          m_connection;
    Measurement         m_measurement;
    SubscriberDatabase  m_subscribers   = { };

public:
    Controller(void) = default;

    Controller(const QString & p_device);

    Controller(const Controller & p_other) = delete;

    Controller(Controller & p_other) = delete;

    virtual ~Controller(void) = default;

public:
    void speed(const char p_speed);

    void action(const RobotRequest p_request);

    void start(void);

    void stop(void);

    void subscribe(const Subscriber & p_subscriber);

    bool ready(void) const;

private:
    void run(void);

    void notify(void);
};
