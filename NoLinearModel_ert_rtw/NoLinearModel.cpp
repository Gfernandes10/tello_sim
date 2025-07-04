//
// Sponsored License - for use in support of a program or activity
// sponsored by MathWorks.  Not for government, commercial or other
// non-sponsored organizational use.
//
// File: NoLinearModel.cpp
//
// Code generated for Simulink model 'NoLinearModel'.
//
// Model version                  : 1.61
// Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
// C/C++ source code generated on : Thu Jul  3 20:11:10 2025
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "NoLinearModel.h"
#include <cmath>
#include "rtwtypes.h"

// Model step function
void NoLinearModel::step()
{
  real_T cosOut;
  real_T sinOut;

  // Outport: '<Root>/dx_mps' incorporates:
  //   DiscreteIntegrator: '<S1>/dx'

  rtY.dx_mps = rtDW.dx_DSTATE;

  // Outport: '<Root>/x_m' incorporates:
  //   DiscreteIntegrator: '<S1>/x'

  rtY.x_m = rtDW.x_DSTATE;

  // Outport: '<Root>/pitch_rad' incorporates:
  //   DiscreteIntegrator: '<S1>/pitch'

  rtY.pitch_rad = rtDW.pitch_DSTATE;

  // Outport: '<Root>/dpitch_radps' incorporates:
  //   DiscreteIntegrator: '<S1>/dpitch'

  rtY.dpitch_radps = rtDW.dpitch_DSTATE;

  // Outport: '<Root>/dy_mps' incorporates:
  //   DiscreteIntegrator: '<S1>/dy'

  rtY.dy_mps = rtDW.dy_DSTATE;

  // Outport: '<Root>/y_m' incorporates:
  //   DiscreteIntegrator: '<S1>/y'

  rtY.y_m = rtDW.y_DSTATE;

  // Outport: '<Root>/roll_rad' incorporates:
  //   DiscreteIntegrator: '<S1>/roll'

  rtY.roll_rad = rtDW.roll_DSTATE;

  // Outport: '<Root>/roll_radps' incorporates:
  //   DiscreteIntegrator: '<S1>/droll'

  rtY.roll_radps = rtDW.droll_DSTATE;

  // Outport: '<Root>/yaw_rad' incorporates:
  //   DiscreteIntegrator: '<S1>/yaw'

  rtY.yaw_rad = rtDW.yaw_DSTATE;

  // Outport: '<Root>/dyaw_radps' incorporates:
  //   DiscreteIntegrator: '<S1>/dyaw'

  rtY.dyaw_radps = rtDW.dyaw_DSTATE;

  // Outport: '<Root>/dz_mps' incorporates:
  //   DiscreteIntegrator: '<S1>/dz'

  rtY.dz_mps = rtDW.dz_DSTATE;

  // Outport: '<Root>/z_m' incorporates:
  //   DiscreteIntegrator: '<S1>/z'

  rtY.z_m = rtDW.z_DSTATE;

  // Trigonometry: '<S1>/Cos2' incorporates:
  //   Outport: '<Root>/roll_rad'

  cosOut = rtY.roll_rad;
  sinOut = std::sin(cosOut);
  cosOut = std::cos(cosOut);

  // Trigonometry: '<S1>/Cos2'
  rtDW.Cos2_o1 = sinOut;

  // Trigonometry: '<S1>/Cos2'
  rtDW.Cos2_o2 = cosOut;

  // Trigonometry: '<S1>/Cos3' incorporates:
  //   Outport: '<Root>/pitch_rad'

  cosOut = rtY.pitch_rad;
  sinOut = std::sin(cosOut);
  cosOut = std::cos(cosOut);

  // Trigonometry: '<S1>/Cos3'
  rtDW.Cos3_o1 = sinOut;

  // Trigonometry: '<S1>/Cos3'
  rtDW.Cos3_o2 = cosOut;

  // Trigonometry: '<S1>/Cos4' incorporates:
  //   Outport: '<Root>/yaw_rad'

  cosOut = rtY.yaw_rad;
  sinOut = std::sin(cosOut);
  cosOut = std::cos(cosOut);

  // Trigonometry: '<S1>/Cos4'
  rtDW.Cos4_o1 = sinOut;

  // Trigonometry: '<S1>/Cos4'
  rtDW.Cos4_o2 = cosOut;

  // Gain: '<S1>/Gain' incorporates:
  //   Inport: '<Root>/uyaw'

  rtDW.Gain = -rtU.uyaw;

  // Product: '<S1>/Divide' incorporates:
  //   Constant: '<S2>/Constant11'
  //   Constant: '<S2>/Constant8'
  //   Constant: '<S2>/Constant9'

  rtDW.Divide = rtDW.Gain * rtInstP.yawp_K * rtInstP.yawp_max / rtInstP.yawp_tal;

  // Product: '<S1>/Divide1' incorporates:
  //   Constant: '<S2>/Constant11'
  //   Outport: '<Root>/dyaw_radps'

  rtDW.Divide1 = rtY.dyaw_radps / rtInstP.yawp_tal;

  // Product: '<S1>/Divide2' incorporates:
  //   Constant: '<S2>/Constant10'
  //   Constant: '<S2>/Constant12'
  //   Constant: '<S2>/Constant13'
  //   Inport: '<Root>/uzp'

  rtDW.Divide2 = rtU.uzp * rtInstP.zp_K * rtInstP.zp_max / rtInstP.zp_tal;

  // Product: '<S1>/Divide3' incorporates:
  //   Constant: '<S2>/Constant10'
  //   Outport: '<Root>/dz_mps'

  rtDW.Divide3 = rtY.dz_mps / rtInstP.zp_tal;

  // Sum: '<S1>/Sum2'
  rtDW.z2p_mps2 = rtDW.Divide2 - rtDW.Divide3;

  // Sum: '<S1>/Sum4' incorporates:
  //   Constant: '<S1>/Constant3'

  rtDW.Sum4 = rtDW.z2p_mps2 + 9.81;

  // Product: '<S1>/Product6'
  rtDW.Product6 = rtDW.Cos2_o2 * rtDW.Cos3_o2;

  // Product: '<S1>/Divide4' incorporates:
  //   Constant: '<S1>/Constant2'

  rtDW.Divide4 = rtDW.Sum4 * 0.8 / rtDW.Product6;

  // Product: '<S1>/Divide5' incorporates:
  //   Constant: '<S1>/Constant4'
  //   Product: '<S1>/Divide6'

  cosOut = rtDW.Divide4 / 0.8;

  // Product: '<S1>/Divide5'
  rtDW.Divide5 = cosOut;

  // Product: '<S1>/Divide6'
  rtDW.Divide6 = cosOut;

  // Product: '<S1>/Product' incorporates:
  //   Constant: '<S2>/Constant'
  //   Constant: '<S2>/Constant1'
  //   Constant: '<S2>/Constant2'
  //   Inport: '<Root>/uroll'

  rtDW.Product = rtU.uroll * rtInstP.roll_K * rtInstP.roll_omega *
    rtInstP.roll_omega * rtInstP.roll_max;

  // Product: '<S1>/Product1' incorporates:
  //   Constant: '<S1>/Constant'
  //   Constant: '<S2>/Constant1'
  //   Constant: '<S2>/Constant3'
  //   Outport: '<Root>/roll_radps'

  rtDW.Product1 = rtInstP.roll_zeta * rtInstP.roll_omega * 2.0 * rtY.roll_radps;

  // Product: '<S1>/Product10' incorporates:
  //   Constant: '<S2>/Constant14'
  //   Outport: '<Root>/dx_mps'

  rtDW.Product10 = rtY.dx_mps * rtInstP.Cx;

  // Product: '<S1>/Product11' incorporates:
  //   Constant: '<S2>/Constant15'
  //   Outport: '<Root>/dy_mps'

  rtDW.Product11 = rtY.dy_mps * rtInstP.Cy;

  // Product: '<S1>/Product12'
  rtDW.Product12 = rtDW.Cos4_o2 * rtDW.Cos2_o1;

  // Product: '<S1>/Product13'
  rtDW.Product13 = rtDW.Cos4_o1 * rtDW.Cos2_o2 * rtDW.Cos3_o1;

  // Sum: '<S1>/Sum7'
  rtDW.Sum7 = rtDW.Product13 - rtDW.Product12;

  // Product: '<S1>/Product14'
  rtDW.Product14 = rtDW.Divide6 * rtDW.Sum7;

  // Product: '<S1>/Product2' incorporates:
  //   Constant: '<S2>/Constant1'
  //   Outport: '<Root>/roll_rad'

  rtDW.Product2 = rtInstP.roll_omega * rtInstP.roll_omega * rtY.roll_rad;

  // Product: '<S1>/Product3' incorporates:
  //   Constant: '<S2>/Constant4'
  //   Constant: '<S2>/Constant5'
  //   Constant: '<S2>/Constant6'
  //   Inport: '<Root>/upitch'

  rtDW.Product3 = rtU.upitch * rtInstP.pitch_K * rtInstP.pitch_omega *
    rtInstP.pitch_omega * rtInstP.pitch_max;

  // Product: '<S1>/Product4' incorporates:
  //   Constant: '<S1>/Constant1'
  //   Constant: '<S2>/Constant5'
  //   Constant: '<S2>/Constant7'
  //   Outport: '<Root>/dpitch_radps'

  rtDW.Product4 = rtInstP.pitch_zeta * rtInstP.pitch_omega * 2.0 *
    rtY.dpitch_radps;

  // Product: '<S1>/Product5' incorporates:
  //   Constant: '<S2>/Constant5'
  //   Outport: '<Root>/pitch_rad'

  rtDW.Product5 = rtInstP.pitch_omega * rtInstP.pitch_omega * rtY.pitch_rad;

  // Product: '<S1>/Product7'
  rtDW.Product7 = rtDW.Cos4_o1 * rtDW.Cos2_o1;

  // Product: '<S1>/Product8'
  rtDW.Product8 = rtDW.Cos4_o2 * rtDW.Cos2_o2 * rtDW.Cos3_o1;

  // Sum: '<S1>/Sum5'
  rtDW.Sum5 = rtDW.Product7 + rtDW.Product8;

  // Product: '<S1>/Product9'
  rtDW.Product9 = rtDW.Divide5 * rtDW.Sum5;

  // Sum: '<S1>/Sum'
  rtDW.d2roll_radps2 = (rtDW.Product - rtDW.Product1) - rtDW.Product2;

  // Sum: '<S1>/Sum1'
  rtDW.d2pitch_radps2 = (rtDW.Product3 - rtDW.Product4) - rtDW.Product5;

  // Sum: '<S1>/Sum3'
  rtDW.d2yaw_radps2 = rtDW.Divide - rtDW.Divide1;

  // Sum: '<S1>/Sum6'
  rtDW.d2x_mps2 = rtDW.Product9 - rtDW.Product10;

  // Sum: '<S1>/Sum8'
  rtDW.d2y_mps = rtDW.Product14 - rtDW.Product11;

  // Update for DiscreteIntegrator: '<S1>/dx'
  rtDW.dx_DSTATE += 0.01 * rtDW.d2x_mps2;

  // Update for DiscreteIntegrator: '<S1>/x' incorporates:
  //   Outport: '<Root>/dx_mps'

  rtDW.x_DSTATE += 0.01 * rtY.dx_mps;

  // Update for DiscreteIntegrator: '<S1>/pitch' incorporates:
  //   Outport: '<Root>/dpitch_radps'

  rtDW.pitch_DSTATE += 0.01 * rtY.dpitch_radps;

  // Update for DiscreteIntegrator: '<S1>/dpitch'
  rtDW.dpitch_DSTATE += 0.01 * rtDW.d2pitch_radps2;

  // Update for DiscreteIntegrator: '<S1>/dy'
  rtDW.dy_DSTATE += 0.01 * rtDW.d2y_mps;

  // Update for DiscreteIntegrator: '<S1>/y' incorporates:
  //   Outport: '<Root>/dy_mps'

  rtDW.y_DSTATE += 0.01 * rtY.dy_mps;

  // Update for DiscreteIntegrator: '<S1>/roll' incorporates:
  //   Outport: '<Root>/roll_radps'

  rtDW.roll_DSTATE += 0.01 * rtY.roll_radps;

  // Update for DiscreteIntegrator: '<S1>/droll'
  rtDW.droll_DSTATE += 0.01 * rtDW.d2roll_radps2;

  // Update for DiscreteIntegrator: '<S1>/yaw' incorporates:
  //   Outport: '<Root>/dyaw_radps'

  rtDW.yaw_DSTATE += 0.01 * rtY.dyaw_radps;

  // Update for DiscreteIntegrator: '<S1>/dyaw'
  rtDW.dyaw_DSTATE += 0.01 * rtDW.d2yaw_radps2;

  // Update for DiscreteIntegrator: '<S1>/dz'
  rtDW.dz_DSTATE += 0.01 * rtDW.z2p_mps2;

  // Update for DiscreteIntegrator: '<S1>/z' incorporates:
  //   Outport: '<Root>/dz_mps'

  rtDW.z_DSTATE += 0.01 * rtY.dz_mps;
}

// Model initialize function
void NoLinearModel::initialize()
{
  // (no initialization code required)
}

// Root outports get method
const NoLinearModel::ExtY &NoLinearModel::getExternalOutputs() const
{
  return rtY;
}

// Constructor
NoLinearModel::NoLinearModel():
  rtU(),
  rtY(),
  rtDW()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
NoLinearModel::~NoLinearModel() = default;

//
// File trailer for generated code.
//
// [EOF]
//
