//=====================================================================
//
// FastMemcpy.c - skywind3000@163.com, 2015
//
// feature:
// 50% speed up in avg. vs standard memcpy (tested in vc2012/gcc4.9)
//
//=====================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "fast_memcpy.h"