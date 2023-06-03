#include "vec3.h"

namespace egc {
    vec3& vec3::operator =(const vec3& srcVector) {
        x = srcVector.x;
        y = srcVector.y;
        z = srcVector.z;
        return *this;
    }
    vec3 vec3::operator +(const vec3& srcVector) const {
        vec3 a;
        a.x = x + srcVector.x;
        a.y = y + srcVector.y;
        a.z = z + srcVector.z;
        return a;
    }
    vec3& vec3::operator +=(const vec3& srcVector) {
        x = x + srcVector.x;
        y = y + srcVector.y;
        z = z + srcVector.z;
        return *this;
    }
    vec3 vec3::operator *(float scalarValue) const {
        vec3 a;
        a.x = x * scalarValue;
        a.y = y * scalarValue;
        a.z = z * scalarValue;
        return a;
    }
    vec3 vec3::operator -(const vec3& srcVector) const {
        vec3 a;
        a.x = x - srcVector.x;
        a.y = y - srcVector.y;
        a.z = z - srcVector.z;
        return a;
    }
    vec3& vec3::operator -=(const vec3& srcVector) {
        x = x - srcVector.x;
        y = y - srcVector.y;
        z = z - srcVector.z;
        return *this;
    }
    vec3 vec3::operator -() const {
        vec3 a;
        a = (*this) * (-1);
        return a;
    }
    float vec3::length() const {
        float a = sqrt(x * x + y * y + z * z);
        return a;
    }
    vec3& vec3::normalize() {
        float modul = length();
        x = x / modul;
        y = y / modul;
        z = z / modul;
        return *this;
    }

    float dotProduct(const vec3& v1, const vec3& v2) {
        float a;
        a = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
        return a;
    }
    vec3 crossProduct(const vec3& v1, const vec3& v2) {
        vec3 a;
        a.x = v1.y * v2.z - v1.z * v2.y;
        a.y = v1.z * v2.x - v1.x * v2.z;
        a.z = v1.x * v2.y - v1.y * v2.x;
        return a;
    }

}