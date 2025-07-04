//
// Sponsored License - for use in support of a program or activity
// sponsored by MathWorks.  Not for government, commercial or other
// non-sponsored organizational use.
//
// File: NoLinearModel.h
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
#ifndef NoLinearModel_h_
#define NoLinearModel_h_
#include <cmath>
#include "rtwtypes.h"

// Class declaration for model NoLinearModel
class NoLinearModel final
{
  // public data and function members
 public:
  // Block signals and states (default storage) for system '<Root>'
  struct DW {
    real_T Cos2_o1;                    // '<S1>/Cos2'
    real_T Cos2_o2;                    // '<S1>/Cos2'
    real_T Cos3_o1;                    // '<S1>/Cos3'
    real_T Cos3_o2;                    // '<S1>/Cos3'
    real_T Cos4_o1;                    // '<S1>/Cos4'
    real_T Cos4_o2;                    // '<S1>/Cos4'
    real_T Gain;                       // '<S1>/Gain'
    real_T Divide;                     // '<S1>/Divide'
    real_T Divide1;                    // '<S1>/Divide1'
    real_T Divide2;                    // '<S1>/Divide2'
    real_T Divide3;                    // '<S1>/Divide3'
    real_T z2p_mps2;                   // '<S1>/Sum2'
    real_T Sum4;                       // '<S1>/Sum4'
    real_T Product6;                   // '<S1>/Product6'
    real_T Divide4;                    // '<S1>/Divide4'
    real_T Divide5;                    // '<S1>/Divide5'
    real_T Divide6;                    // '<S1>/Divide6'
    real_T Product;                    // '<S1>/Product'
    real_T Product1;                   // '<S1>/Product1'
    real_T Product10;                  // '<S1>/Product10'
    real_T Product11;                  // '<S1>/Product11'
    real_T Product12;                  // '<S1>/Product12'
    real_T Product13;                  // '<S1>/Product13'
    real_T Sum7;                       // '<S1>/Sum7'
    real_T Product14;                  // '<S1>/Product14'
    real_T Product2;                   // '<S1>/Product2'
    real_T Product3;                   // '<S1>/Product3'
    real_T Product4;                   // '<S1>/Product4'
    real_T Product5;                   // '<S1>/Product5'
    real_T Product7;                   // '<S1>/Product7'
    real_T Product8;                   // '<S1>/Product8'
    real_T Sum5;                       // '<S1>/Sum5'
    real_T Product9;                   // '<S1>/Product9'
    real_T d2roll_radps2;              // '<S1>/Sum'
    real_T d2pitch_radps2;             // '<S1>/Sum1'
    real_T d2yaw_radps2;               // '<S1>/Sum3'
    real_T d2x_mps2;                   // '<S1>/Sum6'
    real_T d2y_mps;                    // '<S1>/Sum8'
    real_T dx_DSTATE;                  // '<S1>/dx'
    real_T x_DSTATE;                   // '<S1>/x'
    real_T pitch_DSTATE;               // '<S1>/pitch'
    real_T dpitch_DSTATE;              // '<S1>/dpitch'
    real_T dy_DSTATE;                  // '<S1>/dy'
    real_T y_DSTATE;                   // '<S1>/y'
    real_T roll_DSTATE;                // '<S1>/roll'
    real_T droll_DSTATE;               // '<S1>/droll'
    real_T yaw_DSTATE;                 // '<S1>/yaw'
    real_T dyaw_DSTATE;                // '<S1>/dyaw'
    real_T dz_DSTATE;                  // '<S1>/dz'
    real_T z_DSTATE;                   // '<S1>/z'
  };

  // instance parameters, for system '<Root>'
  struct InstP {
    real_T Cx;                         // Variable: Cx
                                          //  Referenced by: '<S2>/Constant14'

    real_T Cy;                         // Variable: Cy
                                          //  Referenced by: '<S2>/Constant15'

    real_T pitch_K;                    // Variable: pitch_K
                                          //  Referenced by: '<S2>/Constant4'

    real_T pitch_max;                  // Variable: pitch_max
                                          //  Referenced by: '<S2>/Constant6'

    real_T pitch_omega;                // Variable: pitch_omega
                                          //  Referenced by: '<S2>/Constant5'

    real_T pitch_zeta;                 // Variable: pitch_zeta
                                          //  Referenced by: '<S2>/Constant7'

    real_T roll_K;                     // Variable: roll_K
                                          //  Referenced by: '<S2>/Constant'

    real_T roll_max;                   // Variable: roll_max
                                          //  Referenced by: '<S2>/Constant2'

    real_T roll_omega;                 // Variable: roll_omega
                                          //  Referenced by: '<S2>/Constant1'

    real_T roll_zeta;                  // Variable: roll_zeta
                                          //  Referenced by: '<S2>/Constant3'

    real_T yawp_K;                     // Variable: yawp_K
                                          //  Referenced by: '<S2>/Constant8'

    real_T yawp_max;                   // Variable: yawp_max
                                          //  Referenced by: '<S2>/Constant9'

    real_T yawp_tal;                   // Variable: yawp_tal
                                          //  Referenced by: '<S2>/Constant11'

    real_T zp_K;                       // Variable: zp_K
                                          //  Referenced by: '<S2>/Constant12'

    real_T zp_max;                     // Variable: zp_max
                                          //  Referenced by: '<S2>/Constant13'

    real_T zp_tal;                     // Variable: zp_tal
                                          //  Referenced by: '<S2>/Constant10'

  };

  // External inputs (root inport signals with default storage)
  struct ExtU {
    real_T upitch;                     // '<Root>/upitch'
    real_T uroll;                      // '<Root>/uroll'
    real_T uzp;                        // '<Root>/uzp'
    real_T uyaw;                       // '<Root>/uyaw'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY {
    real_T dx_mps;                     // '<Root>/dx_mps'
    real_T x_m;                        // '<Root>/x_m'
    real_T pitch_rad;                  // '<Root>/pitch_rad'
    real_T dpitch_radps;               // '<Root>/dpitch_radps'
    real_T dy_mps;                     // '<Root>/dy_mps'
    real_T y_m;                        // '<Root>/y_m'
    real_T roll_rad;                   // '<Root>/roll_rad'
    real_T roll_radps;                 // '<Root>/roll_radps'
    real_T yaw_rad;                    // '<Root>/yaw_rad'
    real_T dyaw_radps;                 // '<Root>/dyaw_radps'
    real_T dz_mps;                     // '<Root>/dz_mps'
    real_T z_m;                        // '<Root>/z_m'
  };

  // Copy Constructor
  NoLinearModel(NoLinearModel const&) = delete;

  // Assignment Operator
  NoLinearModel& operator= (NoLinearModel const&) & = delete;

  // Move Constructor
  NoLinearModel(NoLinearModel &&) = delete;

  // Move Assignment Operator
  NoLinearModel& operator= (NoLinearModel &&) = delete;

  // External inputs
  ExtU rtU;

  // External outputs
  ExtY rtY;

  // Root inport: '<Root>/upitch' set method
  void setupitch(real_T localArgInput)
  {
    rtU.upitch = localArgInput;
  }

  // Root inport: '<Root>/uroll' set method
  void seturoll(real_T localArgInput)
  {
    rtU.uroll = localArgInput;
  }

  // Root inport: '<Root>/uzp' set method
  void setuzp(real_T localArgInput)
  {
    rtU.uzp = localArgInput;
  }

  // Root inport: '<Root>/uyaw' set method
  void setuyaw(real_T localArgInput)
  {
    rtU.uyaw = localArgInput;
  }

  // Root outports get method
  const ExtY &getExternalOutputs() const;

  // get method for instance parameters
  const InstP &get_InstP() const
  {
    return rtInstP;
  }

  // set method for instance parameters
  void set_InstP(const InstP &NoLinearModel_InstP_arg)
  {
    rtInstP = NoLinearModel_InstP_arg;
  }

  // model initialize function
  static void initialize();

  // model step function
  void step();

  // Constructor
  NoLinearModel();

  // Destructor
  ~NoLinearModel();

  // private data and function members
 private:
  // Block states
  DW rtDW;

  // instance parameters
  InstP rtInstP{
    // Variable: Cx
    //  Referenced by: '<S2>/Constant14'

    1.0,

    // Variable: Cy
    //  Referenced by: '<S2>/Constant15'

    1.0,

    // Variable: pitch_K
    //  Referenced by: '<S2>/Constant4'

    1.0,

    // Variable: pitch_max
    //  Referenced by: '<S2>/Constant6'

    1.0,

    // Variable: pitch_omega
    //  Referenced by: '<S2>/Constant5'

    1.0,

    // Variable: pitch_zeta
    //  Referenced by: '<S2>/Constant7'

    1.0,

    // Variable: roll_K
    //  Referenced by: '<S2>/Constant'

    1.0,

    // Variable: roll_max
    //  Referenced by: '<S2>/Constant2'

    1.0,

    // Variable: roll_omega
    //  Referenced by: '<S2>/Constant1'

    1.0,

    // Variable: roll_zeta
    //  Referenced by: '<S2>/Constant3'

    1.0,

    // Variable: yawp_K
    //  Referenced by: '<S2>/Constant8'

    1.0,

    // Variable: yawp_max
    //  Referenced by: '<S2>/Constant9'

    1.0,

    // Variable: yawp_tal
    //  Referenced by: '<S2>/Constant11'

    1.0,

    // Variable: zp_K
    //  Referenced by: '<S2>/Constant12'

    1.0,

    // Variable: zp_max
    //  Referenced by: '<S2>/Constant13'

    1.0,

    // Variable: zp_tal
    //  Referenced by: '<S2>/Constant10'

    1.0
  };
};

//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'NoLinearModel'
//  '<S1>'   : 'NoLinearModel/NonLinearDynamic'
//  '<S2>'   : 'NoLinearModel/Parameters'

#endif                                 // NoLinearModel_h_

//
// File trailer for generated code.
//
// [EOF]
//
