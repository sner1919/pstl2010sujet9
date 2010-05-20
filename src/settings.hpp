#pragma once
#include <iostream>

using namespace std;

#define _MACRO_TO_STR(s) #s
#define MACRO_TO_STR(s) _MACRO_TO_STR(s)


#define EPS1 1040000000 // rq : dépend de n (ex < 1040000000 pour n=1000, < 1030000000 pour n = 100)
