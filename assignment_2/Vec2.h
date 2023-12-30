
#ifndef VEC2_H
#define VEC2_H

class Vec2{
public:
    double x, y;

    Vec2(double x, double y) : x(x), y(y) {}

    bool operator == (const Vec2& other) const;
    bool operator != (const Vec2& other) const;
    Vec2 operator +  (const Vec2& other) const;
    Vec2 operator -  (const Vec2& other) const;
    Vec2 operator *  (const Vec2& other) const;
    Vec2 operator /  (const Vec2& other) const;

    void normalise();
    double lenght() const;

};

#endif