#include "LookUpTables.h"

uint16_t LookUpTables::getMxOverCos(uint8_t x, const Angle &theta) const {
    return mxOverCos[x][theta.getReducedValue()];
}

uint16_t LookUpTables::getCosX128(const Angle &theta) const {
    return cosX128[theta.getReducedValue()];
}

uint16_t LookUpTables::getCosX16(const Angle& theta) const {
    return cosX16[theta.getReducedValue()];
}
