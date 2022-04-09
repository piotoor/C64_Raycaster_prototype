#include "LookUpTables.h"

uint32_t LookUpTables::getMxOverCos(uint8_t x, const Angle &theta) const {
    return mxOverCos[x][theta.getReducedValue()];
}

uint32_t LookUpTables::getMxOverSin(uint8_t x, const Angle &theta) const {
    return mxOverSin[x][theta.getReducedValue()];
}

uint32_t LookUpTables::getMCos(const Angle &theta) const {
    return mCos[theta.getReducedValue()];
}
