#include "triang.h"
#include "memory.h"
#define eps 0.00000001
#define allocconst 1024
class branch
{
public:
	branch* f;
	tr** t;
	int nt;
	branch* b; // 4
	float x;
	float y;
	float s;
	branch();
	branch(const branch& a);
	branch& operator=(branch a);
	branch operator+=(tr* a);
	branch operator-=(tr* a);
	void pregnant();
	~branch();
};
//branch operator += (branch &th, tr* &a);
void deltr(branch root, tr* a);
void addtr(branch root, tr* a);
void paste(branch* root, tr* t, point a, int& nn);