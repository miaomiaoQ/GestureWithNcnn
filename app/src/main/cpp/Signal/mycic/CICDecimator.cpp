//
// File: CICDecimator.cpp
//
// MATLAB Coder version            : 2.8
// C/C++ source code generated on  : 24-Mar-2017 13:57:42
//

// Include Files
#include "rt_nonfinite.h"
#include "MyCic.h"
#include "CICDecimator.h"
#include "SystemCore.h"

// Function Definitions

//
// Arguments    : dsp_CICDecimator_2 *obj
//                const int in[6600]
//                long long out[165]
// Return Type  : void
//
void CICDecimator_stepImpl(dsp_CICDecimator_2 *obj, const int in[6600], long
  long out[165])
{
  dsp_private_Integrator_0 *b_obj;
  int i;
  int j;
  long long i0;
  long long y[6600];
  dsp_private_Integrator_1 *c_obj;
  dsp_private_Integrator_2 *d_obj;
  long long b_y[165];
  b_obj = &obj->cIntgStage1;
  if (b_obj->S0_isInitialized != 1) {
    b_obj->S0_isInitialized = 1;

    // System object Initialization function: dsp.private.Integrator
    b_obj->W0_states = 0LL;
  }

  // System object Outputs function: dsp.private.Integrator
  i = 0;
  for (j = 0; j < 6600; j++) {
    b_obj->O0_Y0[i] = b_obj->W0_states;
    i0 = b_obj->W0_states + in[i];
    if ((i0 & 1152921504606846976LL) != 0LL) {
      b_obj->W0_states = i0 | -1152921504606846976LL;
    } else {
      b_obj->W0_states = i0 & 1152921504606846975LL;
    }

    i++;
  }

  for (i = 0; i < 6600; i++) {
    y[i] = b_obj->O0_Y0[i];
  }

  c_obj = &obj->cIntgStage2;
  if (c_obj->S0_isInitialized != 1) {
    c_obj->S0_isInitialized = 1;

    // System object Initialization function: dsp.private.Integrator
    c_obj->W0_states = 0LL;
  }

  // System object Outputs function: dsp.private.Integrator
  i = 0;
  for (j = 0; j < 6600; j++) {
    c_obj->O0_Y0[i] = c_obj->W0_states;
    i0 = c_obj->W0_states + y[i];
    if ((i0 & 1152921504606846976LL) != 0LL) {
      c_obj->W0_states = i0 | -1152921504606846976LL;
    } else {
      c_obj->W0_states = i0 & 1152921504606846975LL;
    }

    i++;
  }

  for (i = 0; i < 6600; i++) {
    y[i] = c_obj->O0_Y0[i];
  }

  d_obj = &obj->cIntgStage3;
  if (d_obj->S0_isInitialized != 1) {
    d_obj->S0_isInitialized = 1;

    // System object Initialization function: dsp.private.Integrator
    d_obj->W0_states = 0LL;
  }

  // System object Outputs function: dsp.private.Integrator
  i = 0;
  for (j = 0; j < 6600; j++) {
    d_obj->O0_Y0[i] = d_obj->W0_states;
    i0 = d_obj->W0_states + y[i];
    if ((i0 & 1152921504606846976LL) != 0LL) {
      d_obj->W0_states = i0 | -1152921504606846976LL;
    } else {
      d_obj->W0_states = i0 & 1152921504606846975LL;
    }

    i++;
  }

  for (i = 0; i < 6600; i++) {
    y[i] = d_obj->O0_Y0[i];
  }

  for (i = 0; i < 165; i++) {
    b_y[i] = y[40 * i];
  }

  b_SystemCore_step(&obj->cCmbStage1, b_y, out);
  memcpy(&b_y[0], &out[0], 165U * sizeof(long long));
  c_SystemCore_step(&obj->cCmbStage2, b_y, out);
  memcpy(&b_y[0], &out[0], 165U * sizeof(long long));
  d_SystemCore_step(&obj->cCmbStage3, b_y, out);
}

//
// File trailer for CICDecimator.cpp
//
// [EOF]
//