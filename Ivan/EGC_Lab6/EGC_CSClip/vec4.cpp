#include "vec4.h"

namespace egc {
    vec4& vec4::operator =(const vec4& srcVector) {
        x = srcVector.x;
        y = srcVector.y;
        z = srcVector.z;
        w = srcVector.w;
        return *this;
    }
    vec4 vec4::operator +(const vec4& srcVector) const {
        vec4 a;
        a.x = x + srcVector.x;
        a.y = y + srcVector.y;
        a.z = z + srcVector.z;
        a.w = w + srcVector.w;
        return a;
    }
    vec4& vec4::operator +=(const vec4& srcVector) {
        x = x + srcVector.x;
        y = y + srcVector.y;
        z = z + srcVector.z;
        w = w + srcVector.w;
        return *this;
    }
    vec4 vec4::operator *(float scalarValue) const {
        vec4 a;
        a.x = x * scalarValue;
        a.y = y * scalarValue;
        a.z = z * scalarValue;
        a.w = w * scalarValue;
        return a;
    }
    vec4 vec4::operator -(const vec4& srcVector) const {
        vec4 a;
        a.x = x - srcVector.x;
        a.y = y - srcVector.y;
        a.z = z - srcVector.z;
        a.w = w - srcVector.w;
        return a;
    }
    vec4& vec4::operator -=(const vec4& srcVector) {
        x = x - srcVector.x;
        y = y - srcVector.y;
        z = z - srcVector.z;
        w = w - srcVector.w;
        return *this;
    }
    vec4 vec4::operator -() const {
        vec4 a;
        a = (*this) * (-1);
        return a;
    }
    float vec4::length() const {
        float a = sqrt(x * x + y * y + z * z + w * w);
        return a;
    }
    vec4& vec4::normalize() {
        float modul = length();
        x = x / modul;
        y = y / modul;
        z = z / modul;
        w = w / modul;
        return *this;
    }
}