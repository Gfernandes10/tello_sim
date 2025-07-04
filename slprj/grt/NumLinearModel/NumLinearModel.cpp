/*
 * Code generation for system model 'NumLinearModel'
 *
 * Model                      : NumLinearModel
 * Model version              : 6.27
 * Simulink Coder version : 25.1 (R2025a) 21-Nov-2024
 * C++ source code generated on : Fri May 30 20:24:35 2025
 *
 * Note that the functions contained in this file are part of a Simulink
 * model, and are not self-contained algorithms.
 */

#include "NumLinearModel.h"
#include "rtwtypes.h"
#include <cmath>
#include "NumLinearModel_private.h"

P_NumLinearModel_T NumLinearModel::NumLinearModel_rtP{
  /* Computed Parameter: u_control_out_Y0
   * Referenced by: '<S1>/u_control_out'
   */
  {
    0.0,                               /* uphi */
    0.0,                               /* utheta */
    0.0,                               /* uzp */
    0.0                                /* uyaw */
  },

  /* Expression: 0.0
   * Referenced by: '<S1>/Delay'
   */
  0.0,

  /* Expression: 0.0
   * Referenced by: '<S1>/Delay1'
   */
  0.0,

  /* Expression: 0.0
   * Referenced by: '<S1>/Delay2'
   */
  0.0,

  /* Expression: 0.0
   * Referenced by: '<S1>/Delay3'
   */
  0.0,

  /* Expression: 2
   * Referenced by: '<S2>/Constant'
   */
  2.0,

  /* Expression: 2
   * Referenced by: '<S2>/Constant1'
   */
  2.0,

  /* Computed Parameter: Integrator1_gainval
   * Referenced by: '<S2>/Integrator1'
   */
  0.01,

  /* Expression: 0
   * Referenced by: '<S2>/Integrator1'
   */
  0.0,

  /* Computed Parameter: Integrator3_gainval
   * Referenced by: '<S2>/Integrator3'
   */
  0.01,

  /* Expression: 0
   * Referenced by: '<S2>/Integrator3'
   */
  0.0,

  /* Computed Parameter: Integrator5_gainval
   * Referenced by: '<S2>/Integrator5'
   */
  0.01,

  /* Expression: 0
   * Referenced by: '<S2>/Integrator5'
   */
  0.0,

  /* Computed Parameter: Integrator4_gainval
   * Referenced by: '<S2>/Integrator4'
   */
  0.01,

  /* Expression: 0
   * Referenced by: '<S2>/Integrator4'
   */
  0.0,

  /* Computed Parameter: Integrator6_gainval
   * Referenced by: '<S2>/Integrator6'
   */
  0.01,

  /* Expression: 0
   * Referenced by: '<S2>/Integrator6'
   */
  0.0,

  /* Computed Parameter: Integrator_gainval
   * Referenced by: '<S2>/Integrator'
   */
  0.01,

  /* Expression: 0
   * Referenced by: '<S2>/Integrator'
   */
  0.0,

  /* Computed Parameter: Integrator10_gainval
   * Referenced by: '<S2>/Integrator10'
   */
  0.01,

  /* Expression: 0
   * Referenced by: '<S2>/Integrator10'
   */
  0.0,

  /* Computed Parameter: Integrator11_gainval
   * Referenced by: '<S2>/Integrator11'
   */
  0.01,

  /* Expression: 0
   * Referenced by: '<S2>/Integrator11'
   */
  0.0,

  /* Computed Parameter: Integrator2_gainval
   * Referenced by: '<S2>/Integrator2'
   */
  0.01,

  /* Expression: 0
   * Referenced by: '<S2>/Integrator2'
   */
  0.0,

  /* Computed Parameter: Integrator7_gainval
   * Referenced by: '<S2>/Integrator7'
   */
  0.01,

  /* Expression: 0
   * Referenced by: '<S2>/Integrator7'
   */
  0.0,

  /* Computed Parameter: Integrator8_gainval
   * Referenced by: '<S2>/Integrator8'
   */
  0.01,

  /* Expression: 0
   * Referenced by: '<S2>/Integrator8'
   */
  0.0,

  /* Computed Parameter: Integrator9_gainval
   * Referenced by: '<S2>/Integrator9'
   */
  0.01,

  /* Expression: 0
   * Referenced by: '<S2>/Integrator9'
   */
  0.0
};

/* System initialize for referenced model: 'NumLinearModel' */
void NumLinearModel::init(void)
{
  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator1' */
  NumLinearModel_DW.Integrator1_DSTATE = NumLinearModel_rtP.Integrator1_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator3' */
  NumLinearModel_DW.Integrator3_DSTATE = NumLinearModel_rtP.Integrator3_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator5' */
  NumLinearModel_DW.Integrator5_DSTATE = NumLinearModel_rtP.Integrator5_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator4' */
  NumLinearModel_DW.Integrator4_DSTATE = NumLinearModel_rtP.Integrator4_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator6' */
  NumLinearModel_DW.Integrator6_DSTATE = NumLinearModel_rtP.Integrator6_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator' */
  NumLinearModel_DW.Integrator_DSTATE = NumLinearModel_rtP.Integrator_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator10' */
  NumLinearModel_DW.Integrator10_DSTATE = NumLinearModel_rtP.Integrator10_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator11' */
  NumLinearModel_DW.Integrator11_DSTATE = NumLinearModel_rtP.Integrator11_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator2' */
  NumLinearModel_DW.Integrator2_DSTATE = NumLinearModel_rtP.Integrator2_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator7' */
  NumLinearModel_DW.Integrator7_DSTATE = NumLinearModel_rtP.Integrator7_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator8' */
  NumLinearModel_DW.Integrator8_DSTATE = NumLinearModel_rtP.Integrator8_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator9' */
  NumLinearModel_DW.Integrator9_DSTATE = NumLinearModel_rtP.Integrator9_IC;

  /* SystemInitialize for Enabled SubSystem: '<Root>/InputDelay' */
  /* InitializeConditions for Delay: '<S1>/Delay' */
  NumLinearModel_DW.Delay_DSTATE = NumLinearModel_rtP.Delay_InitialCondition;

  /* InitializeConditions for Delay: '<S1>/Delay1' */
  NumLinearModel_DW.Delay1_DSTATE = NumLinearModel_rtP.Delay1_InitialCondition;

  /* InitializeConditions for Delay: '<S1>/Delay2' */
  NumLinearModel_DW.Delay2_DSTATE = NumLinearModel_rtP.Delay2_InitialCondition;

  /* InitializeConditions for Delay: '<S1>/Delay3' */
  NumLinearModel_DW.Delay3_DSTATE = NumLinearModel_rtP.Delay3_InitialCondition;

  /* SystemInitialize for Delay: '<S1>/Delay' incorporates:
   *  Outport: '<S1>/u_control_out'
   */
  NumLinearModel_B.uphi = NumLinearModel_rtP.u_control_out_Y0.uphi;

  /* SystemInitialize for Delay: '<S1>/Delay1' incorporates:
   *  Outport: '<S1>/u_control_out'
   */
  NumLinearModel_B.utheta = NumLinearModel_rtP.u_control_out_Y0.utheta;

  /* SystemInitialize for Delay: '<S1>/Delay2' incorporates:
   *  Outport: '<S1>/u_control_out'
   */
  NumLinearModel_B.uzp = NumLinearModel_rtP.u_control_out_Y0.uzp;

  /* SystemInitialize for Delay: '<S1>/Delay3' incorporates:
   *  Outport: '<S1>/u_control_out'
   */
  NumLinearModel_B.uyaw = NumLinearModel_rtP.u_control_out_Y0.uyaw;

  /* End of SystemInitialize for SubSystem: '<Root>/InputDelay' */
}

/* System reset for referenced model: 'NumLinearModel' */
void NumLinearModel::reset(void)
{
  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator1' */
  NumLinearModel_DW.Integrator1_DSTATE = NumLinearModel_rtP.Integrator1_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator3' */
  NumLinearModel_DW.Integrator3_DSTATE = NumLinearModel_rtP.Integrator3_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator5' */
  NumLinearModel_DW.Integrator5_DSTATE = NumLinearModel_rtP.Integrator5_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator4' */
  NumLinearModel_DW.Integrator4_DSTATE = NumLinearModel_rtP.Integrator4_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator6' */
  NumLinearModel_DW.Integrator6_DSTATE = NumLinearModel_rtP.Integrator6_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator' */
  NumLinearModel_DW.Integrator_DSTATE = NumLinearModel_rtP.Integrator_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator10' */
  NumLinearModel_DW.Integrator10_DSTATE = NumLinearModel_rtP.Integrator10_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator11' */
  NumLinearModel_DW.Integrator11_DSTATE = NumLinearModel_rtP.Integrator11_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator2' */
  NumLinearModel_DW.Integrator2_DSTATE = NumLinearModel_rtP.Integrator2_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator7' */
  NumLinearModel_DW.Integrator7_DSTATE = NumLinearModel_rtP.Integrator7_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator8' */
  NumLinearModel_DW.Integrator8_DSTATE = NumLinearModel_rtP.Integrator8_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator9' */
  NumLinearModel_DW.Integrator9_DSTATE = NumLinearModel_rtP.Integrator9_IC;
}

/* Disable for referenced model: 'NumLinearModel' */
void NumLinearModel::disable(void)
{
  /* Disable for Enabled SubSystem: '<Root>/InputDelay' */
  NumLinearModel_DW.InputDelay_MODE = false;

  /* End of Disable for SubSystem: '<Root>/InputDelay' */
}

/* Output and update for referenced model: 'NumLinearModel' */
void NumLinearModel::step(const real_T *rtu_uphi, const real_T *rtu_utheta,
  const real_T *rtu_uzp, const real_T *rtu_uyaw, real_T *rty_ground_truth_pose_x,
  real_T *rty_ground_truth_pose_y, real_T *rty_ground_truth_pose_z, real_T
  *rty_ground_truth_pose_roll, real_T *rty_ground_truth_pose_pitch, real_T
  *rty_ground_truth_pose_yaw, real_T *rty_ground_truth_velocity_dx, real_T
  *rty_ground_truth_velocity_dy, real_T *rty_ground_truth_velocity_dz, real_T
  *rty_ground_truth_velocity_droll, real_T *rty_ground_truth_velocity_dpitc,
  real_T *rty_ground_truth_velocity_dyaw, real_T
  *rty_ground_truth_acceleration_d, real_T *rty_ground_truth_acceleration_e,
  real_T *rty_ground_truth_acceleration_o, real_T rtp_Cx, real_T rtp_Cy,
  boolean_T rtp_enable_input_delay, real_T rtp_gravity, real_T rtp_mass, real_T
  rtp_phi_K, real_T rtp_phi_max, real_T rtp_phi_omega, real_T rtp_phi_zeta,
  real_T rtp_theta_K, real_T rtp_theta_max, real_T rtp_theta_omega, real_T
  rtp_theta_zeta, real_T rtp_yawp_K, real_T rtp_yawp_max, real_T rtp_yawp_tal,
  real_T rtp_zp_K, real_T rtp_zp_max, real_T rtp_zp_tal)
{
  real_T cosOut;
  real_T sinOut;
  boolean_T tmp;
  tmp = rtmIsSampleHit(getRTM(), 1);
  if (tmp) {
    /* Outputs for Enabled SubSystem: '<Root>/InputDelay' incorporates:
     *  EnablePort: '<S1>/Enable'
     */
    /* Constant: '<Root>/Constant' */
    if (rtp_enable_input_delay) {
      if (!NumLinearModel_DW.InputDelay_MODE) {
        /* InitializeConditions for Delay: '<S1>/Delay' */
        NumLinearModel_DW.Delay_DSTATE =
          NumLinearModel_rtP.Delay_InitialCondition;

        /* InitializeConditions for Delay: '<S1>/Delay1' */
        NumLinearModel_DW.Delay1_DSTATE =
          NumLinearModel_rtP.Delay1_InitialCondition;

        /* InitializeConditions for Delay: '<S1>/Delay2' */
        NumLinearModel_DW.Delay2_DSTATE =
          NumLinearModel_rtP.Delay2_InitialCondition;

        /* InitializeConditions for Delay: '<S1>/Delay3' */
        NumLinearModel_DW.Delay3_DSTATE =
          NumLinearModel_rtP.Delay3_InitialCondition;
        NumLinearModel_DW.InputDelay_MODE = true;
      }

      /* Delay: '<S1>/Delay' */
      NumLinearModel_B.uphi = NumLinearModel_DW.Delay_DSTATE;

      /* Delay: '<S1>/Delay1' */
      NumLinearModel_B.utheta = NumLinearModel_DW.Delay1_DSTATE;

      /* Delay: '<S1>/Delay2' */
      NumLinearModel_B.uzp = NumLinearModel_DW.Delay2_DSTATE;

      /* Delay: '<S1>/Delay3' */
      NumLinearModel_B.uyaw = NumLinearModel_DW.Delay3_DSTATE;

      /* Update for Delay: '<S1>/Delay' */
      NumLinearModel_DW.Delay_DSTATE = *rtu_uphi;

      /* Update for Delay: '<S1>/Delay1' */
      NumLinearModel_DW.Delay1_DSTATE = *rtu_utheta;

      /* Update for Delay: '<S1>/Delay2' */
      NumLinearModel_DW.Delay2_DSTATE = *rtu_uzp;

      /* Update for Delay: '<S1>/Delay3' */
      NumLinearModel_DW.Delay3_DSTATE = *rtu_uyaw;
    } else {
      NumLinearModel_DW.InputDelay_MODE = false;
    }

    /* End of Constant: '<Root>/Constant' */
    /* End of Outputs for SubSystem: '<Root>/InputDelay' */

    /* Product: '<S2>/Divide' incorporates:
     *  Constant: '<S3>/Constant11'
     *  Constant: '<S3>/Constant8'
     *  Constant: '<S3>/Constant9'
     */
    NumLinearModel_B.Divide = NumLinearModel_B.uyaw * rtp_yawp_K * rtp_yawp_max /
      rtp_yawp_tal;

    /* Product: '<S2>/Divide2' incorporates:
     *  Constant: '<S3>/Constant10'
     *  Constant: '<S3>/Constant12'
     *  Constant: '<S3>/Constant13'
     */
    NumLinearModel_B.Divide2 = NumLinearModel_B.uzp * rtp_zp_K * rtp_zp_max /
      rtp_zp_tal;

    /* Product: '<S2>/Product' incorporates:
     *  Constant: '<S3>/Constant'
     *  Constant: '<S3>/Constant1'
     *  Constant: '<S3>/Constant2'
     */
    NumLinearModel_B.Product = NumLinearModel_B.uphi * rtp_phi_K * rtp_phi_omega
      * rtp_phi_omega * rtp_phi_max;

    /* Product: '<S2>/Product3' incorporates:
     *  Constant: '<S3>/Constant4'
     *  Constant: '<S3>/Constant5'
     *  Constant: '<S3>/Constant6'
     */
    NumLinearModel_B.Product3 = NumLinearModel_B.utheta * rtp_theta_K *
      rtp_theta_omega * rtp_theta_omega * rtp_theta_max;
  }

  /* DiscreteIntegrator: '<S2>/Integrator1' */
  *rty_ground_truth_pose_roll = NumLinearModel_DW.Integrator1_DSTATE;

  /* Trigonometry: '<S2>/Cos2' */
  cosOut = *rty_ground_truth_pose_roll;
  sinOut = std::sin(cosOut);
  cosOut = std::cos(cosOut);

  /* Trigonometry: '<S2>/Cos2' */
  NumLinearModel_B.Cos2_o1 = sinOut;

  /* Trigonometry: '<S2>/Cos2' */
  NumLinearModel_B.Cos2_o2 = cosOut;

  /* DiscreteIntegrator: '<S2>/Integrator3' */
  *rty_ground_truth_pose_pitch = NumLinearModel_DW.Integrator3_DSTATE;

  /* Trigonometry: '<S2>/Cos3' */
  cosOut = *rty_ground_truth_pose_pitch;
  sinOut = std::sin(cosOut);
  cosOut = std::cos(cosOut);

  /* Trigonometry: '<S2>/Cos3' */
  NumLinearModel_B.Cos3_o1 = sinOut;

  /* Trigonometry: '<S2>/Cos3' */
  NumLinearModel_B.Cos3_o2 = cosOut;

  /* DiscreteIntegrator: '<S2>/Integrator5' */
  *rty_ground_truth_pose_yaw = NumLinearModel_DW.Integrator5_DSTATE;

  /* Trigonometry: '<S2>/Cos4' */
  cosOut = *rty_ground_truth_pose_yaw;
  sinOut = std::sin(cosOut);
  cosOut = std::cos(cosOut);

  /* Trigonometry: '<S2>/Cos4' */
  NumLinearModel_B.Cos4_o1 = sinOut;

  /* Trigonometry: '<S2>/Cos4' */
  NumLinearModel_B.Cos4_o2 = cosOut;

  /* DiscreteIntegrator: '<S2>/Integrator4' */
  *rty_ground_truth_velocity_dyaw = NumLinearModel_DW.Integrator4_DSTATE;

  /* Product: '<S2>/Divide1' incorporates:
   *  Constant: '<S3>/Constant11'
   */
  NumLinearModel_B.Divide1 = *rty_ground_truth_velocity_dyaw / rtp_yawp_tal;

  /* DiscreteIntegrator: '<S2>/Integrator6' */
  *rty_ground_truth_velocity_dz = NumLinearModel_DW.Integrator6_DSTATE;

  /* Product: '<S2>/Divide3' incorporates:
   *  Constant: '<S3>/Constant10'
   */
  NumLinearModel_B.Divide3 = *rty_ground_truth_velocity_dz / rtp_zp_tal;

  /* Sum: '<S2>/Sum2' */
  *rty_ground_truth_acceleration_o = NumLinearModel_B.Divide2 -
    NumLinearModel_B.Divide3;

  /* Sum: '<S2>/Sum4' incorporates:
   *  Constant: '<S2>/Constant3'
   */
  NumLinearModel_B.Sum4 = rtp_gravity + *rty_ground_truth_acceleration_o;

  /* Product: '<S2>/Product6' */
  NumLinearModel_B.Product6 = NumLinearModel_B.Cos2_o2 *
    NumLinearModel_B.Cos3_o2;

  /* Product: '<S2>/Divide4' incorporates:
   *  Constant: '<S2>/Constant2'
   */
  NumLinearModel_B.Divide4 = NumLinearModel_B.Sum4 * rtp_mass /
    NumLinearModel_B.Product6;

  /* Product: '<S2>/Divide5' incorporates:
   *  Constant: '<S2>/Constant4'
   *  Product: '<S2>/Divide6'
   */
  cosOut = NumLinearModel_B.Divide4 / rtp_mass;

  /* Product: '<S2>/Divide5' */
  NumLinearModel_B.Divide5 = cosOut;

  /* Product: '<S2>/Divide6' */
  NumLinearModel_B.Divide6 = cosOut;

  /* DiscreteIntegrator: '<S2>/Integrator' */
  *rty_ground_truth_velocity_droll = NumLinearModel_DW.Integrator_DSTATE;

  /* DiscreteIntegrator: '<S2>/Integrator10' */
  *rty_ground_truth_velocity_dy = NumLinearModel_DW.Integrator10_DSTATE;

  /* DiscreteIntegrator: '<S2>/Integrator11' */
  *rty_ground_truth_pose_y = NumLinearModel_DW.Integrator11_DSTATE;

  /* DiscreteIntegrator: '<S2>/Integrator2' */
  *rty_ground_truth_velocity_dpitc = NumLinearModel_DW.Integrator2_DSTATE;

  /* DiscreteIntegrator: '<S2>/Integrator7' */
  *rty_ground_truth_pose_z = NumLinearModel_DW.Integrator7_DSTATE;

  /* DiscreteIntegrator: '<S2>/Integrator8' */
  *rty_ground_truth_velocity_dx = NumLinearModel_DW.Integrator8_DSTATE;

  /* DiscreteIntegrator: '<S2>/Integrator9' */
  *rty_ground_truth_pose_x = NumLinearModel_DW.Integrator9_DSTATE;

  /* Product: '<S2>/Product1' incorporates:
   *  Constant: '<S2>/Constant'
   *  Constant: '<S3>/Constant1'
   *  Constant: '<S3>/Constant3'
   */
  NumLinearModel_B.Product1 = rtp_phi_zeta * rtp_phi_omega *
    NumLinearModel_rtP.Constant_Value * *rty_ground_truth_velocity_droll;

  /* Product: '<S2>/Product10' incorporates:
   *  Constant: '<S3>/Constant14'
   */
  NumLinearModel_B.Product10 = *rty_ground_truth_velocity_dx * rtp_Cx;

  /* Product: '<S2>/Product11' incorporates:
   *  Constant: '<S3>/Constant15'
   */
  NumLinearModel_B.Product11 = *rty_ground_truth_velocity_dy * rtp_Cy;

  /* Product: '<S2>/Product12' */
  NumLinearModel_B.Product12 = NumLinearModel_B.Cos4_o2 *
    NumLinearModel_B.Cos2_o1;

  /* Product: '<S2>/Product13' */
  NumLinearModel_B.Product13 = NumLinearModel_B.Cos4_o1 *
    NumLinearModel_B.Cos2_o2 * NumLinearModel_B.Cos3_o1;

  /* Sum: '<S2>/Sum7' */
  NumLinearModel_B.Sum7 = NumLinearModel_B.Product13 -
    NumLinearModel_B.Product12;

  /* Product: '<S2>/Product14' */
  NumLinearModel_B.Product14 = NumLinearModel_B.Divide6 * NumLinearModel_B.Sum7;

  /* Product: '<S2>/Product2' incorporates:
   *  Constant: '<S3>/Constant1'
   */
  NumLinearModel_B.Product2 = rtp_phi_omega * rtp_phi_omega *
    *rty_ground_truth_pose_roll;

  /* Product: '<S2>/Product4' incorporates:
   *  Constant: '<S2>/Constant1'
   *  Constant: '<S3>/Constant5'
   *  Constant: '<S3>/Constant7'
   */
  NumLinearModel_B.Product4 = rtp_theta_zeta * rtp_theta_omega *
    NumLinearModel_rtP.Constant1_Value * *rty_ground_truth_velocity_dpitc;

  /* Product: '<S2>/Product5' incorporates:
   *  Constant: '<S3>/Constant5'
   */
  NumLinearModel_B.Product5 = rtp_theta_omega * rtp_theta_omega *
    *rty_ground_truth_pose_pitch;

  /* Product: '<S2>/Product7' */
  NumLinearModel_B.Product7 = NumLinearModel_B.Cos4_o1 *
    NumLinearModel_B.Cos2_o1;

  /* Product: '<S2>/Product8' */
  NumLinearModel_B.Product8 = NumLinearModel_B.Cos4_o2 *
    NumLinearModel_B.Cos2_o2 * NumLinearModel_B.Cos3_o1;

  /* Sum: '<S2>/Sum5' */
  NumLinearModel_B.Sum5 = NumLinearModel_B.Product7 + NumLinearModel_B.Product8;

  /* Product: '<S2>/Product9' */
  NumLinearModel_B.Product9 = NumLinearModel_B.Divide5 * NumLinearModel_B.Sum5;

  /* Sum: '<S2>/Sum' */
  NumLinearModel_B.phi2p_radps2 = (NumLinearModel_B.Product -
    NumLinearModel_B.Product1) - NumLinearModel_B.Product2;

  /* Sum: '<S2>/Sum1' */
  NumLinearModel_B.theta2p_radps2 = (NumLinearModel_B.Product3 -
    NumLinearModel_B.Product4) - NumLinearModel_B.Product5;

  /* Sum: '<S2>/Sum3' */
  NumLinearModel_B.yaw2p_radps2 = NumLinearModel_B.Divide -
    NumLinearModel_B.Divide1;

  /* Sum: '<S2>/Sum6' */
  *rty_ground_truth_acceleration_d = NumLinearModel_B.Product9 -
    NumLinearModel_B.Product10;

  /* Sum: '<S2>/Sum8' */
  *rty_ground_truth_acceleration_e = NumLinearModel_B.Product14 -
    NumLinearModel_B.Product11;

  /* Update for DiscreteIntegrator: '<S2>/Integrator1' */
  NumLinearModel_DW.Integrator1_DSTATE += NumLinearModel_rtP.Integrator1_gainval
    * *rty_ground_truth_velocity_droll;

  /* Update for DiscreteIntegrator: '<S2>/Integrator3' */
  NumLinearModel_DW.Integrator3_DSTATE += NumLinearModel_rtP.Integrator3_gainval
    * *rty_ground_truth_velocity_dpitc;

  /* Update for DiscreteIntegrator: '<S2>/Integrator5' */
  NumLinearModel_DW.Integrator5_DSTATE += NumLinearModel_rtP.Integrator5_gainval
    * *rty_ground_truth_velocity_dyaw;

  /* Update for DiscreteIntegrator: '<S2>/Integrator4' */
  NumLinearModel_DW.Integrator4_DSTATE += NumLinearModel_rtP.Integrator4_gainval
    * NumLinearModel_B.yaw2p_radps2;

  /* Update for DiscreteIntegrator: '<S2>/Integrator6' */
  NumLinearModel_DW.Integrator6_DSTATE += NumLinearModel_rtP.Integrator6_gainval
    * *rty_ground_truth_acceleration_o;

  /* Update for DiscreteIntegrator: '<S2>/Integrator' */
  NumLinearModel_DW.Integrator_DSTATE += NumLinearModel_rtP.Integrator_gainval *
    NumLinearModel_B.phi2p_radps2;

  /* Update for DiscreteIntegrator: '<S2>/Integrator10' */
  NumLinearModel_DW.Integrator10_DSTATE +=
    NumLinearModel_rtP.Integrator10_gainval * *rty_ground_truth_acceleration_e;

  /* Update for DiscreteIntegrator: '<S2>/Integrator11' */
  NumLinearModel_DW.Integrator11_DSTATE +=
    NumLinearModel_rtP.Integrator11_gainval * *rty_ground_truth_velocity_dy;

  /* Update for DiscreteIntegrator: '<S2>/Integrator2' */
  NumLinearModel_DW.Integrator2_DSTATE += NumLinearModel_rtP.Integrator2_gainval
    * NumLinearModel_B.theta2p_radps2;

  /* Update for DiscreteIntegrator: '<S2>/Integrator7' */
  NumLinearModel_DW.Integrator7_DSTATE += NumLinearModel_rtP.Integrator7_gainval
    * *rty_ground_truth_velocity_dz;

  /* Update for DiscreteIntegrator: '<S2>/Integrator8' */
  NumLinearModel_DW.Integrator8_DSTATE += NumLinearModel_rtP.Integrator8_gainval
    * *rty_ground_truth_acceleration_d;

  /* Update for DiscreteIntegrator: '<S2>/Integrator9' */
  NumLinearModel_DW.Integrator9_DSTATE += NumLinearModel_rtP.Integrator9_gainval
    * *rty_ground_truth_velocity_dx;
}

/* Constructor */
NumLinearModel::NumLinearModel() :
  NumLinearModel_B(),
  NumLinearModel_DW(),
  NumLinearModel_M()
{
  /* Currently there is no constructor body generated.*/
}

/* Destructor */
/* Currently there is no destructor body generated.*/
NumLinearModel::~NumLinearModel() = default;

/* Real-Time Model get method */
RT_MODEL_NumLinearModel_T * NumLinearModel::getRTM()
{
  return (&NumLinearModel_M);
}

/* member function to initialize Real-Time model */
void NumLinearModel::initializeRTM(const rtTimingBridge *timingBridge, int_T
  mdlref_TID0, int_T mdlref_TID1)
{
  setupGlobalTimingEngine(timingBridge, mdlref_TID0, mdlref_TID1);
}

/* Private member function to set up the global timing engine */
void NumLinearModel::setupGlobalTimingEngine(const rtTimingBridge *timingBridge,
  int_T mdlref_TID0, int_T mdlref_TID1)
{
  (&NumLinearModel_M)->Timing.mdlref_GlobalTID[0] = mdlref_TID0;
  (&NumLinearModel_M)->Timing.mdlref_GlobalTID[1] = mdlref_TID1;
  (&NumLinearModel_M)->timingBridge = timingBridge;
}

/* member function to setup error status pointer */
void NumLinearModel::setErrorStatusPointer(const char_T **rt_errorStatus)
{
  rtmSetErrorStatusPointer((&NumLinearModel_M), rt_errorStatus);
}
