/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Filter0.h
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

#ifndef RTW_HEADER_Filter0_h_
#define RTW_HEADER_Filter0_h_
#ifndef Filter0_COMMON_INCLUDES_
#define Filter0_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Filter0_COMMON_INCLUDES_ */

#include "Filter0_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T DigitalFilter_FILT_STATES[2]; /* '<S2>/Digital Filter' */
  real_T DigitalFilter_FILT_STATES_g[2];/* '<S3>/Digital Filter' */
} DW_Filter0_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T u1;                           /* '<Root>/u1' */
  real_T u2;                           /* '<Root>/u2' */
} ExtU_Filter0_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T y1;                           /* '<Root>/y1' */
  real_T y2;                           /* '<Root>/y2' */
} ExtY_Filter0_T;

/* Real-time Model Data Structure */
struct tag_RTM_Filter0_T {
  const char_T * volatile errorStatus;
};

/* Block states (default storage) */
extern DW_Filter0_T Filter0_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_Filter0_T Filter0_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_Filter0_T Filter0_Y;

/* Model entry point functions */
extern void Filter0_initialize(void);
extern void Filter0_step(void);
extern void Filter0_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Filter0_T *const Filter0_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S4>/Check Signal Attributes' : Unused code path elimination
 * Block '<S5>/Check Signal Attributes' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('SimuESP32/Filter')    - opens subsystem SimuESP32/Filter
 * hilite_system('SimuESP32/Filter/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'SimuESP32'
 * '<S1>'   : 'SimuESP32/Filter'
 * '<S2>'   : 'SimuESP32/Filter/Digital Filter Design'
 * '<S3>'   : 'SimuESP32/Filter/Digital Filter Design1'
 * '<S4>'   : 'SimuESP32/Filter/Digital Filter Design/Check Signal Attributes'
 * '<S5>'   : 'SimuESP32/Filter/Digital Filter Design1/Check Signal Attributes'
 */
#endif                                 /* RTW_HEADER_Filter0_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
