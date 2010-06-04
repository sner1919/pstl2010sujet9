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
double randDouble();
double randDouble2();

typedef mpf_class TYPE_SUM;
#define TYPE_SUM_TO_DOUBLE(x) x.get_d()
#define DOUBLE_TO_TYPE_SUM(x) mpf_class(x, 64)
#define TYPE_SUM_PRECISION 1024

class TYPE_UNION {
	public:
		int type;
		union {
			double* d;
			TYPE_SUM* s;
		};

		TYPE_UNION(double& x);

		TYPE_UNION(TYPE_SUM& x);

		TYPE_SUM toTypeSum();

		double toDouble();

		TYPE_UNION& operator=(const TYPE_UNION& x);

		TYPE_UNION& operator=(const double& x);

		TYPE_UNION& operator=(const TYPE_SUM& x);

		TYPE_UNION& operator+=(const TYPE_UNION& x);

		TYPE_UNION& operator+=(const double& x);

		TYPE_UNION& operator+=(const TYPE_SUM& x);

		TYPE_UNION& operator-=(const TYPE_UNION& x);

		TYPE_UNION& operator-=(const double& x);

		TYPE_UNION& operator-=(const TYPE_SUM& x);

		bool operator==(const TYPE_UNION& x) const;

		bool operator==(const double& x) const;

		bool operator==(const TYPE_SUM& x) const;

		bool operator!=(const TYPE_UNION& x) const;

		bool operator!=(const double& x) const;

		bool operator!=(const TYPE_SUM& x) const;

	    friend ostream& operator<<(ostream& out, const TYPE_UNION& x);
};
