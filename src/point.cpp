#include "point.hpp"

#include <iostream>
#include <ostream>

void Point::setPoint(int r, int c, int val)
{
    row = r;
    col = c;
    value = validateValue(val);
}

bool Point::operator==(const Point& other) const
{
    return row == other.row && col == other.col;
}

inline std::ostream& operator<<(std::ostream& out, Point::PointTypes type)
{
    switch (type) {
        case Point::PointTypes::noPath:
            out << "[X]";
            break;
        case Point::PointTypes::path:
            out << "[ ]";
            break;
        default:
            out << "Invalid value";
            break;
    }
    return out;
}

Point::PointTypes Point::validateValue(int value)
{
    if (value == 0) {
        return PointTypes::noPath;
    } else if (value == 1) {
        return PointTypes::path;
    } else {
        std::cerr << "Invalid value passed into the program" << std::endl;
        return PointTypes::noPath;  // Default to noPath if invalid
    }
}

void Point::printPoint() const
{
    switch (value) {
        case Point::PointTypes::noPath:
            std::cout << "[X]";
            break;
        case Point::PointTypes::path:
            std::cout << "[ ]";
            break;
        default:
            std::cout << "Invalid value";
            break;
    }
}
