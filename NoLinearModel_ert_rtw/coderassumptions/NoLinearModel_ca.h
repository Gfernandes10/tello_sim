/*
 * File: NoLinearModel_ca.h
 *
 * Abstract: Tests assumptions in the generated code.
 */

#ifndef NOLINEARMODEL_CA_H
#define NOLINEARMODEL_CA_H

/* preprocessor validation checks */
#include "NoLinearModel_ca_preproc.h"
#include "coder_assumptions_hwimpl.h"

/* variables holding test results */
extern CA_ChecksTestResults CA_NoLinearModel_Res;
extern CA_PWS_TestResults CA_NoLinearModel_PWSRes;

/* variables holding "expected" and "actual" hardware implementation */
extern const CA_Checks CA_NoLinearModel_Exp;
extern CA_Checks CA_NoLinearModel_Act;
extern const int numberOfImportedTypes;

/* entry point function to run tests */
void NoLinearModel_caRunTests(void);

#endif                                 /* NOLINEARMODEL_CA_H */
