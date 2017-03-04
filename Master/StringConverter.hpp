#ifndef STRING_CONVERTER_HPP
#define STRING_CONVERTER_HPP


#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>


class ByteConverter {
public:
    template <typename ByteType>
    static std::string to_hex(const ByteType pValue) {
        std::stringstream stream;

        stream << std::setw(2) << std::setfill('0') << std::hex;
        stream << std::hex << (int) pValue;

        std::string result("\\x" + stream.str());

        return result;
    }
};


#endif
