#include "vec2.h"

namespace egc {
	vec2& vec2::operator =(const vec2 &srcVector) { //needed const so we never change value of source vector
		//v1 = v2
		this->x = srcVector.x;
		this->y = srcVector.y;

		return *this;
	}
	vec2 vec2::operator +(const vec2& srcVector) const {
		//also viable to try vec2(2,2) or vec2 a = {2, 2} for initialization.
		//cannot write something like this->x = 5;
		//don't want to modify either v1 or v2, we want to create new vector with sum of both v1 and v2
		//v1 and v2 immutable
		//a = f(b)
		//f(b) = a
		//advantage is that we can implement just oen method and that method canact as a setter r a getter depending on which way we act on that particular method
		//eg we get value from matrix but at same time we can change value of matrix for particular line/column
		//a setter and a getter in the same method
		return vec2(this->x + srcVector.x, this->y + srcVector.y);
	}
	
	vec2& vec2::operator +=(const vec2& srcVector) {
		this->x += srcVector.x;
		this->y += srcVector.y;
		return *this;
	}
	
	vec2 vec2::operator *(float scalarValue) const {
		return vec2(this->x * scalarValue, this->y * scalarValue);
	}
	vec2 vec2::operator -(const vec2& srcVector) const {
		return vec2(this->x - srcVector.x, this->y - srcVector.y);
	}
	
	vec2& vec2::operator -=(const vec2& srcVector) {
		this->x -= srcVector.x;
		this->y -= srcVector.y;
		return *this;
	}

	vec2 vec2::operator -() const {
		return vec2(this->x * -1, this->y * -1);
	}
	
	float vec2::length() const {
		return sqrt(this->x * this->x + this->y * this->y);
	}
	
	vec2& vec2::normalize() {
		float length = this->length();
		this->x /= length;
		this->y /= length;
		return *this;
	}

	float dotProduct(const vec2& v1, const vec2& v2) {
		return (v1.x * v2.x + v2.x * v2.y);
	}

}