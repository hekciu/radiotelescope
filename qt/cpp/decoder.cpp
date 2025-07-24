#include "decoder.h"
#include <QtCore/QDebug>


Radiotelescope::AntennaData Radiotelescope::Decoder::decode(const QByteArray & data) {
    if (data.length() < RT_ANTENNA_DATA_SIZE) {
        throw std::exception();
    };

    AntennaData output = {0, 0};

    uint32_t byte0 = data.at(0);
    uint32_t byte1 = data.at(1);
    uint32_t byte2 = data.at(2);
    uint32_t byte3 = data.at(3);
    uint16_t byte4 = data.at(4);
    uint16_t byte5 = data.at(5);

    output.timestamp = (byte0 << 24) + (byte1 << 16) + (byte2 << 8) + byte3;

    output.value = (byte4 << 8) + byte5;

    return output;
};
