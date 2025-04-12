#pragma once

#include <ostream>

class Point
{
   public:
    enum class PointTypes
    {
        noPath = 0,
        path = 1
    };
    Point() = default;
    Point(int x, int y, int value) : row(x), col(y), value(validate(value)) {}
    bool isPath() const { return value == PointTypes::path; };
    Point::PointTypes getValue() const { return value; };
    int getRow() const { return row; }
    int getCol() const { return col; }
    void setPoint(int r, int c, int val);
    bool operator==(const Point& other) const;

   private:
    int row;
    int col;
    PointTypes value = PointTypes::noPath;
    static PointTypes validate(int value);
};

std::ostream& operator<<(std::ostream& os, const Point& point);
