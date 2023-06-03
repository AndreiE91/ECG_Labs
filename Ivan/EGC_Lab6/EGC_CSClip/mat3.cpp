#include "mat3.h"

namespace egc {

	float& mat3::at(int i, int j) {
		return matrixData[3 * j + i];
	}

	const float& mat3::at(int i, int j) const {
		return matrixData[3 * j + i];
	}

	mat3& mat3::operator =(const mat3& srcMatrix) {
		for(int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				this->at(i, j) = srcMatrix.at(i, j);
;			}
		return (*this);
	}
	mat3 mat3::operator *(float scalarValue) const {
		mat3 m;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				m.at(i, j) = this->at(i, j) * scalarValue;
		return m;
	}

	mat3 mat3::operator *(const mat3& srcMatrix) const {
		mat3 m;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				m.at(i, j) = this->at(i, 0) * srcMatrix.at(0, j) + this->at(i, 1) * srcMatrix.at(1, j) +
					this->at(i, 2) * srcMatrix.at(2, j);
			}
		return m;
	}
	
	vec3 mat3::operator *(const vec3& srcVector) const {
		vec3 v;
		v.x = this->at(0, 0) * srcVector.x + this->at(0, 1) * srcVector.y + this->at(0, 2) * srcVector.z;
		v.y = this->at(1, 0) * srcVector.x + this->at(1, 1) * srcVector.y + this->at(1, 2) * srcVector.z;
		v.z = this->at(2, 0) * srcVector.x + this->at(2, 1) * srcVector.y + this->at(2, 2) * srcVector.z;
		return v;
	}
	
	mat3 mat3::operator +(const mat3& srcMatrix) const {
		mat3 m;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				m.at(i, j) = this->at(i, j) + srcMatrix.at(i, j);
		return m;
	}
	
	float mat3::determinant() const {
		float x = 0.0;
		x = this->at(0, 0) * (this->at(1, 1) * this->at(2, 2) - this->at(1, 2) * this->at(2, 1)) -
			this->at(0, 1) * (this->at(1, 0) * this->at(2, 2) - this->at(1, 2) * this->at(2, 0)) +
			this->at(0, 2) * (this->at(1, 0) * this->at(2, 1) - this->at(1, 1) * this->at(2, 0));
		return x;
	}
	
	mat3 mat3::inverse() const {
		float deter = this->determinant();
		mat3 mRez;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				mRez.at(i, j) = ((this->at((j + 1) % 3, (i + 1) % 3) * this->at((j + 2) % 3, (i + 2) % 3)) - (this->at((j + 1) % 3, (i + 2) % 3) * this->at((j + 2) % 3, (i + 1) % 3))) / deter;
		return mRez;
	}
	
	mat3 mat3::transpose() const {
		mat3 m;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				m.at(i, j) = this->at(j, i);
		return m;
	}
}