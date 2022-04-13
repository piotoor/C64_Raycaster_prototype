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

        uint16_t getMxOverCos(uint8_t x, const Angle &theta) const;
        uint16_t getMxOverSin(uint8_t x, const Angle &theta) const;
        uint16_t getCosX128(const Angle &theta) const;
        uint16_t getSinX128(const Angle &theta) const;
        uint16_t getCosX16(const Angle &theta) const;
        uint16_t getSinX16(const Angle &theta) const;

    private:
        std::vector<std::vector<uint16_t>> mxOverCos = lutGenerators::generateMXOverCos(128, 16, 64);
        std::vector<std::vector<uint16_t>> mxOverSin = lutGenerators::generateMXOverSin(128, 16, 64);
        std::vector<uint16_t> cosX128 = lutGenerators::generateMCos(128, 40);
        std::vector<uint16_t> sinX128 = lutGenerators::generateMSin(128, 40);
        std::vector<uint16_t> cosX16 = lutGenerators::generateMCos(16, 64);
        std::vector<uint16_t> sinX16= lutGenerators::generateMSin(16, 64);
};

#endif // LOOKUPTABLES_H
