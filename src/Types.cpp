#include "Types.hpp"

PSTL_TYPE_UNION::PSTL_TYPE_UNION(double& x) : type(0), d(&x) {}

PSTL_TYPE_UNION::PSTL_TYPE_UNION(PSTL_TYPE_SUM& x) : type(1), s(&x) {}

PSTL_TYPE_UNION::operator double() {
	return (type == 0 ? *d : s->get_d());
}

PSTL_TYPE_UNION::operator PSTL_TYPE_SUM() {
	PSTL_TYPE_SUM res = (type == 0 ? *d : *s);
	return res;
}

PSTL_TYPE_UNION& PSTL_TYPE_UNION::operator=(const PSTL_TYPE_UNION& x) {
	if(type == 0) *d = (x.type == 0 ? *x.d : x.s->get_d());
	else *s = (x.type == 0 ? *x.d : *x.s);
	return *this;
}

PSTL_TYPE_UNION& PSTL_TYPE_UNION::operator=(const double& x) {
	if(type == 0) *d = x;
	else *s = x;
	return *this;
}

PSTL_TYPE_UNION& PSTL_TYPE_UNION::operator=(const PSTL_TYPE_SUM& x) {
	if(type == 0) *d = x.get_d();
	else *s = x;
	return *this;
}

PSTL_TYPE_UNION& PSTL_TYPE_UNION::operator+=(const PSTL_TYPE_UNION& x) {
	if(type == 0) {
		PSTL_TYPE_SUM aux = *d;
		aux += (x.type == 0 ? *x.d : *x.s);
		*d = aux.get_d();
	} else *s += (x.type == 0 ? *x.d : *x.s);
	return *this;
}

PSTL_TYPE_UNION& PSTL_TYPE_UNION::operator+=(const double& x) {
	if(type == 0) {
		PSTL_TYPE_SUM aux = *d;
		aux += x;
		*d = aux.get_d();
	} else *s += x;
	return *this;
}

PSTL_TYPE_UNION& PSTL_TYPE_UNION::operator+=(const PSTL_TYPE_SUM& x) {
	if(type == 0) {
		PSTL_TYPE_SUM aux = *d;
		aux += x;
		*d = aux.get_d();
	} else *s += x;
	return *this;
}

PSTL_TYPE_UNION& PSTL_TYPE_UNION::operator-=(const PSTL_TYPE_UNION& x) {
	return operator+=(-(x.type == 0 ? *x.d : *x.s));
}

PSTL_TYPE_UNION& PSTL_TYPE_UNION::operator-=(const double& x) {
	return operator+=(-x);
}

PSTL_TYPE_UNION& PSTL_TYPE_UNION::operator-=(const PSTL_TYPE_SUM& x) {
	return operator+=(-x);
}

bool PSTL_TYPE_UNION::operator==(const PSTL_TYPE_UNION& x) const {
	return (type == 0 ? *d : *s) == (x.type == 0 ? *x.d : *x.s);
}

bool PSTL_TYPE_UNION::operator==(const double& x) const {
	return (type == 0 ? *d : *s) == x;
}

bool PSTL_TYPE_UNION::operator==(const PSTL_TYPE_SUM& x) const {
	return (type == 0 ? *d : *s) == x.get_d();
}

ostream& operator<<(ostream& out, const PSTL_TYPE_UNION& x) {
    out << (x.type == 0 ? *x.d : *x.s);
    return out;
}
