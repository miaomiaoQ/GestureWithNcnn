//
// File: FIRCombFilter.cpp
//
// MATLAB Coder version            : 2.8
// C/C++ source code generated on  : 24-Mar-2017 13:57:42
//

// Include Files
#include "rt_nonfinite.h"
#include "MyCic.h"
#include "FIRCombFilter.h"
#include "step.h"

// Function Definitions

//
// Arguments    : dsp_private_FIRCombFilter *obj
//                const long long in[165]
//                long long out[165]
// Return Type  : void
//
void FIRCombFilter_stepImpl(dsp_private_FIRCombFilter *obj, const long long in
  [165], long long out[165])
{
  dsp_Delay_3 *b_obj;
  int curCircBuff;
  int toWriteHead;
  int k;
  long long i1;
  b_obj = &obj->cDelay;
  if (b_obj->S0_isInitialized != 1) {
    b_obj->S0_isInitialized = 1;
    d_InitializeConditions(b_obj);
  }

  // System object Outputs function: dsp.Delay
  curCircBuff = b_obj->W0_CIRC_BUF_IDX;
  toWriteHead = 17 - curCircBuff;
  for (k = 0; k < toWriteHead; k++) {
    out[k] = b_obj->W1_IC_BUFF[curCircBuff + k];
  }

  for (k = 0; k < curCircBuff; k++) {
    out[toWriteHead + k] = b_obj->W1_IC_BUFF[k];
  }

  memcpy(&out[17], &in[0], 148U * sizeof(long long));

  // System object Update function: dsp.Delay
  for (k = 0; k < 17; k++) {
    b_obj->W1_IC_BUFF[k] = in[k + 148];
  }

  b_obj->W0_CIRC_BUF_IDX = 0;
  for (curCircBuff = 0; curCircBuff < 165; curCircBuff++) {
    i1 = in[curCircBuff] - out[curCircBuff];
    if ((i1 & 1152921504606846976LL) != 0LL) {
      out[curCircBuff] = i1 | -1152921504606846976LL;
    } else {
      out[curCircBuff] = i1 & 1152921504606846975LL;
    }
  }
}

//
// Arguments    : dsp_private_FIRCombFilter_1 *obj
//                const long long in[165]
//                long long out[165]
// Return Type  : void
//
void b_FIRCombFilter_stepImpl(dsp_private_FIRCombFilter_1 *obj, const long long
  in[165], long long out[165])
{
  dsp_Delay_4 *b_obj;
  int curCircBuff;
  int toWriteHead;
  int k;
  long long i2;
  b_obj = &obj->cDelay;
  if (b_obj->S0_isInitialized != 1) {
    b_obj->S0_isInitialized = 1;
    e_InitializeConditions(b_obj);
  }

  // System object Outputs function: dsp.Delay
  curCircBuff = b_obj->W0_CIRC_BUF_IDX;
  toWriteHead = 17 - curCircBuff;
  for (k = 0; k < toWriteHead; k++) {
    out[k] = b_obj->W1_IC_BUFF[curCircBuff + k];
  }

  for (k = 0; k < curCircBuff; k++) {
    out[toWriteHead + k] = b_obj->W1_IC_BUFF[k];
  }

  memcpy(&out[17], &in[0], 148U * sizeof(long long));

  // System object Update function: dsp.Delay
  for (k = 0; k < 17; k++) {
    b_obj->W1_IC_BUFF[k] = in[k + 148];
  }

  b_obj->W0_CIRC_BUF_IDX = 0;
  for (curCircBuff = 0; curCircBuff < 165; curCircBuff++) {
    i2 = in[curCircBuff] - out[curCircBuff];
    if ((i2 & 1152921504606846976LL) != 0LL) {
      out[curCircBuff] = i2 | -1152921504606846976LL;
    } else {
      out[curCircBuff] = i2 & 1152921504606846975LL;
    }
  }
}

//
// Arguments    : dsp_private_FIRCombFilter_2 *obj
//                const long long in[165]
//                long long out[165]
// Return Type  : void
//
void c_FIRCombFilter_stepImpl(dsp_private_FIRCombFilter_2 *obj, const long long
  in[165], long long out[165])
{
  dsp_Delay_5 *b_obj;
  int curCircBuff;
  int toWriteHead;
  int k;
  long long i3;
  b_obj = &obj->cDelay;
  if (b_obj->S0_isInitialized != 1) {
    b_obj->S0_isInitialized = 1;
    f_InitializeConditions(b_obj);
  }

  // System object Outputs function: dsp.Delay
  curCircBuff = b_obj->W0_CIRC_BUF_IDX;
  toWriteHead = 17 - curCircBuff;
  for (k = 0; k < toWriteHead; k++) {
    out[k] = b_obj->W1_IC_BUFF[curCircBuff + k];
  }

  for (k = 0; k < curCircBuff; k++) {
    out[toWriteHead + k] = b_obj->W1_IC_BUFF[k];
  }

  memcpy(&out[17], &in[0], 148U * sizeof(long long));

  // System object Update function: dsp.Delay
  for (k = 0; k < 17; k++) {
    b_obj->W1_IC_BUFF[k] = in[k + 148];
  }

  b_obj->W0_CIRC_BUF_IDX = 0;
  for (curCircBuff = 0; curCircBuff < 165; curCircBuff++) {
    i3 = in[curCircBuff] - out[curCircBuff];
    if ((i3 & 1152921504606846976LL) != 0LL) {
      out[curCircBuff] = i3 | -1152921504606846976LL;
    } else {
      out[curCircBuff] = i3 & 1152921504606846975LL;
    }
  }
}

//
// File trailer for FIRCombFilter.cpp
//
// [EOF]
//
