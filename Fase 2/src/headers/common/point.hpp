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
        float getX() const;
        float getY() const;
        float getZ() const;
        void setX(float);
        void setY(float);
        void setZ(float);
        std::string toString();
};

#endif