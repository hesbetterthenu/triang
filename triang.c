#include "stdafx.h"
#include "triang.h"
#define eps 0.00000001
tr::tr()
{
	a = 0;
	b = 0;
	c = 0;
}
tr::tr(point _a, point _b, point _c)
{
	a = _a;
	b = _b;
	c = _c;
}
tr::tr(const tr &t)
{
	a = t.a;
	b = t.b;
	c = t.c;
}
tr& tr::operator=(tr t)
{
	a = t.a;
	b = t.b;
	c = t.c;
	return *this;
}
bool tr::operator==(tr p)
{
	bool ttt = true;
	for (int i = 0; i < 3; i++)
	{
		bool tt = false;
		for (int j = 0; j < 3; j++)
		{
			tt |= (*this)[i] == p[j];
		}
		ttt &= tt;
	}
	return ttt;
}
point tr::operator[](int k)
{
	switch (k)
	{
	case 0:
		return a;
		break;
	case 1:
		return b;
		break;
	default:
		return c;
		break;
	}
}
point tr::ce() // incenter
{
	point r = (a + b + c) / 3;
	return r;
}
int taken(tr* t)
{
	tr* temp = t;
	int r = 0;
	while (!isnull(temp))
	{
		r++;
		t++;
		temp++;
	}
	return r;
}
int pointed(tr* t, point p) // 0 - not inside; 1 - equal; 2ab 3ac 4bc - sided; 5 - inside
{
	if (!t)
		return 0;
	float temp = sq(t->a, t->b, p);
	temp += sq(t->a, t->c, p);
	temp += sq(t->b, t->c, p);
	if (temp > sq(t->a, t->b, t->c))
		return 0;
	if ((t->a == p) || (t->b == p) || (t->c == p))
		return 1;
	if (pointincut(t->a, t->b, p))
		return 2;
	if (pointincut(t->a, t->c, p))
		return 3;
	if (pointincut(t->b, t->c, p))
		return 4;
	return 5;
}
int delone(tr* t0, tr* t1) // 0 - no swap
{
	point a[2];
	point b[2];
	int n[2];
	int ca = 0;
	for (int i = 0; i < 3; i++)
	{
		bool t = false;
		for (int j = 0; j < 3; j++)
		if ((*t0)[i] == (*t1)[j])
		{
			t = true;
			n[ca] = j;
			a[ca] = (*t0)[i];
			ca++;
			break;
		}
		if (!t)
		{
			b[0] = (*t0)[i];
		}
	}
	if (ca < 2)
		return 0;
	for (int i = 0; i < 3; i++)
	if (!((i == n[0]) || (i == n[1])))
	{
		b[1] = (*t1)[i];
		break;
	}
	if (!cross(a[0], a[1], b[0], b[1]))
		return 0;
	if (abs(a[1] - a[0]) < abs(b[1] - b[0]))
		return 0;
	*t0 = tr(b[0], b[1], a[0]);
	*t1 = tr(b[0], b[1], a[1]);
	return 1;
}
void makenull(tr* t)
{
	t->a = 0;
	t->b = 0;
	t->c = 0;
}
int isnull(tr* t)
{
	return (t->a == 0) && (t->b == 0) && (t->c == 0);
}