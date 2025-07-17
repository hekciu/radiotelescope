#include "decoder.h"


// maybe use QByteArray?
Radiotelescope::AntennaMeasurement Radiotelescope::Decoder::decode(const QString & data) {
    if (data.length() < sizeof(Radiotelescope::AntennaMeasurement)) {};
};
