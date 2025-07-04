/*
 * Code generation for system model 'NumLinearModel'
 * For more details, see corresponding source file NumLinearModel.c
 *
 */

#ifndef NumLinearModel_h_
#define NumLinearModel_h_
#include <cmath>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_nonfinite.h"
#include "NumLinearModel_types.h"
#include "model_reference_types.h"
#include <cstring>

/* Block signals for model 'NumLinearModel' */
struct B_NumLinearModel_T {
  real_T Cos2_o1;                      /* '<S2>/Cos2' */
  real_T Cos2_o2;                      /* '<S2>/Cos2' */
  real_T Cos3_o1;                      /* '<S2>/Cos3' */
  real_T Cos3_o2;                      /* '<S2>/Cos3' */
  real_T Cos4_o1;                      /* '<S2>/Cos4' */
  real_T Cos4_o2;                      /* '<S2>/Cos4' */
  real_T Divide;                       /* '<S2>/Divide' */
  real_T Divide1;                      /* '<S2>/Divide1' */
  real_T Divide2;                      /* '<S2>/Divide2' */
  real_T Divide3;                      /* '<S2>/Divide3' */
  real_T Sum4;                         /* '<S2>/Sum4' */
  real_T Product6;                     /* '<S2>/Product6' */
  real_T Divide4;                      /* '<S2>/Divide4' */
  real_T Divide5;                      /* '<S2>/Divide5' */
  real_T Divide6;                      /* '<S2>/Divide6' */
  real_T Product;                      /* '<S2>/Product' */
  real_T Product1;                     /* '<S2>/Product1' */
  real_T Product10;                    /* '<S2>/Product10' */
  real_T Product11;                    /* '<S2>/Product11' */
  real_T Product12;                    /* '<S2>/Product12' */
  real_T Product13;                    /* '<S2>/Product13' */
  real_T Sum7;                         /* '<S2>/Sum7' */
  real_T Product14;                    /* '<S2>/Product14' */
  real_T Product2;                     /* '<S2>/Product2' */
  real_T Product3;                     /* '<S2>/Product3' */
  real_T Product4;                     /* '<S2>/Product4' */
  real_T Product5;                     /* '<S2>/Product5' */
  real_T Product7;                     /* '<S2>/Product7' */
  real_T Product8;                     /* '<S2>/Product8' */
  real_T Sum5;                         /* '<S2>/Sum5' */
  real_T Product9;                     /* '<S2>/Product9' */
  real_T phi2p_radps2;                 /* '<S2>/Sum' */
  real_T theta2p_radps2;               /* '<S2>/Sum1' */
  real_T yaw2p_radps2;                 /* '<S2>/Sum3' */
  real_T uphi;                         /* '<S1>/Delay' */
  real_T utheta;                       /* '<S1>/Delay1' */
  real_T uzp;                          /* '<S1>/Delay2' */
  real_T uyaw;                         /* '<S1>/Delay3' */
};

/* Block states (default storage) for model 'NumLinearModel' */
struct DW_NumLinearModel_T {
  real_T Integrator1_DSTATE;           /* '<S2>/Integrator1' */
  real_T Integrator3_DSTATE;           /* '<S2>/Integrator3' */
  real_T Integrator5_DSTATE;           /* '<S2>/Integrator5' */
  real_T Integrator4_DSTATE;           /* '<S2>/Integrator4' */
  real_T Integrator6_DSTATE;           /* '<S2>/Integrator6' */
  real_T Integrator_DSTATE;            /* '<S2>/Integrator' */
  real_T Integrator10_DSTATE;          /* '<S2>/Integrator10' */
  real_T Integrator11_DSTATE;          /* '<S2>/Integrator11' */
  real_T Integrator2_DSTATE;           /* '<S2>/Integrator2' */
  real_T Integrator7_DSTATE;           /* '<S2>/Integrator7' */
  real_T Integrator8_DSTATE;           /* '<S2>/Integrator8' */
  real_T Integrator9_DSTATE;           /* '<S2>/Integrator9' */
  real_T Delay_DSTATE;                 /* '<S1>/Delay' */
  real_T Delay1_DSTATE;                /* '<S1>/Delay1' */
  real_T Delay2_DSTATE;                /* '<S1>/Delay2' */
  real_T Delay3_DSTATE;                /* '<S1>/Delay3' */
  boolean_T InputDelay_MODE;           /* '<Root>/InputDelay' */
};

/* Parameters (default storage) */
struct P_NumLinearModel_T_ {
  struct_ntCcZA6dmYQlhHRgczZZUG u_control_out_Y0;/* Computed Parameter: u_control_out_Y0
                                                  * Referenced by: '<S1>/u_control_out'
                                                  */
  real_T Delay_InitialCondition;       /* Expression: 0.0
                                        * Referenced by: '<S1>/Delay'
                                        */
  real_T Delay1_InitialCondition;      /* Expression: 0.0
                                        * Referenced by: '<S1>/Delay1'
                                        */
  real_T Delay2_InitialCondition;      /* Expression: 0.0
                                        * Referenced by: '<S1>/Delay2'
                                        */
  real_T Delay3_InitialCondition;      /* Expression: 0.0
                                        * Referenced by: '<S1>/Delay3'
                                        */
  real_T Constant_Value;               /* Expression: 2
                                        * Referenced by: '<S2>/Constant'
                                        */
  real_T Constant1_Value;              /* Expression: 2
                                        * Referenced by: '<S2>/Constant1'
                                        */
  real_T Integrator1_gainval;         /* Computed Parameter: Integrator1_gainval
                                       * Referenced by: '<S2>/Integrator1'
                                       */
  real_T Integrator1_IC;               /* Expression: 0
                                        * Referenced by: '<S2>/Integrator1'
                                        */
  real_T Integrator3_gainval;         /* Computed Parameter: Integrator3_gainval
                                       * Referenced by: '<S2>/Integrator3'
                                       */
  real_T Integrator3_IC;               /* Expression: 0
                                        * Referenced by: '<S2>/Integrator3'
                                        */
  real_T Integrator5_gainval;         /* Computed Parameter: Integrator5_gainval
                                       * Referenced by: '<S2>/Integrator5'
                                       */
  real_T Integrator5_IC;               /* Expression: 0
                                        * Referenced by: '<S2>/Integrator5'
                                        */
  real_T Integrator4_gainval;         /* Computed Parameter: Integrator4_gainval
                                       * Referenced by: '<S2>/Integrator4'
                                       */
  real_T Integrator4_IC;               /* Expression: 0
                                        * Referenced by: '<S2>/Integrator4'
                                        */
  real_T Integrator6_gainval;         /* Computed Parameter: Integrator6_gainval
                                       * Referenced by: '<S2>/Integrator6'
                                       */
  real_T Integrator6_IC;               /* Expression: 0
                                        * Referenced by: '<S2>/Integrator6'
                                        */
  real_T Integrator_gainval;           /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S2>/Integrator'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * Referenced by: '<S2>/Integrator'
                                        */
  real_T Integrator10_gainval;       /* Computed Parameter: Integrator10_gainval
                                      * Referenced by: '<S2>/Integrator10'
                                      */
  real_T Integrator10_IC;              /* Expression: 0
                                        * Referenced by: '<S2>/Integrator10'
                                        */
  real_T Integrator11_gainval;       /* Computed Parameter: Integrator11_gainval
                                      * Referenced by: '<S2>/Integrator11'
                                      */
  real_T Integrator11_IC;              /* Expression: 0
                                        * Referenced by: '<S2>/Integrator11'
                                        */
  real_T Integrator2_gainval;         /* Computed Parameter: Integrator2_gainval
                                       * Referenced by: '<S2>/Integrator2'
                                       */
  real_T Integrator2_IC;               /* Expression: 0
                                        * Referenced by: '<S2>/Integrator2'
                                        */
  real_T Integrator7_gainval;         /* Computed Parameter: Integrator7_gainval
                                       * Referenced by: '<S2>/Integrator7'
                                       */
  real_T Integrator7_IC;               /* Expression: 0
                                        * Referenced by: '<S2>/Integrator7'
                                        */
  real_T Integrator8_gainval;         /* Computed Parameter: Integrator8_gainval
                                       * Referenced by: '<S2>/Integrator8'
                                       */
  real_T Integrator8_IC;               /* Expression: 0
                                        * Referenced by: '<S2>/Integrator8'
                                        */
  real_T Integrator9_gainval;         /* Computed Parameter: Integrator9_gainval
                                       * Referenced by: '<S2>/Integrator9'
                                       */
  real_T Integrator9_IC;               /* Expression: 0
                                        * Referenced by: '<S2>/Integrator9'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_NumLinearModel_T {
  const char_T **errorStatus;
  const rtTimingBridge *timingBridge;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    int_T mdlref_GlobalTID[2];
  } Timing;
};

extern P_NumLinearModel_T NumLinearModel_rtP;

/* Class declaration for model NumLinearModel */
class NumLinearModel final
{
  /* public data and function members */
 public:
  /* Initial conditions function */
  void init();

  /* Copy Constructor */
  NumLinearModel(NumLinearModel const&) = delete;

  /* Assignment Operator */
  NumLinearModel& operator= (NumLinearModel const&) & = delete;

  /* Move Constructor */
  NumLinearModel(NumLinearModel &&) = delete;

  /* Move Assignment Operator */
  NumLinearModel& operator= (NumLinearModel &&) = delete;

  /* Real-Time Model get method */
  RT_MODEL_NumLinearModel_T * getRTM();

  /* member function to initialize Real-Time model */
  void initializeRTM(const rtTimingBridge *timingBridge, int_T mdlref_TID0,
                     int_T mdlref_TID1);

  /*member function to setup error status pointer */
  void setErrorStatusPointer(const char_T **rt_errorStatus);

  /* model step function */
  void step(const real_T *rtu_uphi, const real_T *rtu_utheta, const real_T
            *rtu_uzp, const real_T *rtu_uyaw, real_T *rty_ground_truth_pose_x,
            real_T *rty_ground_truth_pose_y, real_T *rty_ground_truth_pose_z,
            real_T *rty_ground_truth_pose_roll, real_T
            *rty_ground_truth_pose_pitch, real_T *rty_ground_truth_pose_yaw,
            real_T *rty_ground_truth_velocity_dx, real_T
            *rty_ground_truth_velocity_dy, real_T *rty_ground_truth_velocity_dz,
            real_T *rty_ground_truth_velocity_droll, real_T
            *rty_ground_truth_velocity_dpitc, real_T
            *rty_ground_truth_velocity_dyaw, real_T
            *rty_ground_truth_acceleration_d, real_T
            *rty_ground_truth_acceleration_e, real_T
            *rty_ground_truth_acceleration_o, real_T rtp_Cx, real_T rtp_Cy,
            boolean_T rtp_enable_input_delay, real_T rtp_gravity, real_T
            rtp_mass, real_T rtp_phi_K, real_T rtp_phi_max, real_T rtp_phi_omega,
            real_T rtp_phi_zeta, real_T rtp_theta_K, real_T rtp_theta_max,
            real_T rtp_theta_omega, real_T rtp_theta_zeta, real_T rtp_yawp_K,
            real_T rtp_yawp_max, real_T rtp_yawp_tal, real_T rtp_zp_K, real_T
            rtp_zp_max, real_T rtp_zp_tal);

  /* Reset function */
  void reset();

  /* model disable function */
  void disable();

  /* Constructor */
  NumLinearModel();

  /* Destructor */
  ~NumLinearModel();

  /* private data and function members */
 private:
  /* Block signals */
  B_NumLinearModel_T NumLinearModel_B;

  /* Block states */
  DW_NumLinearModel_T NumLinearModel_DW;

  /* Tunable parameters */
  static P_NumLinearModel_T NumLinearModel_rtP;

  /* Private member function to set up the global timing engine */
  void setupGlobalTimingEngine(const rtTimingBridge *timingBridge, int_T
    mdlref_TID0, int_T mdlref_TID1);

  /* Real-Time Model */
  RT_MODEL_NumLinearModel_T NumLinearModel_M;
};

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'NumLinearModel'
 * '<S1>'   : 'NumLinearModel/InputDelay'
 * '<S2>'   : 'NumLinearModel/NonLinearDynamics'
 * '<S3>'   : 'NumLinearModel/Parameters'
 */
#endif                                 /* NumLinearModel_h_ */
