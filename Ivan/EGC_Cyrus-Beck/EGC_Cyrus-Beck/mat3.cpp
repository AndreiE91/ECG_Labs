#include <iostream>
#include "mat3.h"
#include "vec3.h"

namespace egc {

    mat3& mat3::operator =(const mat3& srcMatrix) {
        
        for (int i = 0; i < 9; i++)
        {
            this->matrixData[i] = srcMatrix.matrixData[i];
        }
        return *this;
    }
    
    mat3 mat3::operator *(float scalarValue) const{

        mat3 result;
        for (int i = 0; i < 9; i++) {
            result.matrixData[i] = this->matrixData[i] * scalarValue;
        }

        return result;
    }
    mat3 mat3::operator *(const mat3& srcMatrix) const {
        mat3 result;
       

        for (int j = 0; j < 3; j++) {
            for (int i = 0; i < 3; i++) {
                result.at(i, j) = 0;
                for (int k = 0; k < 3; k++) {
                    result.at(i, j) += this->at(i, k) * srcMatrix.at(k, j);
                }

            }
        }
        
        return result;
    }
    
    vec3 mat3::operator *(const vec3& srcVector) const {
        vec3 result;
        result.x = srcVector.x * this->at(0, 0) + srcVector.y * this->at(0, 1) + srcVector.z * this->at(0, 2);
        result.y = srcVector.x * this->at(1, 0) + srcVector.y * this->at(1, 1) + srcVector.z * this->at(1, 2);
        result.z = srcVector.x * this->at(2, 0) + srcVector.y * this->at(2, 1) + srcVector.z * this->at(2, 2);
        return result;
    }
    
    
    mat3 mat3::operator +(const mat3& srcMatrix) const {
        mat3 result;
        for (int i = 0; i < 9; i++)
        {
            result.matrixData[i] = this->matrixData[i] + srcMatrix.matrixData[i];
        }
        return result;
    }
    
    float& mat3::at(int i, int j) {

        return this->matrixData[i+j*3];
    }
    const float& mat3::at(int i, int j) const {
        return this->matrixData[i+j*3];
    }
    
    float mat3::determinant() const {
        
        return this->at(1, 1) * this->at(2, 2) * this->at(0, 0) + this->at(0, 2) * this->at(1, 0) * this->at(2, 1) +
            this->at(0, 1) * this->at(1, 2) * this->at(2, 0) - this->at(0, 2) * this->at(1, 1) * this->at(2, 0) - this->at(0, 1) * this->at(1, 0) *
            this->at(2, 2) - this->at(0, 0) * this->at(2, 1) * this->at(1, 2);
        
    }
    mat3 mat3::inverse() const {
        mat3 result;
        float d = 1/ this->determinant();
        mat3 tr = this->transpose();
        result.at(0, 0) = tr.at(1, 1) * tr.at(2, 2) - tr.at(1, 2) * tr.at(2, 1);
        result.at(0, 1) = -( tr.at(1, 0) * tr.at(2, 2) - tr.at(2, 0) * tr.at(1, 2));
        result.at(0, 2) = tr.at(1, 0) * tr.at(2, 1) - tr.at(1, 1) * tr.at(2, 0);

        result.at(1, 0) = -(tr.at(0, 1) * tr.at(2, 2) - tr.at(2, 1) * tr.at(0, 2));
        result.at(1, 1) = tr.at(0, 0) * tr.at(2, 2) - tr.at(0, 2) * tr.at(2, 0);
        result.at(1, 2) = -(tr.at(0, 0) * tr.at(2, 1) - tr.at(2, 0) * tr.at(0, 1));

        result.at(2, 0) = tr.at(0, 1) * tr.at(1, 2) - tr.at(1, 1) * tr.at(0, 2);
        result.at(2, 1) = -(tr.at(0, 0) * tr.at(1, 2) - tr.at(1, 0) * tr.at(0, 2));
        result.at(2, 2) = tr.at(1, 1) * tr.at(0, 0) - tr.at(1, 0) * tr.at(0, 1);
       
        result = result.operator*(d);
        return result;
    }
    mat3 mat3::transpose() const {
        mat3 result;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                result.at(i, j) = this->at(j, i);
            }
        }
        return result;
    }
    

    
}