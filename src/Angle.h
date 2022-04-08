#ifndef ANGLE_H
#define ANGLE_H
#include <cstdint>

enum class Quadrant {
    I,
    II,
    III,
    IV
};

class Angle {
    public:
        Angle() = default;
        Angle(uint8_t value);
        virtual ~Angle() = default;

        friend Angle operator+ (const Angle& lhs, const Angle& rhs);
        friend Angle operator+ (const Angle& lhs, uint8_t rhs);
        friend Angle operator- (const Angle& lhs, const Angle& rhs);
        friend Angle operator- (const Angle& lhs, uint8_t rhs);

        Angle& operator++();
        Angle operator++(int);
        Angle& operator--();
        Angle operator--(int);

        uint8_t getValue() const;
        uint8_t getReducedValue() const;
        Quadrant getQuadrant() const;

    private:
        void reduce();

        uint8_t value;
        uint8_t reducedValue;
};

#endif // ANGLE_H
