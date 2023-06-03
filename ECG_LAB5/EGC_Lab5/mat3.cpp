#include "mat3.h"

namespace egc {
    mat3& mat3::operator =(const mat3& srcMatrix) {
        this->matrixData[0] = srcMatrix.matrixData[0];
        this->matrixData[1] = srcMatrix.matrixData[1];
        this->matrixData[2] = srcMatrix.matrixData[2];
        this->matrixData[3] = srcMatrix.matrixData[3];
        this->matrixData[4] = srcMatrix.matrixData[4];
        this->matrixData[5] = srcMatrix.matrixData[5];
        this->matrixData[6] = srcMatrix.matrixData[6];
        this->matrixData[7] = srcMatrix.matrixData[7];
        this->matrixData[8] = srcMatrix.matrixData[8];

        return *this;
    }
    mat3 mat3::operator *(float scalarValue) const {
        float newMat[] = {this->matrixData[0] * scalarValue, this->matrixData[1] * scalarValue, this->matrixData[2] * scalarValue, 
                          this->matrixData[3] * scalarValue, this->matrixData[4] * scalarValue, this->matrixData[5] * scalarValue,
                          this->matrixData[6] * scalarValue, this->matrixData[7] * scalarValue, this->matrixData[8] * scalarValue};
        return mat3(newMat);

    }

    //==============================================
        //matrixData is stored in column-major order
        //  m0  m3   m6  n0 n3 n6    m0n0+m3n1+m6n2  m0n3+m3n4+m6n5  m0n6+m3n7+m6n8  fg7
        //  m1  m4   m7  n1 n4 n7 => m1n0+m4n1+m7n2  m1n3+m4n4+m7n5  m1n6+m4n7+m7n8    
        //  m2  m5   m8  n2 n5 n8    m2n0+m5n1+m8n2  m2n3+m5n4+m8n5  m2n6+m5n7+m8n8
        //
        //  matrixData[] = {m0, m1, m2,
        //                  m3, m4, m5,
        //                  m6, m7, m8}
        //==============================================
    mat3 mat3::operator *(const mat3& srcMatrix) const {
        float newMat[] = { this->matrixData[0] * srcMatrix.matrixData[0] + this->matrixData[3] * srcMatrix.matrixData[1] + this->matrixData[6] * srcMatrix.matrixData[2],
                           this->matrixData[0] * srcMatrix.matrixData[3] + this->matrixData[3] * srcMatrix.matrixData[4] + this->matrixData[6] * srcMatrix.matrixData[5],
                           this->matrixData[0] * srcMatrix.matrixData[6] + this->matrixData[3] * srcMatrix.matrixData[7] + this->matrixData[6] * srcMatrix.matrixData[8],

                           this->matrixData[1] * srcMatrix.matrixData[0] + this->matrixData[4] * srcMatrix.matrixData[1] + this->matrixData[7] * srcMatrix.matrixData[2],
                           this->matrixData[1] * srcMatrix.matrixData[3] + this->matrixData[4] * srcMatrix.matrixData[4] + this->matrixData[7] * srcMatrix.matrixData[5],
                           this->matrixData[1] * srcMatrix.matrixData[6] + this->matrixData[4] * srcMatrix.matrixData[7] + this->matrixData[7] * srcMatrix.matrixData[8],

                           this->matrixData[2] * srcMatrix.matrixData[0] + this->matrixData[5] * srcMatrix.matrixData[1] + this->matrixData[8] * srcMatrix.matrixData[2],
                           this->matrixData[2] * srcMatrix.matrixData[3] + this->matrixData[5] * srcMatrix.matrixData[4] + this->matrixData[8] * srcMatrix.matrixData[5],
                           this->matrixData[2] * srcMatrix.matrixData[6] + this->matrixData[5] * srcMatrix.matrixData[7] + this->matrixData[8] * srcMatrix.matrixData[8],
        };
        return mat3(newMat).transpose();
    }
    vec3 mat3::operator *(const vec3& srcVector) const {
        return vec3(this->matrixData[0] * srcVector.x + this->matrixData[3] * srcVector.y + this->matrixData[6] * srcVector.z,
                    this->matrixData[1] * srcVector.x + this->matrixData[4] * srcVector.y + this->matrixData[7] * srcVector.z,
                    this->matrixData[2] * srcVector.x + this->matrixData[5] * srcVector.y + this->matrixData[8] * srcVector.z);
    }
    mat3 mat3::operator +(const mat3& srcMatrix) const {
        float newMat[] = { this->matrixData[0] + srcMatrix.matrixData[0], this->matrixData[1] + srcMatrix.matrixData[1], this->matrixData[2] + srcMatrix.matrixData[2],
                          this->matrixData[3] + srcMatrix.matrixData[3], this->matrixData[4] + srcMatrix.matrixData[4], this->matrixData[5] + srcMatrix.matrixData[5],
                          this->matrixData[6] + srcMatrix.matrixData[6], this->matrixData[7] + srcMatrix.matrixData[7], this->matrixData[8] + srcMatrix.matrixData[8] };
        return mat3(newMat);
    }
    //get element by (row, column)
    float& mat3::at(int i, int j) {
        return this->matrixData[i + 3 * j];
    }
    const float& mat3::at(int i, int j) const {
        return this->matrixData[i + 3 * j];
    }
    float mat3::determinant() const {
        return(this->matrixData[0]* this->matrixData[4]* this->matrixData[8] + this->matrixData[1] * this->matrixData[5] * this->matrixData[6] +
            this->matrixData[2] * this->matrixData[3] * this->matrixData[7] - this->matrixData[2] * this->matrixData[4] * this->matrixData[6] -
            this->matrixData[0] * this->matrixData[5] * this->matrixData[7] - this->matrixData[1] * this->matrixData[3] * this->matrixData[8]);
    }
    mat3 mat3::inverse() const {
        if (this->determinant() == 0) {
            printf("Zero determinant matrix has no inverse\n");
            return NULL;
        }
        float tempMat[3][6] = { {this->matrixData[0], this->matrixData[3], this->matrixData[6], 1, 0, 0},
                                {this->matrixData[1], this->matrixData[4], this->matrixData[7], 0, 1, 0}, 
                                {this->matrixData[2], this->matrixData[5], this->matrixData[8], 0, 0, 1}};
        /* Applying Gauss Jordan Elimination */
        for (int i = 0; i < 3; i++)
        {
            if (tempMat[i][i] == 0.0)
            {
                printf("Mathematical Error!");
                exit(0);
            }
            for (int j = 0; j < 3; j++)
            {
                if (i != j)
                {
                    float ratio = 1.0 * tempMat[j][i] / tempMat[i][i];
                    for (int k = 0; k < 6; k++)
                    {
                        tempMat[j][k] = tempMat[j][k] - ratio * tempMat[i][k];
                    }
                }
            }
        }
        /* Row Operation to Make Principal Diagonal to 1 */
        for (int i = 0; i < 3; i++)
        {
            for (int j = 3; j < 6; j++)
            {
                tempMat[i][j] = 1.0 * tempMat[i][j] / tempMat[i][i];
            }
        }
        float inverseMat[9];
        int count = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 3; j < 6; j++) {
                inverseMat[count] = tempMat[i][j];
                ++count;
            }
        }
        return mat3(inverseMat).transpose();
    }
    mat3 mat3::transpose() const {
        float newMat[] = {this->matrixData[0], this->matrixData[3], this->matrixData[6],
                          this->matrixData[1], this->matrixData[4], this->matrixData[7],
                          this->matrixData[2], this->matrixData[5], this->matrixData[8] 
        };
        return mat3(newMat);
    }
}