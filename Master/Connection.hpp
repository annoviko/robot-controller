#pragma once


#include <vector>

#include <QSerialPort>


using ByteArray = std::vector<char>;


enum class ResponseHeader {
    ACK             = 0x11,
    NACK            = 0x12,
    NONE            = 0xFF
};


struct ResponseMessage {
    ResponseHeader      m_header;
    QByteArray          m_payload;
};


class Connection {
private:
    const static std::size_t RECEIVE_BUFFER_SIZE;

private:
    QSerialPort m_serial;

public:
    Connection(void) = default;

    Connection(const QString & p_endpoint);

public:
    ResponseMessage send(const char p_command);

    ResponseMessage send(const ByteArray & p_message);
};
