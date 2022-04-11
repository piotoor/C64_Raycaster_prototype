#include "LookUpTables.h"

uint32_t LookUpTables::getMxOverCos(uint8_t x, const Angle &theta) const {
    return mxOverCos[x][theta.getReducedValue()];
}

uint32_t LookUpTables::getMxOverSin(uint8_t x, const Angle &theta) const {
    return mxOverSin[x][theta.getReducedValue()];
}

uint32_t LookUpTables::getCosX128(const Angle &theta) const {
    return cosX128[theta.getReducedValue()];
}

uint32_t LookUpTables::getCosX32(const Angle& theta) const {
    return cosX32[theta.getReducedValue()];
}

uint32_t LookUpTables::getSinX132(const Angle& theta) const {
    return sinX32[theta.getReducedValue()];
}
