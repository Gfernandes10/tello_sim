/*
 * File: coder_assumptions.h
 *
 * Abstract: Coder assumptions header file
 */

#ifndef CODER_ASSUMPTIONS_H
#define CODER_ASSUMPTIONS_H

/* include model specific checks */
#include "NoLinearModel_ca.h"

/* global results variable mapping for static code */
#define CA_Expected                    CA_NoLinearModel_Exp
#define CA_Actual                      CA_NoLinearModel_Act
#define CA_TestResults                 CA_NoLinearModel_Res
#define CA_PortableWordSizes_Results   CA_NoLinearModel_PWSRes

/* entry point function mapping for static code */
#define CA_Run_Tests                   NoLinearModel_caRunTests
#define CA_MODEL_SPECIFIC_CHECKS_ENABLED 0
#endif                                 /* CODER_ASSUMPTIONS_H */
