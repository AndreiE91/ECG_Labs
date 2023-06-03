#include "mat4.h"

namespace egc {
    mat4& mat4::operator =(const mat4& srcMatrix) {
        this->matrixData[0] = srcMatrix.matrixData[0];
        this->matrixData[1] = srcMatrix.matrixData[1];
        this->matrixData[2] = srcMatrix.matrixData[2];
        this->matrixData[3] = srcMatrix.matrixData[3];
        this->matrixData[4] = srcMatrix.matrixData[4];
        this->matrixData[5] = srcMatrix.matrixData[5];
        this->matrixData[6] = srcMatrix.matrixData[6];
        this->matrixData[7] = srcMatrix.matrixData[7];
        this->matrixData[8] = srcMatrix.matrixData[8];
        this->matrixData[9] = srcMatrix.matrixData[9];
        this->matrixData[10] = srcMatrix.matrixData[10];
        this->matrixData[11] = srcMatrix.matrixData[11];
        this->matrixData[12] = srcMatrix.matrixData[12];
        this->matrixData[13] = srcMatrix.matrixData[13];
        this->matrixData[14] = srcMatrix.matrixData[14];
        this->matrixData[15] = srcMatrix.matrixData[15];
        return *this;
    }
    mat4 mat4::operator *(float scalarValue) const {
        float newMat[] = { this->matrixData[0] * scalarValue, this->matrixData[4] * scalarValue, this->matrixData[8] * scalarValue, this->matrixData[12] * scalarValue,
                          this->matrixData[1] * scalarValue, this->matrixData[5] * scalarValue, this->matrixData[9] * scalarValue, this->matrixData[13] * scalarValue,
                          this->matrixData[2] * scalarValue, this->matrixData[6] * scalarValue, this->matrixData[10] * scalarValue, this->matrixData[14] * scalarValue,
                          this->matrixData[3] * scalarValue, this->matrixData[7] * scalarValue, this->matrixData[11] * scalarValue, this->matrixData[15] * scalarValue
        };
        return mat4(newMat).transpose();
    }
    mat4 mat4::operator *(const mat4& srcMatrix) const {
        float newMat[16];
        int count = 0;
        int tempSum = 0;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                for (int m = 0; m < 4; ++m) {
                    tempSum += this->at(i, m) * srcMatrix.at(m, j);
                }
                newMat[count] = tempSum;
                tempSum = 0;
                ++count;
            }
        }
    return mat4(newMat).transpose();
    }
    vec4 mat4::operator *(const vec4& srcVector) const {
        return vec4(this->matrixData[0] * srcVector.x + this->matrixData[4] * srcVector.y + this->matrixData[8] * srcVector.z + this->matrixData[12] * srcVector.w,
            this->matrixData[1] * srcVector.x + this->matrixData[5] * srcVector.y + this->matrixData[9] * srcVector.z + this->matrixData[13] * srcVector.w,
            this->matrixData[2] * srcVector.x + this->matrixData[6] * srcVector.y + this->matrixData[10] * srcVector.z + this->matrixData[14] * srcVector.w,
            this->matrixData[3] * srcVector.x + this->matrixData[7] * srcVector.y + this->matrixData[11] * srcVector.z + this->matrixData[15] * srcVector.w
        );
    }
    mat4 mat4::operator +(const mat4& srcMatrix) const {
        float newMat[] = { this->matrixData[0] + srcMatrix.matrixData[0], this->matrixData[1] + srcMatrix.matrixData[1], this->matrixData[2] + srcMatrix.matrixData[2], +this->matrixData[3] + srcMatrix.matrixData[3],
                          this->matrixData[4] + srcMatrix.matrixData[4], this->matrixData[5] + srcMatrix.matrixData[5], this->matrixData[6] + srcMatrix.matrixData[6], this->matrixData[7] + srcMatrix.matrixData[7],
                          this->matrixData[6] + srcMatrix.matrixData[6], this->matrixData[7] + srcMatrix.matrixData[7], this->matrixData[10] + srcMatrix.matrixData[10], this->matrixData[11] + srcMatrix.matrixData[11],
                          this->matrixData[12] + srcMatrix.matrixData[12], this->matrixData[13] + srcMatrix.matrixData[13], this->matrixData[14] + srcMatrix.matrixData[14], this->matrixData[15] + srcMatrix.matrixData[15]
        };
        return mat4(newMat);
    }
    //get element by (row, column)
    float& mat4::at(int i, int j) {
        return this->matrixData[i + 4 * j];
    }
    const float& mat4::at(int i, int j) const {
        return this->matrixData[i + 4 * j];
    }
    float mat4::determinant() const {
        return(this->matrixData[0] * (this->matrixData[5] * this->matrixData[10] * this->matrixData[15] + this->matrixData[6] * this->matrixData[11] * this->matrixData[13] + this->matrixData[9] * this->matrixData[14] * this->matrixData[7] - this->matrixData[13] * this->matrixData[10] * this->matrixData[7] - this->matrixData[11] * this->matrixData[14] * this->matrixData[5] - this->matrixData[6] * this->matrixData[9] * this->matrixData[15])
             - this->matrixData[1] * (this->matrixData[4] * this->matrixData[10] * this->matrixData[15] + this->matrixData[6] * this->matrixData[11] * this->matrixData[12] + this->matrixData[7] * this->matrixData[8] * this->matrixData[14] - this->matrixData[7] * this->matrixData[10] * this->matrixData[12] - this->matrixData[4] * this->matrixData[11] * this->matrixData[14] - this->matrixData[6] * this->matrixData[8] * this->matrixData[15])
             + this->matrixData[2] * (this->matrixData[4] * this->matrixData[9] * this->matrixData[15] + this->matrixData[5] * this->matrixData[11] * this->matrixData[12] + this->matrixData[7] * this->matrixData[8] * this->matrixData[13] - this->matrixData[7] * this->matrixData[9] * this->matrixData[12] - this->matrixData[4] * this->matrixData[11] * this->matrixData[13] - this->matrixData[5] * this->matrixData[8] * this->matrixData[15])
             - this->matrixData[3] * (this->matrixData[4] * this->matrixData[9] * this->matrixData[14] + this->matrixData[5] * this->matrixData[10] * this->matrixData[12] + this->matrixData[6] * this->matrixData[8] * this->matrixData[13] - this->matrixData[6] * this->matrixData[9] * this->matrixData[12] - this->matrixData[4] * this->matrixData[10] * this->matrixData[13] - this->matrixData[5] * this->matrixData[8] * this->matrixData[14]));
    }
    mat4 mat4::inverse() const {
        if (this->determinant() == 0) {
            printf("Zero determinant matrix has no inverse\n");
            return NULL;
        }
        float tempMat[4][8] = { {this->matrixData[0], this->matrixData[4], this->matrixData[8], this->matrixData[12], 1, 0, 0, 0},
                                {this->matrixData[1], this->matrixData[5], this->matrixData[9], this->matrixData[13], 0, 1, 0, 0},
                                {this->matrixData[2], this->matrixData[6], this->matrixData[10], this->matrixData[14], 0, 0, 1, 0},
                                {this->matrixData[3], this->matrixData[7], this->matrixData[11], this->matrixData[15], 0, 0, 0, 1}

        };
        /* Applying Gauss Jordan Elimination */
        for (int i = 0; i < 4; i++)
        {
            if (tempMat[i][i] == 0.0)
            {
                printf("Mathematical Error!");
                exit(0);
            }
            for (int j = 0; j < 4; j++)
            {
                if (i != j)
                {
                    float ratio = 1.0 * tempMat[j][i] / tempMat[i][i];
                    for (int k = 0; k < 8; k++)
                    {
                        tempMat[j][k] = tempMat[j][k] - ratio * tempMat[i][k];
                    }
                }
            }
        }
        /* Row Operation to Make Principal Diagonal to 1 */
        for (int i = 0; i < 4; i++)
        {
            for (int j = 4; j < 8; j++)
            {
                tempMat[i][j] = 1.0 * tempMat[i][j] / tempMat[i][i];
            }
        }
        float inverseMat[16];
        int count = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 4; j < 8; j++) {
                inverseMat[count] = tempMat[i][j];
                ++count;
            }
        }
        return mat4(inverseMat).transpose();
    }
    //==============================================
        //matrixData is stored in column-major order
        //  m00  m04   m08  m12
        //  m01  m05   m09  m13
        //  m02  m06   m10  m14
        //  m03  m07   m11  m15
        //
        //  matrixData[] = {m00, m01, m02, m03,
        //                  m04, m05, m06, m07,
        //                  m08, m09, m10, m11,
        //                  m12, m13, m14, m15}
        //==============================================
    mat4 mat4::transpose() const {
        float newMat[] = { this->matrixData[0], this->matrixData[4], this->matrixData[8], this->matrixData[12],
                           this->matrixData[1], this->matrixData[5], this->matrixData[9], this->matrixData[13],
                           this->matrixData[2], this->matrixData[6], this->matrixData[10], this->matrixData[14],
                           this->matrixData[3], this->matrixData[7], this->matrixData[11], this->matrixData[15],

        };
        return mat4(newMat);
    }
}