#include "transform.h"

namespace egc {
    mat3 translate(const vec2 translateArray) {
        mat3 m;
        m.at(0, 0) = 1;
        m.at(1, 1) = 1;
        m.at(2, 2) = 1;
        m.at(0, 2) = translateArray.x;
        m.at(1, 2) = translateArray.y;
        return m;
    }
    
    mat3 translate(float tx, float ty) {
        mat3 m;
        m.at(0, 0) = 1;
        m.at(1, 1) = 1;
        m.at(2, 2) = 1;
        m.at(0, 2) = tx;
        m.at(1, 2) = ty;
        return m;
    }
    
    mat3 scale(const vec2 scaleArray) {
        mat3 m;
        m.at(0, 0) = scaleArray.x;
        m.at(1, 1) = scaleArray.y;
        m.at(2, 2) = 1;
        return m;
    }

    mat3 scale(float sx, float sy) {
        mat3 m;
        m.at(0, 0) = sx;
        m.at(1, 1) = sy;
        m.at(2, 2) = 1;
        return m;
    }

    mat3 rotate(float angle) {
        mat3 m;
        m.at(0, 0) = (float)cos((PI * angle)/180);
        m.at(0, 1) = (float)-sin((PI * angle) / 180);
        m.at(1, 0) = (float)sin((PI * angle) / 180);
        m.at(1, 1) = (float)cos((PI * angle) / 180);
        m.at(2, 2) = 1;
        return m;
    }

    mat4 translate(const vec3 translateArray) {
        mat4 m;
        m.at(0, 0) = 1;
        m.at(1, 1) = 1;
        m.at(2, 2) = 1;
        m.at(3, 3) = 1;
        m.at(0, 3) = translateArray.x;
        m.at(1, 3) = translateArray.y;
        m.at(2, 3) = translateArray.z;
        return m;
    }
    mat4 translate(float tx, float ty, float tz) {
        mat4 m;
        m.at(0, 0) = 1;
        m.at(1, 1) = 1;
        m.at(2, 2) = 1;
        m.at(3, 3) = 1;
        m.at(0, 3) = tx;
        m.at(1, 3) = ty;
        m.at(2, 3) = tz;
        return m;
    }

    mat4 scale(const vec3 scaleArray) {
        mat4 m;
        m.at(0, 0) = scaleArray.x;
        m.at(1, 1) = scaleArray.y;
        m.at(2, 2) = scaleArray.z;
        m.at(3, 3) = 1;
        return m;
    }
    mat4 scale(float sx, float sy, float sz) {
        mat4 m;
        m.at(0, 0) = sx;
        m.at(1, 1) = sy;
        m.at(2, 2) = sz;
        m.at(3, 3) = 1;
        return m;
    }

    mat4 rotateX(float angle) {
        mat4 m;
        m.at(0, 0) = 1;
        m.at(1, 1) = (float)cos((PI * angle) / 180);
        m.at(1, 2) = (float)-sin((PI * angle) / 180);
        m.at(2, 1) = (float)sin((PI * angle) / 180);
        m.at(2, 2) = (float)cos((PI * angle) / 180);
        m.at(3, 3) = 1;
        return m;
    }
    mat4 rotateY(float angle) {
        mat4 m;
        m.at(1, 1) = 1;
        m.at(0, 0) = (float)cos((PI * angle) / 180);
        m.at(2, 0) = (float)-sin((PI * angle) / 180);
        m.at(0, 2) = (float)sin((PI * angle) / 180);
        m.at(2, 2) = (float)cos((PI * angle) / 180);
        m.at(3, 3) = 1;
        return m;
    }
    mat4 rotateZ(float angle) {
        mat4 m;
        m.at(2, 2) = 1;
        m.at(0, 0) = (float)cos((PI * angle) / 180);
        m.at(0, 1) = (float)-sin((PI * angle) / 180);
        m.at(1, 0) = (float)sin((PI * angle) / 180);
        m.at(1, 1) = (float)cos((PI * angle) / 180);
        m.at(3, 3) = 1;
        return m;
    }

}