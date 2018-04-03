//
// File: SystemCore.cpp
//
// MATLAB Coder version            : 2.8
// C/C++ source code generated on  : 24-Mar-2017 13:57:42
//

// Include Files
#include "rt_nonfinite.h"
#include "MyCic.h"
#include "SystemCore.h"
#include "FIRCombFilter.h"
#include "step.h"
#include "CICDecimator.h"

// Function Definitions

//
// Arguments    : dsp_CICDecimator_2 *obj
//                const int varargin_1[6600]
//                long long varargout_1[165]
// Return Type  : void
//
void SystemCore_step(dsp_CICDecimator_2 *obj, const int varargin_1[6600], long
                     long varargout_1[165])
{
  dsp_CICDecimator_2 *b_obj;
  int k;
  static const short inputSize[8] = { 6600, 1, 1, 1, 1, 1, 1, 1 };

  dsp_private_FIRCombFilter *c_obj;
  dsp_private_FIRCombFilter_1 *d_obj;
  dsp_private_FIRCombFilter_2 *e_obj;
  boolean_T exitg1;
  static const short iv0[8] = { 6600, 1, 1, 1, 1, 1, 1, 1 };

  if (obj->isInitialized != 1) {
    b_obj = obj;
    b_obj->isInitialized = 1;
    for (k = 0; k < 8; k++) {
      b_obj->inputVarSize1[k] = (unsigned int)inputSize[k];
    }

    // System object Constructor function: dsp.private.Integrator
    b_obj->cIntgStage1.S0_isInitialized = 0;

    // System object Constructor function: dsp.private.Integrator
    b_obj->cIntgStage2.S0_isInitialized = 0;

    // System object Constructor function: dsp.private.Integrator
    b_obj->cIntgStage3.S0_isInitialized = 0;
    b_obj->cCmbStage1.isInitialized = 0;
    b_obj->cCmbStage2.isInitialized = 0;
    b_obj->cCmbStage3.isInitialized = 0;
    if (b_obj->cIntgStage1.S0_isInitialized == 1) {
      InitializeConditions(&b_obj->cIntgStage1);
    }

    c_obj = &b_obj->cCmbStage1;
    if ((b_obj->cCmbStage1.isInitialized == 1) &&
        (c_obj->cDelay.S0_isInitialized == 1)) {
      d_InitializeConditions(&c_obj->cDelay);
    }

    if (b_obj->cIntgStage2.S0_isInitialized == 1) {
      b_InitializeConditions(&b_obj->cIntgStage2);
    }

    d_obj = &b_obj->cCmbStage2;
    if ((b_obj->cCmbStage2.isInitialized == 1) &&
        (d_obj->cDelay.S0_isInitialized == 1)) {
      e_InitializeConditions(&d_obj->cDelay);
    }

    if (b_obj->cIntgStage3.S0_isInitialized == 1) {
      c_InitializeConditions(&b_obj->cIntgStage3);
    }

    e_obj = &b_obj->cCmbStage3;
    if ((b_obj->cCmbStage3.isInitialized == 1) &&
        (e_obj->cDelay.S0_isInitialized == 1)) {
      f_InitializeConditions(&e_obj->cDelay);
    }
  }

  b_obj = obj;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 8)) {
    if (b_obj->inputVarSize1[k] != (unsigned int)iv0[k]) {
      for (k = 0; k < 8; k++) {
        b_obj->inputVarSize1[k] = (unsigned int)inputSize[k];
      }

      exitg1 = true;
    } else {
      k++;
    }
  }

  CICDecimator_stepImpl(obj, varargin_1, varargout_1);
}

//
// Arguments    : dsp_private_FIRCombFilter *obj
//                const long long varargin_1[165]
//                long long varargout_1[165]
// Return Type  : void
//
void b_SystemCore_step(dsp_private_FIRCombFilter *obj, const long long
  varargin_1[165], long long varargout_1[165])
{
  dsp_private_FIRCombFilter *b_obj;
  if (obj->isInitialized != 1) {
    b_obj = obj;
    b_obj->isInitialized = 1;

    // System object Constructor function: dsp.Delay
    b_obj->cDelay.S0_isInitialized = 0;
    b_obj->cDelay.P0_IC = 0LL;
    if (b_obj->cDelay.S0_isInitialized == 1) {
      d_InitializeConditions(&b_obj->cDelay);
    }
  }

  FIRCombFilter_stepImpl(obj, varargin_1, varargout_1);
}

//
// Arguments    : dsp_private_FIRCombFilter_1 *obj
//                const long long varargin_1[165]
//                long long varargout_1[165]
// Return Type  : void
//
void c_SystemCore_step(dsp_private_FIRCombFilter_1 *obj, const long long
  varargin_1[165], long long varargout_1[165])
{
  dsp_private_FIRCombFilter_1 *b_obj;
  if (obj->isInitialized != 1) {
    b_obj = obj;
    b_obj->isInitialized = 1;

    // System object Constructor function: dsp.Delay
    b_obj->cDelay.S0_isInitialized = 0;
    b_obj->cDelay.P0_IC = 0LL;
    if (b_obj->cDelay.S0_isInitialized == 1) {
      e_InitializeConditions(&b_obj->cDelay);
    }
  }

  b_FIRCombFilter_stepImpl(obj, varargin_1, varargout_1);
}

//
// Arguments    : dsp_private_FIRCombFilter_2 *obj
//                const long long varargin_1[165]
//                long long varargout_1[165]
// Return Type  : void
//
void d_SystemCore_step(dsp_private_FIRCombFilter_2 *obj, const long long
  varargin_1[165], long long varargout_1[165])
{
  dsp_private_FIRCombFilter_2 *b_obj;
  if (obj->isInitialized != 1) {
    b_obj = obj;
    b_obj->isInitialized = 1;

    // System object Constructor function: dsp.Delay
    b_obj->cDelay.S0_isInitialized = 0;
    b_obj->cDelay.P0_IC = 0LL;
    if (b_obj->cDelay.S0_isInitialized == 1) {
      f_InitializeConditions(&b_obj->cDelay);
    }
  }

  c_FIRCombFilter_stepImpl(obj, varargin_1, varargout_1);
}

//
// File trailer for SystemCore.cpp
//
// [EOF]
//
