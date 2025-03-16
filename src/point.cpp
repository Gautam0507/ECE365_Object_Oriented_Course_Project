#include "point.hpp"

bool Point::isPath() const { return value == PointTypes::path; }

void Point::setValue(int val) { value = static_cast<PointTypes>(val); }

int Point::getValue() const { return static_cast<int>(value); }
