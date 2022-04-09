#ifndef LOOKUPTABLES_H
#define LOOKUPTABLES_H

#include "Angle.h"
#include "lutGenerators.h"
#include <vector>
#include <cstdint>

class LookUpTables
{
    public:
        LookUpTables() = default;
        LookUpTables(uint16_t m, uint8_t maxX, uint8_t maxTheta);
        virtual ~LookUpTables() = default;

        uint32_t getMxOverCos(uint8_t x, const Angle &theta) const;
        uint32_t getMxOverSin(uint8_t x, const Angle &theta) const;
        uint32_t getMCos(const Angle &theta) const;

    private:
        std::vector<std::vector<uint32_t>> mxOverCos;
        std::vector<std::vector<uint32_t>> mxOverSin;
        std::vector<uint32_t> mCos;
};

#endif // LOOKUPTABLES_H
