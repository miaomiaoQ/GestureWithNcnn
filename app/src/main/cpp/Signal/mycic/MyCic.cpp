//
// File: MyCic.cpp
//
// MATLAB Coder version            : 2.8
// C/C++ source code generated on  : 24-Mar-2017 13:57:42
//

// Include Files
#include "rt_nonfinite.h"
#include "MyCic.h"
#include "step.h"
#include "SystemCore.h"

// Function Definitions

//
// Arguments    : const int I[6600]
//                long long II[165]
// Return Type  : void
//
void MyCic(const int I[6600], long long II[165])
{
  static dsp_CICDecimator_2 hd;
  hd.isInitialized = 0;
  SystemCore_step(&hd, I, II);
  c_Destructor(&hd.cIntgStage3);
  f_Destructor(&hd.cCmbStage3.cDelay);
  b_Destructor(&hd.cIntgStage2);
  e_Destructor(&hd.cCmbStage2.cDelay);
  Destructor(&hd.cIntgStage1);
  d_Destructor(&hd.cCmbStage1.cDelay);
}

//
// File trailer for MyCic.cpp
//
// [EOF]
//
