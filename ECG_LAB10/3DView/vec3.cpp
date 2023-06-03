#include "vec3.h"

namespace egc {


	vec3& vec3::operator =(const vec3& srcVector) {

		x = srcVector.x;
		y = srcVector.y;
		z = srcVector.z;
		return *this;
	}
	vec3 vec3::operator +(const vec3& srcVector) const {
		vec3 a;  //se apeleaza constructorul default
		a.x = this->x + srcVector.x;
		a.y = this->y + srcVector.y;
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
		vec3 a;  //se apeleaza constructorul default
		a.x = this->x - srcVector.x;
		a.y = this->y - srcVector.y;
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
		a.x = -x;
		a.y = -y;
		a.z = -z;
		return a;
	}

	float vec3::length() const {
		float a;
		a = sqrt(x * x + y * y + z * z);
		return a;
	}

	vec3& vec3::normalize() {
		float l = this->length();

		this->x = this->x / l;
		this->y = this->y / l;
		this->z = this->z / l;
		return *this;
	}

	float dotProduct(const vec3& v1, const vec3& v2) {
		float product;
		product = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
		return product;
	}

	vec3 crossProduct(const vec3& v1, const vec3& v2) {
		vec3 rez;
		rez.x = v1.y * v2.z - v1.z * v2.y;
		rez.y = v1.z * v2.x - v1.x * v2.z;
		rez.z = v1.x * v2.y - v1.y * v2.x;
		return rez;
	}

}