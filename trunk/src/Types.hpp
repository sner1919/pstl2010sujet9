#pragma once
#include "settings.hpp"
#include <gmpxx.h>

/* ---------------- Test d'égalité ---------------
	utilise la représentation binaire des flottants :
		- chaque float correspond à un int et chaque double correspond à deux int !!!!!!!!!!
		=> mieux que les tests d'égalité avec un epsilon absolu ou même relatif
-------------------------------------------------- */
int floatToIndex(float a);
void doubleToIndex(double a, int *a1, int *a0);
float indexToFloat(int ai);
double indexToDouble(int a1, int a0);
bool equal(float a, float b, int eps);
bool equal(double a, double b, int eps1, int eps0);

typedef mpf_class TYPE_SUM;
#define TYPE_SUM_TO_DOUBLE(x) x.get_d()

class PSTL_TYPE_UNION {
	public:
		int type;
		union {
			double* d;
			TYPE_SUM* s;
		};

		PSTL_TYPE_UNION(double& x);

		PSTL_TYPE_UNION(TYPE_SUM& x);

		TYPE_SUM toTypeSum();

		double toDouble();

		PSTL_TYPE_UNION& operator=(const PSTL_TYPE_UNION& x);

		PSTL_TYPE_UNION& operator=(const double& x);

		PSTL_TYPE_UNION& operator=(const TYPE_SUM& x);

		PSTL_TYPE_UNION& operator+=(const PSTL_TYPE_UNION& x);

		PSTL_TYPE_UNION& operator+=(const double& x);

		PSTL_TYPE_UNION& operator+=(const TYPE_SUM& x);

		PSTL_TYPE_UNION& operator-=(const PSTL_TYPE_UNION& x);

		PSTL_TYPE_UNION& operator-=(const double& x);

		PSTL_TYPE_UNION& operator-=(const TYPE_SUM& x);

		bool operator==(const PSTL_TYPE_UNION& x) const;

		bool operator==(const double& x) const;

		bool operator==(const TYPE_SUM& x) const;

		bool operator!=(const PSTL_TYPE_UNION& x) const;

		bool operator!=(const double& x) const;

		bool operator!=(const TYPE_SUM& x) const;

	    friend ostream& operator<<(ostream& out, const PSTL_TYPE_UNION& x);
};
