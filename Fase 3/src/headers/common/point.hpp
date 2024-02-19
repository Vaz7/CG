#ifndef POINT_HEADER
#define POINT_HEADER
#include <string>

class Point {
    private:
        float x;
        float y;
        float z;
    
    public:
        Point(float, float, float);
        Point();
        float getX() const;
        float getY() const;
        float getZ() const;
        void setX(float);
        void setY(float);
        void setZ(float);
        std::string toString();
        Point operator+(Point) const;
        Point operator-(Point) const;
        Point operator*(float) const;
        Point operator/(float) const;
};

#endif