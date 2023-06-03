#include "vec3.h"

namespace egc {
    vec3& vec3::operator =(const vec3& srcVector) {
        x = srcVector.x;
        y = srcVector.y;
        z = srcVector.z;
        return *this;
    }
    vec3 vec3::operator +(const vec3& srcVector) const {
        vec3 rez;
        rez.x = x + srcVector.x;
        rez.y = y + srcVector.y;
        rez.z = z + srcVector.z;
        return rez;
    }
    vec3& vec3::operator +=(const vec3& srcVector) {
        x += srcVector.x;
        y += srcVector.y;
        z += srcVector.z;
        return *this;
    }
    vec3 vec3::operator *(float scalarValue) const {
        vec3 rez;
        rez.x = x * scalarValue;
        rez.y = y * scalarValue;
        rez.z = z * scalarValue;
        return rez;

    }
    vec3 vec3::operator -(const vec3& srcVector) const {
        vec3 rez;
        rez.x = x - srcVector.x;
        rez.y = y - srcVector.y;
        rez.z = z - srcVector.z;
        return rez;
    }
    vec3& vec3::operator -=(const vec3& srcVector) {
        x -= srcVector.x;
        y -= srcVector.y;
        z -= srcVector.z;
        return *this;
    }
    vec3 vec3::operator -() const {
        vec3 rez;
        rez.x = -x;
        rez.y = -y;
        rez.z = -z;
        return rez;
    }
    float vec3::length() const {
        float f = sqrt(x * x + y * y +z*z);
        return f;
    }
    vec3& vec3::normalize() {
        float f = length();
        x = x / f;
        y = y / f;
        z = z / f;
        return *this;
    }
    float dotProduct(const vec3& v1, const vec3& v2)
    {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }
    vec3 crossProduct(const vec3& v1, const vec3& v2) {
        vec3 rez;
        rez.x = v1.y * v2.z - v1.z * v2.y;
        rez.y = v1.z * v2.x - v1.x * v2.z;
        rez.z = v1.x * v2.y - v1.y * v2.x;
        return rez;
    }
}