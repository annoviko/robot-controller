#include "Controller.hpp"

#include <cstring>
#include <iostream>
#include <cerrno>

#include <QSerialPort>

#include "StringConverter.hpp"
#include "Measurement.hpp"


Controller::Controller(const QString & p_device) :
    m_connection(p_device)
{
    std::cout << "Device: " << p_device.data() << std::endl;
}


void Controller::action(const RobotRequest p_request) {
    m_request.store(static_cast<char>(p_request), std::memory_order_seq_cst);
}


void Controller::speed(const char p_speed) {
    m_connection.send({ ENGINE_SPEED, p_speed });
}


void Controller::start(void) {
    m_stop = false;
    m_controller = std::thread(&Controller::run, this);
}


void Controller::stop(void) {
    m_stop = true;
    m_controller.join();
}


void Controller::notify(void) {
    std::lock_guard<std::mutex> lock(m_lock);
    for (const auto & subscriber : m_subscribers) {
        subscriber(m_measurement);
    }
}


void Controller::subscribe(const Subscriber & p_subscriber) {
    std::lock_guard<std::mutex> lock(m_lock);
    m_subscribers.push_back(p_subscriber);
}


bool Controller::ready(void) const {
    return !m_stop;
}


void Controller::run(void) {
    std::cout << "Robot Controller is started..." << std::endl;

    while(!m_stop) {
        m_state = m_request.load(std::memory_order_seq_cst);

        /* Send state */
        m_connection.send(m_state);

        /* Send request to obtain measurements */
        auto response = m_connection.send(MEASUREMENT);
        if (response.m_header == ResponseHeader::ACK) {
            /* Store measurement and notify subscribers */
            m_measurement = *((Measurement *) (response.m_payload.data()));
            notify();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    std::cout << "Robot Controller is terminated..." << std::endl;
}
