#include "stdafx.h"
#include "memory.h"
#include "qtree.h"
#define eps 0.00000001
#define allconst 64
branch::branch()
{
	f = 0;
	t = (tr**)malloc(allconst/**sizeof(tr*)*/);
	//t = new tr*[allconst];
	memset((char*)t, 0, sizeof(tr*)*allconst);
	nt = 0;
	b = 0;
	x = 0;
	y = 0;
	s = 0;
}
branch::branch(const branch& a)
{
	f = a.f;
	nt = a.nt;
	t = (tr**)malloc(allconst*sizeof(tr*));
	//t = new tr*[allconst];
	memcpy(t, a.t, nt*sizeof(tr*));
	b = a.b;
	x = a.x;
	y = a.y;
	s = a.s;
}
branch& branch::operator=(branch a)
{
	f = a.f;
	nt = a.nt;
	if (!t)
		t = (tr**)malloc(allconst*sizeof(tr*));
		//t = new tr*[allconst];
	memcpy(t, a.t, nt*sizeof(tr*));
	b = a.b;
	x = a.x;
	y = a.y;
	s = a.s;
	return *this;
}
branch branch::operator+=(tr* a)
{
	for (int i = 0; i < this->nt; i++)
	if (*(this->t[i]) == *a)
		return branch(*this);
	this->t[this->nt] = a;
	this->nt++;
	if (this->nt == 2)
		this->pregnant();
	if (this->nt > 1)
	{
		point tt = a->ce();
		unsigned r = ((tt.x > this->x) | ((tt.y > this->y) << 1)) & 0x3;
		this->b[r] += a;
	}
	return branch(*this);
}
branch branch::operator-=(tr* a)
{
	int i;
	for (i = 0; i < nt; i++)
	if (t[i] == a)
		break;
	if (i == nt)
		return *this;
	t[i] = t[nt - 1];
	nt--;
	if (nt == 1)
	{
		delete[] b;
		b = 0;
		return *this;
	}
	if (nt == 0)
		return *this;
	for (i = 0; i < 4; i++)
	{
		b[i] -= a;
	}
	return *this;
}
void branch::pregnant()
{
	b = new branch[4];
	b[0].f = this;
	b[1].f = this;
	b[2].f = this;
	b[3].f = this;
	b[0].s = s / 2;
	b[1].s = s / 2;
	b[2].s = s / 2;
	b[3].s = s / 2;
	b[0].x = x - s / 4;
	b[0].y = y - s / 4;
	b[1].x = x + s / 4;
	b[1].y = y - s / 4;
	b[2].x = x - s / 4;
	b[2].y = y + s / 4;
	b[3].x = x + s / 4;
	b[3].y = y + s / 4;
	for (int i = 0; i < nt; i++)
	{
		point tt = t[i]->ce();
		unsigned r = ((tt.x > x) | ((tt.y > y) << 1)) & 0x3;
		b[r] += t[i];
	}
}
branch::~branch()
{
	if (t)
		free(t);
		//delete[] t;
	//if (b)
		//delete[] b;
}
void deltr(branch root, tr* a)
{
	root -= a;
}
void addtr(branch root, tr* a)
{
	root += a;
}
void paste(branch* root, tr* t, point a, int& nn)
{
	branch* temp = root;
	while (temp->b != 0)
	{
		unsigned r = ((a.x > temp->x) | ((a.y > temp->y) << 1)) & 0x3;
		temp = temp->b + r;
	}
	int k = 0;
	int res = 0; 
	//int nn;
	//nn = taken(t);
	tr* trtemp = 0;
	while (!res)
	{
		if (k < temp->nt)
		{
			trtemp = temp->t[k];
			res = pointed(temp->t[k], a);
			k++;
		}
		else
		{
			k = 0;
			temp = temp->f;
		}
	}
	k--;
	switch (res)
	{
	case 2: //ab
		*(t + nn) = *trtemp;
		trtemp->a = a;
		(t + nn)->b = a;
		(t + nn + 1)->a = 0;
		(t + nn + 1)->b = 0;
		(t + nn + 1)->c = 0;
		*root -= trtemp;
		*root += trtemp;
		trtemp = (t + nn);
		*root += trtemp;
		nn++;
		break;
	case 3: //ac
		*(t + nn) = *trtemp;
		trtemp->a = a;
		(t + nn)->c = a;
		(t + nn + 1)->a = 0;
		(t + nn + 1)->b = 0;
		(t + nn + 1)->c = 0;
		*root -= trtemp;
		*root += trtemp;
		trtemp = (t + nn);
		*root += trtemp;
		nn++;
		break;
	case 4: //bc
		*(t + nn) = *trtemp;
		trtemp->b = a;
		(t + nn)->c = a;
		(t + nn + 1)->a = 0;
		(t + nn + 1)->b = 0;
		(t + nn + 1)->c = 0;
		*root -= trtemp;
		*root += trtemp;
		trtemp = (t + nn);
		*root += trtemp;
		nn++;
		break;
	case 5: //abc
		*(t + nn) = *trtemp;
		*(t + nn + 1) = *trtemp;
		trtemp->a = a;
		(t + nn)->b = a;
		(t + nn + 1)->c = a;
		(t + nn + 2)->a = 0;
		(t + nn + 2)->b = 0;
		(t + nn + 2)->c = 0;
		*root -= trtemp;
		*root += trtemp;
		trtemp = (t + nn);
		*root += trtemp;
		trtemp = (trtemp + 1);
		*root += trtemp;
		nn += 2;
		break;
	}
}