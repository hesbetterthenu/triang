#define eps 0.00000001
class point{
public:
	float x;
	float y;
	point();
	point(float _x, float _y);
	point(const point &a);
	point& operator=(int a);
	point& operator=(point a);
	point operator+(point p);
	point operator-(point p);
	point operator/(float p);
	point operator*(point p);
	point operator/(point p);
	bool operator==(point p);
	bool operator==(int p);
	bool operator!=(point p);
	float operator[](int k);
};
int cross(point a0, point a1, point b0, point b1);
float abs(point p);
float sq(point a, point b, point c);
int pointincut(point a, point b, point c);