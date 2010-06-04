#include "Types.hpp"
#include <cstdlib>
#include <limits>
#include <cmath>

int floatToIndex(float a) {
	int ai = *(int*) &a;

	return ai = ai < 0 ? 0x80000000 - ai : ai;
}

void doubleToIndex(double a, int *a1, int *a0) {
	int *t = *(int(*)[2]) &a;

	*a0 = t[0];
	*a1 = t[1];
	if(*a1 < 0) {
		*a1 = 0x80000000 - *a1 - 1;
		*a0 = -*a0 - 1;
	}
	*a0 = *a0 < 0 ? *a0 - 0x80000000 : *a0 + 0x80000000;
}

float indexToFloat(int ai) {
	int k = ai < 0 ? 0x80000000 - ai : ai;

	return *(float*) &k;
}

double indexToDouble(int a1, int a0) {
	a0 = a0 < 0 ? a0 - 0x80000000 : a0 + 0x80000000;
	if(a1 < 0) {
		a1 = 0x80000000 - a1 - 1;
		a0 = -a0 - 1;
	}

	int dp[] = {a0, a1};

	return *(double*) &dp;
}

bool equal(float a, float b, int eps) {
	return abs(floatToIndex(a) - floatToIndex(b)) <= eps;
}

bool equal(double a, double b, int eps1, int eps0) {
	int ai[2], bi[2];
	int min, max;

	doubleToIndex(a, &ai[0], &ai[1]);
	doubleToIndex(b, &bi[0], &bi[1]);

	int diff = abs(ai[0] - bi[0]);
	if(diff < eps1) {
		return true;
	} else if(diff == eps1) {
		return abs(ai[1] - bi[1]) <= eps0;
	} else if(diff == eps1 + 1) {
		if(ai[0] < bi[0]) {
			min = ai[1];
			max = bi[1];
		} else {
			min = bi[1];
			max = ai[1];
		}
		if(!(min > 0 && max < 0)) return false;
		//printf("min : %d\n", min);
		//printf("max : %d\n", max);
		min += 0x80000000;
		max -= 0x80000000;
		//printf("minH : %x\n", min);
		//printf("maxH : %x\n", max);
		//printf("abs(max - min) : %d\n", abs(max - min));
		return abs(max - min) <= eps0;
	} else {
		return false;
	}
}

double randDouble() {
	int exp = ((double) rand() / ((double) RAND_MAX + 1) - 0.5) * 2;
	return ((double) rand() / ((double) RAND_MAX + 1) - 0.5) * 2 * pow(2., exp);
}

double randDouble2() {
	int ai[2];

	for(int i = 0; i < 2; i++) ai[i] = (rand() << 16) xor rand();

	return indexToDouble(ai[1], ai[0]);
}

TYPE_UNION::TYPE_UNION(double& x) : type(0), d(&x) {}

TYPE_UNION::TYPE_UNION(TYPE_SUM& x) : type(1), s(&x) {}

double TYPE_UNION::toDouble() {
	return (type == 0 ? *d : s->get_d());
}

TYPE_SUM TYPE_UNION::toTypeSum() {
	return (type == 0 ? *d : *s);
}

TYPE_UNION& TYPE_UNION::operator=(const TYPE_UNION& x) {
	if(type == 0) *d = (x.type == 0 ? *x.d : x.s->get_d());
	else *s = (x.type == 0 ? *x.d : *x.s);
	return *this;
}

TYPE_UNION& TYPE_UNION::operator=(const double& x) {
	if(type == 0) *d = x;
	else *s = x;
	return *this;
}

TYPE_UNION& TYPE_UNION::operator=(const TYPE_SUM& x) {
	if(type == 0) *d = x.get_d();
	else *s = x;
	return *this;
}

TYPE_UNION& TYPE_UNION::operator+=(const TYPE_UNION& x) {
	if(type == 0) {
		TYPE_SUM aux = *d;
		aux += (x.type == 0 ? *x.d : *x.s);
		*d = aux.get_d();
	} else *s += (x.type == 0 ? *x.d : *x.s);
	return *this;
}

TYPE_UNION& TYPE_UNION::operator+=(const double& x) {
	if(type == 0) {
		TYPE_SUM aux = *d;
		aux += x;
		*d = aux.get_d();
	} else *s += x;
	return *this;
}

TYPE_UNION& TYPE_UNION::operator+=(const TYPE_SUM& x) {
	if(type == 0) {
		TYPE_SUM aux = *d;
		aux += x;
		*d = aux.get_d();
	} else *s += x;
	return *this;
}

TYPE_UNION& TYPE_UNION::operator-=(const TYPE_UNION& x) {
	return operator+=(-(x.type == 0 ? *x.d : *x.s));
}

TYPE_UNION& TYPE_UNION::operator-=(const double& x) {
	return operator+=(-x);
}

TYPE_UNION& TYPE_UNION::operator-=(const TYPE_SUM& x) {
	return operator+=(-x);
}

bool TYPE_UNION::operator==(const TYPE_UNION& x) const {
	return (type == 0 ? *d : *s) == (x.type == 0 ? *x.d : *x.s);
}

bool TYPE_UNION::operator==(const double& x) const {
	return (type == 0 ? *d : *s) == x;
}

bool TYPE_UNION::operator==(const TYPE_SUM& x) const {
	return (type == 0 ? *d : *s) == x.get_d();
}

bool TYPE_UNION::operator!=(const TYPE_UNION& x) const {
	return !operator==(x);
}

bool TYPE_UNION::operator!=(const double& x) const {
	return !operator==(x);
}

bool TYPE_UNION::operator!=(const TYPE_SUM& x) const {
	return !operator==(x);
}

ostream& operator<<(ostream& out, const TYPE_UNION& x) {
    out << (x.type == 0 ? *x.d : *x.s);
    return out;
}
