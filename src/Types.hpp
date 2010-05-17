#pragma once
#include "settings.hpp"
#include <gmpxx.h>

typedef mpf_class PSTL_TYPE_SUM;

class PSTL_TYPE_UNION {
	public:
		int type;
		union {
			double* d;
			PSTL_TYPE_SUM* s;
		};

		PSTL_TYPE_UNION(double& x);

		PSTL_TYPE_UNION(PSTL_TYPE_SUM& x);

		operator double();

		operator PSTL_TYPE_SUM();

		PSTL_TYPE_UNION &operator=(const PSTL_TYPE_UNION& x);

		PSTL_TYPE_UNION& operator=(const double& x);

		PSTL_TYPE_UNION& operator=(const PSTL_TYPE_SUM& x);

		PSTL_TYPE_UNION& operator+=(const PSTL_TYPE_UNION& x);

		PSTL_TYPE_UNION& operator+=(const double& x);

		PSTL_TYPE_UNION& operator+=(const PSTL_TYPE_SUM& x);

		PSTL_TYPE_UNION& operator-=(const PSTL_TYPE_UNION& x);

		PSTL_TYPE_UNION& operator-=(const double& x);

		PSTL_TYPE_UNION& operator-=(const PSTL_TYPE_SUM& x);

		bool operator==(const PSTL_TYPE_UNION& x) const;

		bool operator==(const double& x) const;

		bool operator==(const PSTL_TYPE_SUM& x) const;

	    friend ostream& operator<<(ostream& out, const PSTL_TYPE_UNION& x);
};
