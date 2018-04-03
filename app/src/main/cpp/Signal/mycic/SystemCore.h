//
// File: SystemCore.h
//
// MATLAB Coder version            : 2.8
// C/C++ source code generated on  : 24-Mar-2017 13:57:42
//
#ifndef __SYSTEMCORE_H__
#define __SYSTEMCORE_H__

// Include Files
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "MyCic_types.h"

// Function Declarations
extern void SystemCore_step(dsp_CICDecimator_2 *obj, const int varargin_1[6600],
  long long varargout_1[165]);
extern void b_SystemCore_step(dsp_private_FIRCombFilter *obj, const long long
  varargin_1[165], long long varargout_1[165]);
extern void c_SystemCore_step(dsp_private_FIRCombFilter_1 *obj, const long long
  varargin_1[165], long long varargout_1[165]);
extern void d_SystemCore_step(dsp_private_FIRCombFilter_2 *obj, const long long
  varargin_1[165], long long varargout_1[165]);

#endif

//
// File trailer for SystemCore.h
//
// [EOF]
//
