//
// File: FIRCombFilter.h
//
// MATLAB Coder version            : 2.8
// C/C++ source code generated on  : 24-Mar-2017 13:57:42
//
#ifndef __FIRCOMBFILTER_H__
#define __FIRCOMBFILTER_H__

// Include Files
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "MyCic_types.h"

// Function Declarations
extern void FIRCombFilter_stepImpl(dsp_private_FIRCombFilter *obj, const long
  long in[165], long long out[165]);
extern void b_FIRCombFilter_stepImpl(dsp_private_FIRCombFilter_1 *obj, const
  long long in[165], long long out[165]);
extern void c_FIRCombFilter_stepImpl(dsp_private_FIRCombFilter_2 *obj, const
  long long in[165], long long out[165]);

#endif

//
// File trailer for FIRCombFilter.h
//
// [EOF]
//
