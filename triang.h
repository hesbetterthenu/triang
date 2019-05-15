#include "drawit.h"
#define eps 0.00000001
class tr{
public:
	point a;
	point b;
	point c;
	tr();
	tr(point _a, point _b, point _c);
	tr(const tr &t);
	tr& operator=(tr t);
	bool operator==(tr p);
	point operator[](int k);
	point ce();
};
int pointed(tr* t, point p);
int delone(tr* t0, tr* t1);
int taken(tr* t);
void makenull(tr* t);
int isnull(tr* t);