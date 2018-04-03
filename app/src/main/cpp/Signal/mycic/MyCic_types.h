//
// File: MyCic_types.h
//
// MATLAB Coder version            : 2.8
// C/C++ source code generated on  : 24-Mar-2017 13:57:42
//
#ifndef __MYCIC_TYPES_H__
#define __MYCIC_TYPES_H__

// Include Files
#include "rtwtypes.h"

// Type Definitions
#ifndef struct_dsp_Delay_3
#define struct_dsp_Delay_3

struct dsp_Delay_3
{
  int S0_isInitialized;
  int W0_CIRC_BUF_IDX;
  long long W1_IC_BUFF[17];
  int W2_PrevNumChan;
  boolean_T W3_NeedsToInit;
  long long P0_IC;
};

#endif                                 //struct_dsp_Delay_3

typedef struct {
  int isInitialized;
  dsp_Delay_3 cDelay;
} dsp_private_FIRCombFilter;

#ifndef struct_dsp_Delay_4
#define struct_dsp_Delay_4

struct dsp_Delay_4
{
  int S0_isInitialized;
  int W0_CIRC_BUF_IDX;
  long long W1_IC_BUFF[17];
  int W2_PrevNumChan;
  boolean_T W3_NeedsToInit;
  long long P0_IC;
};

#endif                                 //struct_dsp_Delay_4

typedef struct {
  int isInitialized;
  dsp_Delay_4 cDelay;
} dsp_private_FIRCombFilter_1;

#ifndef struct_dsp_Delay_5
#define struct_dsp_Delay_5

struct dsp_Delay_5
{
  int S0_isInitialized;
  int W0_CIRC_BUF_IDX;
  long long W1_IC_BUFF[17];
  int W2_PrevNumChan;
  boolean_T W3_NeedsToInit;
  long long P0_IC;
};

#endif                                 //struct_dsp_Delay_5

typedef struct {
  int isInitialized;
  dsp_Delay_5 cDelay;
} dsp_private_FIRCombFilter_2;

#ifndef struct_dsp_private_Integrator_0
#define struct_dsp_private_Integrator_0

struct dsp_private_Integrator_0
{
  int S0_isInitialized;
  long long W0_states;
  long long O0_Y0[6600];
};

#endif                                 //struct_dsp_private_Integrator_0

#ifndef struct_dsp_private_Integrator_1
#define struct_dsp_private_Integrator_1

struct dsp_private_Integrator_1
{
  int S0_isInitialized;
  long long W0_states;
  long long O0_Y0[6600];
};

#endif                                 //struct_dsp_private_Integrator_1

#ifndef struct_dsp_private_Integrator_2
#define struct_dsp_private_Integrator_2

struct dsp_private_Integrator_2
{
  int S0_isInitialized;
  long long W0_states;
  long long O0_Y0[6600];
};

#endif                                 //struct_dsp_private_Integrator_2

typedef struct {
  int isInitialized;
  unsigned int inputVarSize1[8];
  dsp_private_FIRCombFilter cCmbStage1;
  dsp_private_Integrator_0 cIntgStage1;
  dsp_private_FIRCombFilter_1 cCmbStage2;
  dsp_private_Integrator_1 cIntgStage2;
  dsp_private_FIRCombFilter_2 cCmbStage3;
  dsp_private_Integrator_2 cIntgStage3;
} dsp_CICDecimator_2;

#endif

//
// File trailer for MyCic_types.h
//
// [EOF]
//
