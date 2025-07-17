
#ifndef DECODER_H
#define DECODER_H

#include <cstdint>
#include "QtCore/QString"


namespace Radiotelescope {
    struct AntennaMeasurement;
    class Decoder;
};


struct Radiotelescope::AntennaMeasurement {
    uint32_t timestamp;
    uint16_t value;
};


class Radiotelescope::Decoder {
public:
    Decoder() = delete;
    static AntennaMeasurement decode(const QString &);
};

#endif
