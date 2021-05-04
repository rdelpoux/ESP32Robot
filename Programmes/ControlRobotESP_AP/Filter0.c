/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Filter0.c
 *
 * Code generated for Simulink model 'Filter0'.
 *
 * Model version                  : 1.2
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Tue Apr 27 22:00:35 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Filter0.h"
#include "Filter0_private.h"

/* Block states (default storage) */
DW_Filter0_T Filter0_DW;

/* External inputs (root inport signals with default storage) */
ExtU_Filter0_T Filter0_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Filter0_T Filter0_Y;

/* Real-time model */
static RT_MODEL_Filter0_T Filter0_M_;
RT_MODEL_Filter0_T *const Filter0_M = &Filter0_M_;

/* Model step function */
void Filter0_step(void)
{
  real_T denAccum;

  /* S-Function (sdspbiquad): '<S2>/Digital Filter' incorporates:
   *  Inport: '<Root>/u1'
   */
  denAccum = (0.0674552738890719 * Filter0_U.u1 - -1.1429805025399011 *
              Filter0_DW.DigitalFilter_FILT_STATES[0]) - 0.41280159809618877 *
    Filter0_DW.DigitalFilter_FILT_STATES[1];

  /* Outport: '<Root>/y1' incorporates:
   *  S-Function (sdspbiquad): '<S2>/Digital Filter'
   */
  Filter0_Y.y1 = (2.0 * Filter0_DW.DigitalFilter_FILT_STATES[0] + denAccum) +
    Filter0_DW.DigitalFilter_FILT_STATES[1];

  /* S-Function (sdspbiquad): '<S2>/Digital Filter' */
  Filter0_DW.DigitalFilter_FILT_STATES[1] =
    Filter0_DW.DigitalFilter_FILT_STATES[0];
  Filter0_DW.DigitalFilter_FILT_STATES[0] = denAccum;

  /* S-Function (sdspbiquad): '<S3>/Digital Filter' incorporates:
   *  Inport: '<Root>/u2'
   */
  denAccum = (0.0674552738890719 * Filter0_U.u2 - -1.1429805025399011 *
              Filter0_DW.DigitalFilter_FILT_STATES_g[0]) - 0.41280159809618877 *
    Filter0_DW.DigitalFilter_FILT_STATES_g[1];

  /* Outport: '<Root>/y2' incorporates:
   *  S-Function (sdspbiquad): '<S3>/Digital Filter'
   */
  Filter0_Y.y2 = (2.0 * Filter0_DW.DigitalFilter_FILT_STATES_g[0] + denAccum) +
    Filter0_DW.DigitalFilter_FILT_STATES_g[1];

  /* S-Function (sdspbiquad): '<S3>/Digital Filter' */
  Filter0_DW.DigitalFilter_FILT_STATES_g[1] =
    Filter0_DW.DigitalFilter_FILT_STATES_g[0];
  Filter0_DW.DigitalFilter_FILT_STATES_g[0] = denAccum;
}

/* Model initialize function */
void Filter0_initialize(void)
{
  /* (no initialization code required) */
}

/* Model terminate function */
void Filter0_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
