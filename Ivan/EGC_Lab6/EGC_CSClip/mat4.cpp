#include "mat4.h"
#include "mat3.h"

namespace egc {
    mat4& mat4::operator =(const mat4& srcMatrix) {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++) {
                this->at(i, j) = srcMatrix.at(i, j);
            }
        return (*this);
    }
    mat4 mat4::operator *(float scalarValue) const {
        mat4 m;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                m.at(i, j) = this->at(i, j) * scalarValue;
        return m;
    }
    mat4 mat4::operator *(const mat4& srcMatrix) const {
        mat4 m;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++) {
                m.at(i, j) = this->at(i, 0) * srcMatrix.at(0, j) + this->at(i, 1) * srcMatrix.at(1, j) +
                    this->at(i, 2) * srcMatrix.at(2, j) + this->at(i, 3) * srcMatrix.at(3, j);
            }
        return m;
    }
    vec4 mat4::operator *(const vec4& srcVector) const {
        vec4 v;
        v.x = this->at(0, 0) * srcVector.x + this->at(0, 1) * srcVector.y + this->at(0, 2) * srcVector.z + this->at(0, 3) * srcVector.w;
        v.y = this->at(1, 0) * srcVector.x + this->at(1, 1) * srcVector.y + this->at(1, 2) * srcVector.z + this->at(1, 3) * srcVector.w;
        v.z = this->at(2, 0) * srcVector.x + this->at(2, 1) * srcVector.y + this->at(2, 2) * srcVector.z + this->at(2, 3) * srcVector.w;
        v.w = this->at(3, 0) * srcVector.x + this->at(3, 1) * srcVector.y + this->at(3, 2) * srcVector.z + this->at(3, 3) * srcVector.w;
        return v;
    }
    mat4 mat4::operator +(const mat4& srcMatrix) const {
        mat4 m;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                m.at(i, j) = this->at(i, j) + srcMatrix.at(i, j);
        return m;
    }
    float& mat4::at(int i, int j) {
        return matrixData[4 * j + i];
    }
    const float& mat4::at(int i, int j) const {
        return matrixData[4 * j + i];
    }
    
    float mat4::determinant() const {
        float determ = 0.0;
        mat3 m1, m2, m3, m4;
        for (int i = 1; i < 4; i++)
            for (int j = 0; j < 4; j++){
                if (j != 0)
                    m1.at(i - 1, j - 1) = this->at(i, j);
                if (j < 1)
                    m2.at(i - 1, j) = this->at(i, j);
                if (j > 1)
                    m2.at(i - 1, j - 1) = this->at(i, j);
                if (j < 2)
                    m3.at(i - 1, j) = this->at(i, j);
                if (j > 2)
                    m3.at(i - 1, j - 1) = this->at(i, j);
                if (j < 3)
                    m4.at(i - 1, j) = this->at(i, j);
                if (j > 3)
                    m4.at(i - 1, j - 1) = this->at(i, j);
            }
        float det1, det2, det3, det4;
        det1 = m1.determinant() * this->at(0, 0);
        det2 = m2.determinant() * this->at(0, 1);
        det3 = m3.determinant() * this->at(0, 2);
        det4 = m4.determinant() * this->at(0, 3);
        determ = det1 - det2 + det3 - det4;
        return determ;
    }
    

    mat4 mat4::inverse() const {
        mat4 result;
        float det = 1 / this->determinant();
        mat4 trans = this->transpose();

        result.at(0, 0) = trans.at(1, 1) * trans.at(2, 2) * trans.at(3, 3) + trans.at(2, 1) * trans.at(3, 2) * trans.at(1, 3) + trans.at(1, 2) * trans.at(2, 3) * trans.at(3, 1) - trans.at(1, 3) * trans.at(2, 2) * trans.at(3, 1) - trans.at(2, 1) * trans.at(1, 2) * trans.at(3, 3) - trans.at(1, 1) * trans.at(3, 2) * trans.at(2, 3);
        result.at(0, 1) = -(trans.at(1, 0) * trans.at(2, 2) * trans.at(3, 3) + trans.at(2, 0) * trans.at(3, 2) * trans.at(1, 3) + trans.at(1, 2) * trans.at(2, 3) * trans.at(3, 0) - trans.at(1, 3) * trans.at(2, 2) * trans.at(3, 0) - trans.at(2, 0) * trans.at(1, 2) * trans.at(3, 3) - trans.at(1, 0) * trans.at(3, 2) * trans.at(2, 3));
        result.at(0, 2) = trans.at(1, 0) * trans.at(2, 1) * trans.at(3, 3) + trans.at(2, 0) * trans.at(3, 1) * trans.at(1, 3) + trans.at(1, 1) * trans.at(2, 3) * trans.at(3, 0) - trans.at(1, 3) * trans.at(2, 1) * trans.at(3, 0) - trans.at(2, 0) * trans.at(1, 1) * trans.at(3, 3) - trans.at(1, 0) * trans.at(3, 1) * trans.at(2, 3);
        result.at(0, 3) = -(trans.at(1, 0) * trans.at(2, 1) * trans.at(3, 2) + trans.at(2, 0) * trans.at(3, 1) * trans.at(1, 2) + trans.at(1, 1) * trans.at(2, 2) * trans.at(3, 0) - trans.at(1, 2) * trans.at(2, 1) * trans.at(3, 0) - trans.at(2, 0) * trans.at(1, 1) * trans.at(3, 2) - trans.at(1, 0) * trans.at(3, 1) * trans.at(2, 2));

        result.at(1, 0) = -(trans.at(0, 1) * trans.at(2, 2) * trans.at(3, 3) + trans.at(2, 1) * trans.at(3, 2) * trans.at(0, 3) + trans.at(0, 2) * trans.at(2, 3) * trans.at(3, 1) - trans.at(0, 3) * trans.at(2, 2) * trans.at(3, 1) - trans.at(2, 1) * trans.at(0, 2) * trans.at(3, 3) - trans.at(0, 1) * trans.at(3, 2) * trans.at(2, 3));
        result.at(1, 1) = (trans.at(0, 0) * trans.at(2, 2) * trans.at(3, 3) + trans.at(2, 0) * trans.at(3, 2) * trans.at(0, 3) + trans.at(0, 2) * trans.at(2, 3) * trans.at(3, 0) - trans.at(0, 3) * trans.at(2, 2) * trans.at(3, 0) - trans.at(2, 0) * trans.at(0, 2) * trans.at(3, 3) - trans.at(0, 0) * trans.at(3, 2) * trans.at(2, 3));
        result.at(1, 2) = -(trans.at(0, 0) * trans.at(2, 1) * trans.at(3, 3) + trans.at(2, 0) * trans.at(3, 1) * trans.at(0, 3) + trans.at(0, 1) * trans.at(2, 3) * trans.at(3, 0) - trans.at(0, 3) * trans.at(2, 1) * trans.at(3, 0) - trans.at(2, 0) * trans.at(0, 1) * trans.at(3, 3) - trans.at(0, 0) * trans.at(3, 1) * trans.at(2, 3));
        result.at(1, 3) = (trans.at(0, 0) * trans.at(2, 1) * trans.at(3, 2) + trans.at(2, 0) * trans.at(3, 1) * trans.at(0, 2) + trans.at(0, 1) * trans.at(2, 2) * trans.at(3, 0) - trans.at(0, 2) * trans.at(2, 1) * trans.at(3, 0) - trans.at(2, 0) * trans.at(0, 1) * trans.at(3, 2) - trans.at(0, 0) * trans.at(3, 1) * trans.at(2, 2));

        result.at(2, 0) = trans.at(0, 1) * trans.at(1, 2) * trans.at(3, 3) + trans.at(1, 1) * trans.at(3, 2) * trans.at(0, 3) + trans.at(0, 2) * trans.at(1, 3) * trans.at(3, 1) - trans.at(0, 3) * trans.at(1, 2) * trans.at(3, 1) - trans.at(1, 1) * trans.at(0, 2) * trans.at(3, 3) - trans.at(0, 1) * trans.at(3, 2) * trans.at(1, 3);
        result.at(2, 1) = -(trans.at(0, 0) * trans.at(1, 2) * trans.at(3, 3) + trans.at(1, 0) * trans.at(3, 2) * trans.at(0, 3) + trans.at(0, 2) * trans.at(1, 3) * trans.at(3, 0) - trans.at(0, 3) * trans.at(1, 2) * trans.at(3, 0) - trans.at(1, 0) * trans.at(0, 2) * trans.at(3, 3) - trans.at(0, 0) * trans.at(3, 2) * trans.at(1, 3));
        result.at(2, 2) = trans.at(0, 0) * trans.at(1, 1) * trans.at(3, 3) + trans.at(1, 0) * trans.at(3, 1) * trans.at(0, 3) + trans.at(0, 1) * trans.at(1, 3) * trans.at(3, 0) - trans.at(0, 3) * trans.at(1, 1) * trans.at(3, 0) - trans.at(1, 0) * trans.at(0, 1) * trans.at(3, 3) - trans.at(0, 0) * trans.at(3, 1) * trans.at(1, 3);
        result.at(2, 3) = -(trans.at(0, 0) * trans.at(1, 1) * trans.at(3, 2) + trans.at(1, 0) * trans.at(3, 1) * trans.at(0, 2) + trans.at(0, 1) * trans.at(1, 2) * trans.at(3, 0) - trans.at(0, 2) * trans.at(1, 1) * trans.at(3, 0) - trans.at(1, 0) * trans.at(0, 1) * trans.at(3, 2) - trans.at(0, 0) * trans.at(3, 1) * trans.at(1, 2));

        result.at(3, 0) = -(trans.at(0, 1) * trans.at(1, 2) * trans.at(2, 3) + trans.at(1, 1) * trans.at(2, 2) * trans.at(0, 3) + trans.at(0, 2) * trans.at(1, 3) * trans.at(2, 1) - trans.at(0, 3) * trans.at(1, 2) * trans.at(2, 1) - trans.at(1, 1) * trans.at(0, 2) * trans.at(2, 3) - trans.at(0, 1) * trans.at(2, 2) * trans.at(1, 3));
        result.at(3, 1) = (trans.at(0, 0) * trans.at(1, 2) * trans.at(2, 3) + trans.at(1, 0) * trans.at(2, 2) * trans.at(0, 3) + trans.at(0, 2) * trans.at(1, 3) * trans.at(2, 0) - trans.at(0, 3) * trans.at(1, 2) * trans.at(2, 0) - trans.at(1, 0) * trans.at(0, 2) * trans.at(2, 3) - trans.at(0, 0) * trans.at(2, 2) * trans.at(1, 3));
        result.at(3, 2) = -(trans.at(0, 0) * trans.at(1, 1) * trans.at(2, 3) + trans.at(1, 0) * trans.at(2, 1) * trans.at(0, 3) + trans.at(0, 1) * trans.at(1, 3) * trans.at(2, 0) - trans.at(0, 3) * trans.at(1, 1) * trans.at(2, 0) - trans.at(1, 0) * trans.at(0, 1) * trans.at(2, 3) - trans.at(0, 0) * trans.at(2, 1) * trans.at(1, 3));
        result.at(3, 3) = (trans.at(0, 0) * trans.at(1, 1) * trans.at(2, 2) + trans.at(1, 0) * trans.at(2, 1) * trans.at(0, 2) + trans.at(0, 1) * trans.at(1, 2) * trans.at(2, 0) - trans.at(0, 2) * trans.at(1, 1) * trans.at(2, 0) - trans.at(1, 0) * trans.at(0, 1) * trans.at(2, 2) - trans.at(0, 0) * trans.at(2, 1) * trans.at(1, 2));

        result = result * det;

        return result;
    }
    
    mat4 mat4::transpose() const {
        mat4 m;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                m.at(i, j) = this->at(j, i);
        return m;
    }
    
}