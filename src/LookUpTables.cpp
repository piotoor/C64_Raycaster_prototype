#include "LookUpTables.h"

LookUpTables::LookUpTables(uint16_t m, uint8_t maxX, uint8_t maxTheta):
    mxOverCos(lutGenerators::generateMXOverCos(m, maxX, maxTheta)),
    mxOverSin(lutGenerators::generateMXOverSin(m, maxX, maxTheta)),
    mCos(lutGenerators::generateMCos(m, maxTheta)) {
}

uint32_t LookUpTables::getMxOverCos(uint8_t x, const Angle &theta) const {
    return mxOverCos[x][theta.getReducedValue()];
}

uint32_t LookUpTables::getMxOverSin(uint8_t x, const Angle &theta) const {
    return mxOverSin[x][theta.getReducedValue()];
}

uint32_t LookUpTables::getMCos(const Angle &theta) const {
    return mCos[theta.getReducedValue()];
}
