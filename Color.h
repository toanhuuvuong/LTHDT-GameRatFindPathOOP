#ifndef __COLOR_H__
#define __COLOR_H__

#include<iostream>

class Color
{
public:
	// Member attribute
	std::size_t m_code;
	// Member function
	static const Color Black;
	static const Color White;
	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color Yellow;

	Color() { m_code = 0; }
	Color(const std::size_t &code) : m_code(code) {}
	Color(const Color &other) : Color(other.m_code) {}
	Color(Color &&other) { m_code = other.m_code; }
};
const Color Color::Black = Color(0);
const Color Color::White = Color(0);
const Color Color::Red = Color(0);
const Color Color::Green = Color(0);
const Color Color::Blue = Color(0);
const Color Color::Yellow = Color(0);
bool operator==(const Color &left, const Color &right) { return (left.m_code == right.m_code); }
bool operator!=(const Color &left, const Color &right) { return !(left == right); }
Color operator+(const Color &left, const Color &right) { return Color(left.m_code + right.m_code); }
Color operator-(const Color &left, const Color &right) { return Color(left.m_code - right.m_code); }
Color operator*(const Color &left, const Color &right) { return Color(left.m_code * right.m_code); }
Color& operator+=(Color &left, const Color &right) { left = left + right; return left; }
Color& operator-=(Color &left, const Color &right) { left = left - right; return left; }
Color& operator*=(Color &left, const Color &right) { left = left * right; return left; }

#endif