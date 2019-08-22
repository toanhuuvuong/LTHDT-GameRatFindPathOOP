#ifndef __VECTOR2_H__
#define __VECTOR2_H__

#include<iostream>

template<typename T>
class Vector2
{
public:
	// Member attribute
	T m_x;
	T m_y;
	// Member function
	Vector2() { m_x = m_y = 0; }
	Vector2(const T &x, const T &y) : m_x(x), m_y(y) {}
	template<typename U>
	Vector2(const Vector2<U> &other) : Vector2(other.m_x, other.m_y) {}
	template<typename U>
	Vector2(Vector2<U> &&other) { m_x = other.m_x;  m_y = other.m_y; }
};
template<typename T>
Vector2<T> operator-(const Vector2<T> &right) { return Vector2<T>(-right.m_x , -right.m_y); }
template<typename T>
bool operator==(const Vector2<T> &left, const Vector2<T> &right) { return (left.m_x == right.m_x && left.m_y == right.m_y); }
template<typename T>
bool operator!=(const Vector2<T> &left, const Vector2<T> &right) { return !(left == right); }
template<typename T>
Vector2<T> operator+(const Vector2<T> &left, const Vector2<T> &right) { return Vector2<T>(left.m_x + right.m_x, left.m_y + right.m_y); }
template<typename T>
Vector2<T> operator-(const Vector2<T> &left, const Vector2<T> &right) { return Vector2<T>(left.m_x - right.m_x, left.m_y - right.m_y); }
template<typename T>
Vector2<T> operator*(const Vector2<T> &left, const T &right) { return Vector2<T>(left.m_x * right, left.m_y * right); }
template<typename T>
Vector2<T> operator*(const T &left, const Vector2<T> &right) { return Vector2<T>(right.m_x * left, right.m_y * left); }
template<typename T>
Vector2<T> operator/(const Vector2<T> &left, const T &right) { return Vector2<T>(left.m_x / right, left.m_y / right); }
template<typename T>
Vector2<T>& operator+=(Vector2<T> &left, const Vector2<T> &right) { left = left + right; return left; }
template<typename T>
Vector2<T>& operator-=(Vector2<T> &left, const Vector2<T> &right) { left = left - right; return left; }
template<typename T>
Vector2<T>& operator*=(Vector2<T> &left, const T &right) { left = left * right; return left; }
template<typename T>
Vector2<T>& operator/=(Vector2<T> &left, const T &right) { left = left / right; return left; }

using Vector2i = Vector2<int>;
using Vector2u = Vector2<unsigned int>;
using Vector2f = Vector2<float>;

#endif