/*
 * untitled_dt.h
 *
 * Code generation for model "untitled".
 *
 * Model version              : 1.0
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C source code generated on : Sat Dec 19 17:01:37 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(pointer_T),
  sizeof(action_T),
  2*sizeof(uint32_T),
  sizeof(int16_T),
  sizeof(int32_T),
  sizeof(int32_T),
  sizeof(codertarget_arduinobase_int_b_T),
  sizeof(e_codertarget_arduinobase_i_b_T),
  sizeof(codertarget_arduinobase_inter_T),
  sizeof(e_codertarget_arduinobase_int_T)
};

/* data type name table */
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T",
  "int16_T",
  "int32_T",
  "int32_T",
  "codertarget_arduinobase_int_b_T",
  "e_codertarget_arduinobase_i_b_T",
  "codertarget_arduinobase_inter_T",
  "e_codertarget_arduinobase_int_T"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&untitled_B.Gain1), 1, 0, 1 },

  { (char_T *)(&untitled_B.Sum[0]), 15, 0, 3 }
  ,

  { (char_T *)(&untitled_DW.obj), 17, 0, 1 },

  { (char_T *)(&untitled_DW.obj_p), 19, 0, 1 },

  { (char_T *)(&untitled_DW.gobj_0), 18, 0, 4 },

  { (char_T *)(&untitled_DW.gobj_0_b), 20, 0, 4 },

  { (char_T *)(&untitled_DW.UD_DSTATE[0]), 15, 0, 3 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  7U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&untitled_P.TransferFcnFirstOrder_ICPrevOut), 15, 0, 2 },

  { (char_T *)(&untitled_P.I2CRead_SampleTime), 0, 0, 2 },

  { (char_T *)(&untitled_P.Gain1_Gain), 1, 0, 1 },

  { (char_T *)(&untitled_P.Gain_Gain), 14, 0, 1 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  4U,
  rtPTransitions
};

/* [EOF] untitled_dt.h */
