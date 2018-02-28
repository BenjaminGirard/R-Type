#ifndef BINARY_HPP_
# define BINARY_HPP_

# include <cstring>
# include <stdexcept>
# include <vector>
# include <memory>

#include <iostream>
namespace SolidRType {
    template<class SerializedType>
    void operator<<(std::vector<char> &dest, SerializedType &source) {
        if (dest.size() < sizeof(SerializedType))
            throw std::range_error("Size of struct superior to buffer Struct to Char");
        std::memcpy(dest.data(), &source, sizeof(SerializedType));
    }

    template<class SerializedType>
    void operator<<(SerializedType &dest, std::vector<char> &source) {
        if (source.size() < sizeof(SerializedType))
            throw std::range_error("Size of struct superior to buffer Char to Struct");
        std::memcpy(&dest, source.data(), sizeof(SerializedType));
    }

    //  #pragma pack(1)
    template<class DataType>
    struct UdpPkg {
        int64_t id;
        int32_t pkg_id;
        DataType data;
    };

    // #pragma pack(1)
    template<class DataType>
    struct TcpPkg {
        int8_t pkg_id;
        DataType data;
    };
}

#endif //BINARY_HPP_
