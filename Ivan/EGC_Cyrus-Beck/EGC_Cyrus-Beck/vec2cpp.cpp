#include "vec2.h"

namespace egc {
    vec2& vec2::operator =(const vec2& srcVector)
    {
        this->x = srcVector.x;
        this->y = srcVector.y;
        
        return *this;
    }
    vec2 vec2::operator +(const vec2& srcVector) const {
        vec2 rez;
        rez.x = x + srcVector.x;
        rez.y = y + srcVector.y;
        return rez;
    }
    vec2& vec2::operator +=(const vec2& srcVector) {
        x += srcVector.x;
        y += srcVector.y;
        return *this;
    }
    vec2 vec2::operator *(float scalarValue) const {
        vec2 rez;
        rez.x = x * scalarValue;
        rez.y = y * scalarValue;
        return rez;
    }
    vec2 vec2::operator -(const vec2& srcVector) const {
        vec2 rez;
        rez.x = x - srcVector.x;
        rez.y = y - srcVector.y;
        return rez;

    }
    vec2& vec2::operator -=(const vec2& srcVector) {
        x -= srcVector.x;
        y -= srcVector.y;
        return *this;
    }
    vec2 vec2::operator -() const {
        vec2 rez;
        rez.x = -x;
        rez.y = -y;
        return rez;
    }
    float vec2::length() const {
        float f = sqrt(x * x + y * y);
        return f;
    }
    vec2& vec2::normalize() {
        float f = length();
        x = x / f;
        y = y / f;
        return *this;
    }
    float dotProduct(const vec2& v1, const vec2& v2) {
        return v1.x * v2.x + v2.y * v1.y;
    }
}