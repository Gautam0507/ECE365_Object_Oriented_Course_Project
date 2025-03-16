class Point
{
   public:
    Point() = default;
    Point(int x, int y, int value)
        : x(x), y(y), value(static_cast<PointTypes>(value))
    {
    }
    bool isPath() const;
    void setValue(int val);
    int getValue() const;

   private:
    int x;
    int y;
    enum class PointTypes
    {
        noPath = 0,
        path = 1
    };
    PointTypes value;
};
