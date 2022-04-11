#ifndef ANGLE_H
#define ANGLE_H
#include <cstdint>
#include <string>

enum class Quadrant {
    I,
    II,
    III,
    IV
};

class Angle {
    public:
        Angle(uint8_t value = 0);
        virtual ~Angle() = default;

        Angle& operator+= (const Angle& other);
        Angle& operator-= (const Angle& other);

        Angle& operator++();
        Angle operator++(int);
        Angle& operator--();
        Angle operator--(int);

        friend bool operator== (const Angle &lhs, const Angle& rhs);
        Angle getDist(const Angle& other);

        uint8_t getValue() const;
        uint8_t getReducedValue() const;
        Quadrant getQuadrant() const;
        std::string toString() const;

    private:
        void reduce();

        uint8_t value;
        uint8_t reducedValue;
};

Angle operator+ (const Angle& lhs, const Angle& rhs);
Angle operator+ (const Angle& lhs, uint8_t rhs);
Angle operator- (const Angle& lhs, const Angle& rhs);
Angle operator- (const Angle& lhs, uint8_t rhs);
bool operator< (const Angle& lhs, const Angle& rhs);
Angle operator/ (const Angle& lhs, uint8_t rhs);

#endif // ANGLE_H
