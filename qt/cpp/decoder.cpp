#include "decoder.h"


Radiotelescope::AntennaData Radiotelescope::Decoder::decode(const QByteArray & data) {
    if (data.length() < sizeof(Radiotelescope::AntennaData)) {
    };
};
