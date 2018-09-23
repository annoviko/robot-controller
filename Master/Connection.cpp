#include "Connection.hpp"

#include <chrono>
#include <exception>
#include <iostream>
#include <thread>


const std::size_t Connection::RECEIVE_BUFFER_SIZE = 256;


Connection::Connection(const QString & p_endpoint) :
    m_serial(p_endpoint)
{
    m_serial.setPortName(p_endpoint);
    m_serial.setBaudRate(QSerialPort::Baud9600, QSerialPort::AllDirections);
    m_serial.setDataBits(QSerialPort::Data8);
    m_serial.setParity(QSerialPort::NoParity);
    m_serial.setStopBits(QSerialPort::OneStop);
    m_serial.setFlowControl(QSerialPort::NoFlowControl);

    if (!m_serial.open(QIODevice::ReadWrite)) {
        std::cout << "Impossible to connect to port '" << p_endpoint.toUtf8().constData() << "'." << std::endl;
        throw std::invalid_argument("Invalid port is specified.");
    }
}


ResponseMessage Connection::send(const char p_command) {
    ByteArray request(1, p_command);
    return send(request);
}


ResponseMessage Connection::send(const ByteArray & p_message) {
    ResponseMessage response;
    response.m_header = ResponseHeader::NONE;

    auto bytes = m_serial.write(p_message.data(), static_cast<qint64>(p_message.size()));
    if (bytes != p_message.size()) {
        std::cout << "Impossible to write data to port." << std::endl;
        return response;
    }

    if (!m_serial.waitForBytesWritten(500)) {
        std::cout << "Impossible to write data to port (timeout error)." << std::endl;
        return response;
    }

    bytes = m_serial.read((char *) &(response.m_header), 1);
    response.m_payload = m_serial.readAll();

    return response;
}
