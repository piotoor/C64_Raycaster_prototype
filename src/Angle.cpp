#include "Angle.h"

Angle::Angle(uint8_t value) {
    this->value = value;
    reduce();
}

uint8_t Angle::getValue() const {
    return value;
}

uint8_t Angle::getReducedValue() const {
    return reducedValue;
}

Quadrant Angle::getQuadrant() const {
    if (value >= 0 and value < 64) {
        return Quadrant::I;
    } else if (value >= 64 and value < 128) {
        return Quadrant::II;
    } else if (value >= 128 and value < 192) {
        return Quadrant::III;
    } else {
        return Quadrant::IV;
    }
}

std::string Angle::toString() const {
    return std::to_string((int)value);
}

void Angle::reduce() {
    if (value >= 64 and value < 128) {
        reducedValue = 128 - value;
    } else if (value >= 128 and value < 192) {
        reducedValue = value - 128;
    } else if (value >= 192 and value < 256) {
        reducedValue = 256 - value;
    }
}

Angle operator+ (const Angle& lhs, const Angle& rhs) {
    return Angle(lhs.getValue() + rhs.getValue());
}

Angle operator+ (const Angle& lhs, uint8_t rhs) {
    return Angle(lhs.getValue() + rhs);
}

Angle operator- (const Angle& lhs, const Angle& rhs) {
    return Angle(lhs.getValue() - rhs.getValue());
}

Angle operator- (const Angle& lhs, uint8_t rhs) {
    return Angle(lhs.getValue() - rhs);
}

Angle& Angle::operator++() {
    value++;
    reduce();
    return *this;
}

Angle Angle::operator++(int) {
    uint8_t old = value;
    ++Angle();
    return old;
}

Angle& Angle::operator--() {
    value--;
    reduce();
    return *this;
}

Angle Angle::operator--(int) {
    uint8_t old = value;
    --Angle();
    return old;
}

bool operator== (const Angle &lhs, const Angle& rhs) {
    return lhs.getValue() == rhs.getValue();
}
