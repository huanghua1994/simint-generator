#pragma once

#include "simint/vectorization/vectorization.h"

#define SIMINT_OSTEI_MAXAM 1
#define SIMINT_OSTEI_MAXDER 1
#define SIMINT_OSTEI_DERIV1_MAXAM 0
#define SIMINT_OSTEI_MAX_WORKSIZE ((SIMINT_SIMD_ROUND(SIMINT_NSHELL_SIMD * 81)))
#define SIMINT_OSTEI_MAX_WORKMEM (SIMINT_OSTEI_MAX_WORKSIZE * sizeof(double))
