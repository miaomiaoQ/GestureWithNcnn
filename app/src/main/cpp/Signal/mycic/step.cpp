//
// File: step.cpp
//
// MATLAB Coder version            : 2.8
// C/C++ source code generated on  : 24-Mar-2017 13:57:42
//

// Include Files
#include "rt_nonfinite.h"
#include "MyCic.h"
#include "step.h"

// Function Definitions

//
// Arguments    : dsp_private_Integrator_0 *obj
// Return Type  : void
//
void Destructor(dsp_private_Integrator_0 *obj)
{
  // System object Destructor function: dsp.private.Integrator
  if ((obj->S0_isInitialized == 1) && (obj->S0_isInitialized != 2)) {
    obj->S0_isInitialized = 2;
  }
}

//
// Arguments    : dsp_private_Integrator_0 *obj
// Return Type  : void
//
void InitializeConditions(dsp_private_Integrator_0 *obj)
{
  // System object Initialization function: dsp.private.Integrator
  obj->W0_states = 0LL;
}

//
// Arguments    : dsp_private_Integrator_1 *obj
// Return Type  : void
//
void b_Destructor(dsp_private_Integrator_1 *obj)
{
  // System object Destructor function: dsp.private.Integrator
  if ((obj->S0_isInitialized == 1) && (obj->S0_isInitialized != 2)) {
    obj->S0_isInitialized = 2;
  }
}

//
// Arguments    : dsp_private_Integrator_1 *obj
// Return Type  : void
//
void b_InitializeConditions(dsp_private_Integrator_1 *obj)
{
  // System object Initialization function: dsp.private.Integrator
  obj->W0_states = 0LL;
}

//
// Arguments    : dsp_private_Integrator_2 *obj
// Return Type  : void
//
void c_Destructor(dsp_private_Integrator_2 *obj)
{
  // System object Destructor function: dsp.private.Integrator
  if ((obj->S0_isInitialized == 1) && (obj->S0_isInitialized != 2)) {
    obj->S0_isInitialized = 2;
  }
}

//
// Arguments    : dsp_private_Integrator_2 *obj
// Return Type  : void
//
void c_InitializeConditions(dsp_private_Integrator_2 *obj)
{
  // System object Initialization function: dsp.private.Integrator
  obj->W0_states = 0LL;
}

//
// Arguments    : dsp_Delay_3 *obj
// Return Type  : void
//
void d_Destructor(dsp_Delay_3 *obj)
{
  // System object Destructor function: dsp.Delay
  if ((obj->S0_isInitialized == 1) && (obj->S0_isInitialized != 2)) {
    obj->S0_isInitialized = 2;
  }
}

//
// Arguments    : dsp_Delay_3 *obj
// Return Type  : void
//
void d_InitializeConditions(dsp_Delay_3 *obj)
{
  int j;
  int delayIdx;

  // System object Initialization function: dsp.Delay
  obj->W0_CIRC_BUF_IDX = 0;
  j = 0;
  for (delayIdx = 0; delayIdx < 17; delayIdx++) {
    obj->W1_IC_BUFF[j] = obj->P0_IC;
    j++;
  }
}

//
// Arguments    : dsp_Delay_4 *obj
// Return Type  : void
//
void e_Destructor(dsp_Delay_4 *obj)
{
  // System object Destructor function: dsp.Delay
  if ((obj->S0_isInitialized == 1) && (obj->S0_isInitialized != 2)) {
    obj->S0_isInitialized = 2;
  }
}

//
// Arguments    : dsp_Delay_4 *obj
// Return Type  : void
//
void e_InitializeConditions(dsp_Delay_4 *obj)
{
  int j;
  int delayIdx;

  // System object Initialization function: dsp.Delay
  obj->W0_CIRC_BUF_IDX = 0;
  j = 0;
  for (delayIdx = 0; delayIdx < 17; delayIdx++) {
    obj->W1_IC_BUFF[j] = obj->P0_IC;
    j++;
  }
}

//
// Arguments    : dsp_Delay_5 *obj
// Return Type  : void
//
void f_Destructor(dsp_Delay_5 *obj)
{
  // System object Destructor function: dsp.Delay
  if ((obj->S0_isInitialized == 1) && (obj->S0_isInitialized != 2)) {
    obj->S0_isInitialized = 2;
  }
}

//
// Arguments    : dsp_Delay_5 *obj
// Return Type  : void
//
void f_InitializeConditions(dsp_Delay_5 *obj)
{
  int j;
  int delayIdx;

  // System object Initialization function: dsp.Delay
  obj->W0_CIRC_BUF_IDX = 0;
  j = 0;
  for (delayIdx = 0; delayIdx < 17; delayIdx++) {
    obj->W1_IC_BUFF[j] = obj->P0_IC;
    j++;
  }
}

//
// File trailer for step.cpp
//
// [EOF]
//
