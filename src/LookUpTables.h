#ifndef LOOKUPTABLES_H
#define LOOKUPTABLES_H

#include "Angle.h"
#include "lutGenerators.h"
#include <vector>
#include <cstdint>

class LookUpTables {
    public:
        LookUpTables() = default;
        virtual ~LookUpTables() = default;

        uint32_t getMxOverCos(uint8_t x, const Angle &theta) const;
        uint32_t getMxOverSin(uint8_t x, const Angle &theta) const;
        uint32_t getMCos(const Angle &theta) const;

    private:
        std::vector<std::vector<uint32_t>> mxOverCos = lutGenerators::generateMXOverCos(128, 16, 64);
        std::vector<std::vector<uint32_t>> mxOverSin = lutGenerators::generateMXOverSin(128, 16, 64);
        std::vector<uint32_t> mCos = lutGenerators::generateMCos(128, 40);
};

#endif // LOOKUPTABLES_H
