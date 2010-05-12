#pragma once
#include <iostream>
#include <gmpxx.h>

using namespace std;

typedef mpf_class PSTL_TYPE;

#define PSTL_TYPE_TO_DOUBLE(x) x.get_d()
#define _macroToStr(s) #s
#define macroToStr(s) _macroToStr(s)

