
#ifndef DECODER_H
#define DECODER_H

#include <cstdint>
#include "QtCore/QString"
#include "common_data.h"


namespace Radiotelescope {
    class Decoder;

    typedef Rt_Antenna_Data AntennaData;
};




class Radiotelescope::Decoder {
public:
    Decoder() = delete;
    static AntennaData decode(const QByteArray &);
};

#endif
