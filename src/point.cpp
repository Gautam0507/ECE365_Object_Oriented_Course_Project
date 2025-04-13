#include "point.hpp"

#include <iostream>
#include <ostream>
#include <stdexcept>

void Point::setPoint(int r, int c, int val)
{
    row = r;
    col = c;
    value = validate(val);
}

bool Point::operator==(const Point& other) const
{
    return row == other.row && col == other.col;
}

Point::PointTypes Point::validate(int value)
{
    if (value == 0) {
        return PointTypes::noPath;
    } else if (value == 1) {
        return PointTypes::path;
    } else {
        throw std::invalid_argument(
            "Invalid point value: " + std::to_string(value) +
            ". Expected 0 (noPath) or 1 (path)");
    }
}

std::ostream& operator<<(std::ostream& os, const Point& point)
{
    switch (point.getValue()) {
        case Point::PointTypes::noPath:
            os << "[X]";
            break;
        case Point::PointTypes::path:
            os << "[ ]";
            break;
        default:
            os << "[?]";
            break;
    }
    return os;
}
