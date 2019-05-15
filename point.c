#include "stdafx.h"
#include "math.h"
#include "point.h"
#define eps 0.00000001
float x;
float y;
point::point()
{
	x = 0;
	y = 0;
}
point::point(float _x, float _y)
{
	x = _x;
	y = _y;
}
point::point(const point &a)
{
	x = a.x;
	y = a.y;
}
point& point::operator=(int a)
{
	x = a;
	y = a;
	return *this;
}
point& point::operator=(point a)
{
	x = a.x;
	y = a.y;
	return *this;
}
point point::operator-(point p)
{
	point r(p[0] - x, p[1] - y);
	return r;
}
bool point::operator==(point p)
{
	return ((x == p.x) && (y == p.y));
}
bool point::operator==(int p)
{
	return (x == p) && (y == p);
}
bool point::operator!=(point p)
{
	return !((x == p.x) && (y == p.y));
}
float point::operator[](int k)
{
	return ((k == 0) ? x : y);
}
point point::operator+(point p)
{
	point r(p[0] + x, p[1] + y);
	return r;
}
point point::operator*(point p)
{
	point r(p[0] * x, p[1] * y);
	return r;
}
point point::operator/(point p)
{
	point r(p[0] / x, p[1] / y);
	return r;
}
point point::operator/(float p)
{
	point r(x / p, y / p);
	return r;
}
int cross(point a0, point a1, point b0, point b1) // > 0 - есть пересесчение
{
	float Aa = (a1[1] - a0[1]) / (a1[0] - a0[0]);
	float Ba = a0[1] - a0[0] * Aa;
	float Ab = (b1[1] - b0[1]) / (b1[0] - b0[0]);
	float Bb = b0[1] - b0[0] * Ab;
	float x = (Bb - Ba) / (Ab - Aa);
	int r = (a1[0] > a0[0]) ? ((x < a1[0]) && (x > a0[0])) : ((x < a0[0]) && (x > a1[0]));
	return r;
}
float abs(point p)
{
	return (p[0] * p[0] + p[1] * p[1]); // sqrtf(p[0] * p[0] + p[1] * p[1]);
}
float sq(point a, point b, point c)
{
	point t0 = b - a;
	point t1 = c - a;
	float t = t0.x*t1.y - t0.y*t1.x;
	if (t < 0)
		t = -t;
	return t;
}
int pointincut(point a, point b, point c) // 1 - in
{
	float temp = b.x - a.x;
	if (fabs(temp) < eps)
	{
		if (c.x == a.x)
			return 1;
		else
			return 0;
	}
	else
	{
		float A = (fabs(temp) < eps) ? 0 : (b.y - a.y) / temp;
		float B = a.y - A*a.x;
		if (fabs(A*c.x + B - c.y) < eps)
			return 1;
		else return 0;
	}
}