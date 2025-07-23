#include "decoder.h"


Radiotelescope::AntennaData Radiotelescope::Decoder::decode(const QByteArray & data) {
    if (data.length() < RT_ANTENNA_DATA_SIZE) {
        throw std::exception();
    };

    AntennaData output = {0, 0};

    output.timestamp = (data.at(0) & 0xFF) << 24 +
        (data.at(1) & 0xFF) << 16 +
        (data.at(2) & 0xFF) << 8 +
        (data.at(3) & 0xFF);

    output.value = (data.at(4) & 0xFF) << 8 +
        (data.at(5) & 0xFF);

    return output;
};
