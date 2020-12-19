/*
 * File: untitled_types.h
 *
 * Code generated for Simulink model 'untitled'.
 *
 * Model version                  : 1.0
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Sat Dec 19 17:01:37 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_untitled_types_h_
#define RTW_HEADER_untitled_types_h_
#include "rtwtypes.h"
#include "multiword_types.h"

/* Custom Type definition for MATLABSystem: '<Root>/I2C Read' */
#include "MW_SVD.h"
#ifndef typedef_c_cell_untitled_T
#define typedef_c_cell_untitled_T

typedef struct {
  char_T f1;
  char_T f2;
  char_T f3;
  char_T f4;
  char_T f5;
  char_T f6;
  char_T f7;
  char_T f8;
  char_T f9[2];
  char_T f10[2];
  char_T f11[2];
  char_T f12[2];
} c_cell_untitled_T;

#endif                                 /*typedef_c_cell_untitled_T*/

#ifndef typedef_e_codertarget_arduinobase_int_T
#define typedef_e_codertarget_arduinobase_int_T

typedef struct {
  c_cell_untitled_T AvailablePwmPinNames;
} e_codertarget_arduinobase_int_T;

#endif                               /*typedef_e_codertarget_arduinobase_int_T*/

#ifndef typedef_codertarget_arduinobase_inter_T
#define typedef_codertarget_arduinobase_inter_T

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  e_codertarget_arduinobase_int_T *Hw;
  MW_Handle_Type MW_I2C_HANDLE;
} codertarget_arduinobase_inter_T;

#endif                               /*typedef_codertarget_arduinobase_inter_T*/

#ifndef typedef_d_cell_untitled_T
#define typedef_d_cell_untitled_T

typedef struct {
  char_T f1;
  char_T f2;
  char_T f3;
  char_T f4;
  char_T f5;
  char_T f6;
  char_T f7;
  char_T f8;
  char_T f9[2];
  char_T f10[2];
  char_T f11[2];
  char_T f12[2];
} d_cell_untitled_T;

#endif                                 /*typedef_d_cell_untitled_T*/

#ifndef typedef_e_codertarget_arduinobase_i_b_T
#define typedef_e_codertarget_arduinobase_i_b_T

typedef struct {
  d_cell_untitled_T AvailablePwmPinNames;
} e_codertarget_arduinobase_i_b_T;

#endif                               /*typedef_e_codertarget_arduinobase_i_b_T*/

#ifndef typedef_codertarget_arduinobase_int_b_T
#define typedef_codertarget_arduinobase_int_b_T

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  e_codertarget_arduinobase_i_b_T *Hw;
  MW_Handle_Type MW_I2C_HANDLE;
  real_T SampleTime;
} codertarget_arduinobase_int_b_T;

#endif                               /*typedef_codertarget_arduinobase_int_b_T*/

/* Parameters (default storage) */
typedef struct P_untitled_T_ P_untitled_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_untitled_T RT_MODEL_untitled_T;

#endif                                 /* RTW_HEADER_untitled_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
