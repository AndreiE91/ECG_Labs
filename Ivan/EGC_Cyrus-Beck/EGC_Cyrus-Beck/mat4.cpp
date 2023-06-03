#include <iostream>
#include "mat4.h"
#include "vec4.h"
#include "mat3.h"

namespace egc {
    mat4& mat4::operator =(const mat4& srcMatrix) {
        for (int i = 0; i < 16; i++)
        {
            this->matrixData[i] = srcMatrix.matrixData[i];
        }
        return *this;
    }
    mat4 mat4::operator *(float scalarValue) const {
        mat4 result;
        for (int i = 0; i < 16; i++) {
            result.matrixData[i] = this->matrixData[i] * scalarValue;
        }

        return result;
    }
    mat4 mat4::operator *(const mat4& srcMatrix) const {
        mat4 result;

        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 4; i++) {
                result.at(i, j) = 0;
                for (int k = 0; k < 4; k++) {
                    result.at(i, j) += this->at(i, k) * srcMatrix.at(k, j);
                }

            }
        }

        return result;
    }
    vec4 mat4::operator *(const vec4& srcVector) const {
        vec4 result;
        result.x = srcVector.x * this->at(0, 0) + srcVector.y * this->at(0, 1) + srcVector.z * this->at(0, 2) + srcVector.w * this->at(0, 3);
        result.y = srcVector.x * this->at(1, 0) + srcVector.y * this->at(1, 1) + srcVector.z * this->at(1, 2) + srcVector.w * this->at(1, 3);
        result.z = srcVector.x * this->at(2, 0) + srcVector.y * this->at(2, 1) + srcVector.z * this->at(2, 2) + srcVector.w * this->at(2, 3);
        result.w = srcVector.x * this->at(3, 0) + srcVector.y * this->at(3, 1) + srcVector.z * this->at(3, 2) + srcVector.w * this->at(3, 3);
        return result;
    }
    mat4 mat4::operator +(const mat4& srcMatrix) const {
        mat4 result;
        for (int i = 0; i < 16; i++)
        {
            result.matrixData[i] = this->matrixData[i] + srcMatrix.matrixData[i];
        }
        return result;
    }
    //get element by (row, column)
    float& mat4::at(int i, int j) {
        return this->matrixData[i + 4 * j];
    }
    const float& mat4::at(int i, int j) const {
        return this->matrixData[i + 4 * j];
    }
    float mat4::determinant() const {
        mat3 a, b, c, d;
        float aa, bb, cc, dd;
        a.at(0, 0) = this->at(1, 1);
        a.at(0, 1) = this->at(1, 2);
        a.at(0, 2) = this->at(1, 3);

        a.at(1, 0) = this->at(2, 1);
        a.at(1, 1) = this->at(2, 2);
        a.at(1, 2) = this->at(2, 3);

        a.at(2, 0) = this->at(3, 1);
        a.at(2, 1) = this->at(3, 2);
        a.at(2, 2) = this->at(3, 3);

        b.at(0, 0) = this->at(1, 0);
        b.at(0, 1) = this->at(1, 2);
        b.at(0, 2) = this->at(1, 3);

        b.at(1, 0) = this->at(2, 0);
        b.at(1, 1) = this->at(2, 2);
        b.at(1, 2) = this->at(2, 3);

        b.at(2, 0) = this->at(3, 0);
        b.at(2, 1) = this->at(3, 2);
        b.at(2, 2) = this->at(3, 3);

        c.at(0, 0) = this->at(1, 0);
        c.at(0, 1) = this->at(1, 1);
        c.at(0, 2) = this->at(1, 3);

        c.at(1, 0) = this->at(2, 0);
        c.at(1, 1) = this->at(2, 1);
        c.at(1, 2) = this->at(2, 3);

        c.at(2, 0) = this->at(3, 0);
        c.at(2, 1) = this->at(3, 1);
        c.at(2, 2) = this->at(3, 3);

        d.at(0, 0) = this->at(1, 0);
        d.at(0, 1) = this->at(1, 1);
        d.at(0, 2) = this->at(1, 2);

        d.at(1, 0) = this->at(2, 0);
        d.at(1, 1) = this->at(2, 1);
        d.at(1, 2) = this->at(2, 2);

        d.at(2, 0) = this->at(3, 0);
        d.at(2, 1) = this->at(3, 1);
        d.at(2, 2) = this->at(3, 2);

        aa = a.determinant();
        bb = b.determinant();
        cc = c.determinant();
        dd = d.determinant();

        return this->at(0, 0) * aa - this->at(0, 1) * bb + this->at(0, 2) * cc - this->at(0, 3) * dd;
        
    }
    mat4 mat4::inverse() const {
        mat4 result;
        mat4 tr;
        tr = this->transpose();
        float d = 1 / this->determinant();
        mat3 aux;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++)
            {
                int poz1 = 0;
                int poz2 = 0;
                for (int k = 0; k < 4; k++) {
                    for (int l = 0; l < 4; l++) {
                        if (k != i && l != j) {
                            aux.at(poz1, poz2) = tr.at(k, l);
                            poz2++;
                            if (poz2 == 3) {
                                poz1++;
                                poz2 = 0;
                            }
                        }
                    }
                }
                result.at(i, j) = aux.determinant();
                if ((i + j) % 2 == 1) {
                    result.at(i, j) = -result.at(i, j);
                }
            }
        }
        result = result.operator*(d);
        return result;
    }
    mat4 mat4::transpose() const {
        mat4 result;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                result.at(i, j) = this->at(j, i);
            }
        }
        return result;
    }
}