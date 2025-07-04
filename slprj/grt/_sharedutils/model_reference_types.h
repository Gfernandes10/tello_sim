/*
 * model_reference_types.h
 *
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 *
 * Code generation for model "NumLinearModel".
 *
 * Model version              : 6.27
 * Simulink Coder version : 25.1 (R2025a) 21-Nov-2024
 * C++ source code generated on : Fri May 30 20:21:36 2025
 */

#ifndef MODEL_REFERENCE_TYPES_H
#define MODEL_REFERENCE_TYPES_H
#include "rtwtypes.h"
#ifndef MODEL_REFERENCE_TYPES
#define MODEL_REFERENCE_TYPES

/*===========================================================================*
 * Model reference type definitions                                          *
 *===========================================================================*/
/*
 * This structure is used by model reference to
 * communicate timing information through the hierarchy.
 */
typedef struct _rtTimingBridge_tag rtTimingBridge;
struct _rtTimingBridge_tag {
  uint32_T nTasks;
  uint32_T** clockTick;
  uint32_T** clockTickH;
  uint32_T* taskCounter;
  real_T** taskTime;
  boolean_T** rateTransition;
  boolean_T *firstInitCond;
};

/*
 * This structure is used by model reference to
 * communicate variable discrete rate timing information through the hierarchy.
 */
typedef struct _rtCtrlRateMdlRefTiming_tag rtCtrlRateMdlRefTiming;
struct _rtCtrlRateMdlRefTiming_tag {
  uint32_T firstCtrlRateTID;
  uint32_T* numTicksToNextHitForCtrlRate;
};

#endif                                 /* MODEL_REFERENCE_TYPES */
#endif                                 /* MODEL_REFERENCE_TYPES_H */
