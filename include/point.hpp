/**
 * @file point.hpp
 * @brief Defines the Point class representing a single cell in a maze grid
 */
#pragma once

#include <ostream>

/**
 * @class Point
 * @brief Represents a single cell in a maze grid
 *
 * A Point has a position (row, col) and a type value indicating whether
 * it's a traversable path or an obstacle.
 */
class Point
{
   public:
    /**
     * @enum PointTypes
     * @brief Defines possible types of a maze point
     */
    enum class PointTypes
    {
        noPath = 0,  ///< Cell is an obstacle/wall
        path = 1     ///< Cell is a traversable path
    };

    /**
     * @brief Default constructor
     */
    Point() = default;

    /**
     * @brief Constructs a Point with specific coordinates and type
     * @param x Row position
     * @param y Column position
     * @param value Point type (0 for noPath, 1 for path)
     */
    Point(int x, int y, int value) : row(x), col(y), value(validate(value)) {}

    /**
     * @brief Checks if the point is a traversable path
     * @return true if the point is a path, false otherwise
     */
    bool isPath() const { return value == PointTypes::path; };

    /**
     * @brief Gets the point's type
     * @return The PointType value (path or noPath)
     */
    Point::PointTypes getValue() const { return value; };

    /**
     * @brief Gets the row position
     * @return Row index
     */
    int getRow() const { return row; }

    /**
     * @brief Gets the column position
     * @return Column index
     */
    int getCol() const { return col; }

    /**
     * @brief Sets the point's position and type
     * @param r Row position
     * @param c Column position
     * @param val Point type value (0 or 1)
     */
    void setPoint(int r, int c, int val);

    /**
     * @brief Equality comparison operator
     * @param other Another Point to compare with
     * @return true if the points have the same position
     */
    bool operator==(const Point& other) const;

   private:
    int row;                                ///< Row position
    int col;                                ///< Column position
    PointTypes value = PointTypes::noPath;  ///< Point type (path or obstacle)

    /**
     * @brief Validates and converts an integer to a PointType
     * @param value Integer value to validate (0 or 1)
     * @return Corresponding PointType
     * @throws std::invalid_argument if value is not 0 or 1
     */
    static PointTypes validate(int value);
};

/**
 * @brief Stream insertion operator for Point objects
 * @param os Output stream
 * @param point Point to output
 * @return Modified output stream
 */
std::ostream& operator<<(std::ostream& os, const Point& point);
