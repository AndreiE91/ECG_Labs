//
//  mat3.h
//  Lab3_TODO
//
//  Copyright © 2016 CGIS. All rights reserved.
//

#pragma once

#include <algorithm>
#include <iostream>
#include "vec3.h"

namespace egc {
    class mat3
    {
    public:
        //==============================================
        //matrixData is stored in column-major order
        //  m0  m3   m6  n0 n3 n6    m0n0+m3n1+m6n2  m0n3+m3n4+m6n5  m0n6+m3n7+m6n8
        //  m1  m4   m7  n1 n4 n7 => m1n0+m4n1+m7n2  m1n3+m4n4+m7n5  m1n6+m4n7+m7n8
        //  m2  m5   m8  n2 n5 n8    m2n0+m5n1+m8n2  m2n3+m5n4+m8n5  m2n6+m5n7+m8n8
        //
        //  matrixData[] = {m0, m1, m2,
        //                  m3, m4, m5,
        //                  m6, m7, m8}
        //==============================================
        float matrixData[9];
        
        //==============================================
        //constructors
        //==============================================
        
        //default constructor creates an identity matrix
        mat3()
        {
            for (int i = 0; i < 9; i++) {
                matrixData[i] = (i % 4) ? 0.0f : 1.0f;
            }
        }
        
        mat3(const float* srcMatrix)
        {
            std::copy(srcMatrix, srcMatrix + 9, matrixData);
        }
        
        //==============================================
        // TO BE IMPLEMENTED
        //==============================================
        mat3& operator =(const mat3& srcMatrix);
        mat3 operator *(float scalarValue) const;
        mat3 operator *(const mat3& srcMatrix) const;
        vec3 operator *(const vec3& srcVector) const;
        mat3 operator +(const mat3& srcMatrix) const;
        //get element by (row, column)
        float& at(int i, int j);
        const float& at(int i, int j) const;
        float determinant() const;
        mat3 inverse() const;
        mat3 transpose() const;
        
        //==============================================
        friend std::ostream& operator<< (std::ostream &out, const mat3& srcMatrix);
        
        bool operator ==(const mat3& srcMatrix) const
        {
            for (int i = 0; i < 9; i++)
                if (std::abs(matrixData[i] - srcMatrix.matrixData[i]) >= std::numeric_limits<float>::epsilon()) {
                    return false;
                }
            return true;
        }
    };
    
    inline std::ostream& operator<< (std::ostream &out, const mat3& srcMatrix)
    {
        for(int i = 0; i < 3; i++)
            out << srcMatrix.matrixData[i] << "\t" << srcMatrix.matrixData[i + 3] << "\t" << srcMatrix.matrixData[i + 6] << "\n";
        return out;
    };
}