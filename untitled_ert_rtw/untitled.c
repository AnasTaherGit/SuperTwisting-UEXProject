/*
 * File: untitled.c
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

#include "untitled.h"
#include "untitled_private.h"
#include "untitled_dt.h"

/* Block signals (default storage) */
B_untitled_T untitled_B;

/* Block states (default storage) */
DW_untitled_T untitled_DW;

/* Real-time model */
RT_MODEL_untitled_T untitled_M_;
RT_MODEL_untitled_T *const untitled_M = &untitled_M_;

/* Forward declaration for local functions */
static void untitled_SystemCore_release_b(const codertarget_arduinobase_int_b_T *
  obj);
static void untitled_SystemCore_delete_b(const codertarget_arduinobase_int_b_T
  *obj);
static void matlabCodegenHandle_matlabCod_b(codertarget_arduinobase_int_b_T *obj);
static void untitled_SystemCore_release(const codertarget_arduinobase_inter_T
  *obj);
static void untitled_SystemCore_delete(const codertarget_arduinobase_inter_T
  *obj);
static void matlabCodegenHandle_matlabCodeg(codertarget_arduinobase_inter_T *obj);
static void SystemProp_matlabCodegenSetAn_b(codertarget_arduinobase_int_b_T *obj,
  e_codertarget_arduinobase_i_b_T *iobj_0);
static void SystemProp_matlabCodegenSetAnyP(codertarget_arduinobase_inter_T *obj,
  e_codertarget_arduinobase_int_T *iobj_0);
void mul_wide_s32(int32_T in0, int32_T in1, uint32_T *ptrOutBitsHi, uint32_T
                  *ptrOutBitsLo)
{
  uint32_T absIn0;
  uint32_T absIn1;
  uint32_T in0Lo;
  uint32_T in0Hi;
  uint32_T in1Hi;
  uint32_T productHiLo;
  uint32_T productLoHi;
  absIn0 = in0 < 0L ? ~(uint32_T)in0 + 1UL : (uint32_T)in0;
  absIn1 = in1 < 0L ? ~(uint32_T)in1 + 1UL : (uint32_T)in1;
  in0Hi = absIn0 >> 16UL;
  in0Lo = absIn0 & 65535UL;
  in1Hi = absIn1 >> 16UL;
  absIn0 = absIn1 & 65535UL;
  productHiLo = in0Hi * absIn0;
  productLoHi = in0Lo * in1Hi;
  absIn0 *= in0Lo;
  absIn1 = 0UL;
  in0Lo = (productLoHi << /*MW:OvBitwiseOk*/ 16UL) + /*MW:OvCarryOk*/ absIn0;
  if (in0Lo < absIn0) {
    absIn1 = 1UL;
  }

  absIn0 = in0Lo;
  in0Lo += /*MW:OvCarryOk*/ productHiLo << /*MW:OvBitwiseOk*/ 16UL;
  if (in0Lo < absIn0) {
    absIn1++;
  }

  absIn0 = (((productLoHi >> 16UL) + (productHiLo >> 16UL)) + in0Hi * in1Hi) +
    absIn1;
  if ((in0 != 0L) && ((in1 != 0L) && ((in0 > 0L) != (in1 > 0L)))) {
    absIn0 = ~absIn0;
    in0Lo = ~in0Lo;
    in0Lo++;
    if (in0Lo == 0UL) {
      absIn0++;
    }
  }

  *ptrOutBitsHi = absIn0;
  *ptrOutBitsLo = in0Lo;
}

int32_T mul_s32_loSR_near(int32_T a, int32_T b, uint32_T aShift)
{
  uint32_T u32_chi;
  uint32_T u32_clo;
  mul_wide_s32(a, b, &u32_chi, &u32_clo);
  u32_clo = ((1UL << (aShift - 1UL) & u32_clo) != 0UL) + (u32_chi <<
    /*MW:OvBitwiseOk*/ (32UL - aShift) | u32_clo >> aShift);
  return (int32_T)u32_clo;
}

static void untitled_SystemCore_release_b(const codertarget_arduinobase_int_b_T *
  obj)
{
  if ((obj->isInitialized == 1L) && obj->isSetupComplete) {
    MW_I2C_Close(obj->MW_I2C_HANDLE);
  }
}

static void untitled_SystemCore_delete_b(const codertarget_arduinobase_int_b_T
  *obj)
{
  untitled_SystemCore_release_b(obj);
}

static void matlabCodegenHandle_matlabCod_b(codertarget_arduinobase_int_b_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    untitled_SystemCore_delete_b(obj);
  }
}

static void untitled_SystemCore_release(const codertarget_arduinobase_inter_T
  *obj)
{
  if ((obj->isInitialized == 1L) && obj->isSetupComplete) {
    MW_I2C_Close(obj->MW_I2C_HANDLE);
  }
}

static void untitled_SystemCore_delete(const codertarget_arduinobase_inter_T
  *obj)
{
  untitled_SystemCore_release(obj);
}

static void matlabCodegenHandle_matlabCodeg(codertarget_arduinobase_inter_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    untitled_SystemCore_delete(obj);
  }
}

static void SystemProp_matlabCodegenSetAn_b(codertarget_arduinobase_int_b_T *obj,
  e_codertarget_arduinobase_i_b_T *iobj_0)
{
  iobj_0->AvailablePwmPinNames.f1 = '2';
  iobj_0->AvailablePwmPinNames.f2 = '3';
  iobj_0->AvailablePwmPinNames.f3 = '4';
  iobj_0->AvailablePwmPinNames.f4 = '5';
  iobj_0->AvailablePwmPinNames.f5 = '6';
  iobj_0->AvailablePwmPinNames.f6 = '7';
  iobj_0->AvailablePwmPinNames.f7 = '8';
  iobj_0->AvailablePwmPinNames.f8 = '9';
  iobj_0->AvailablePwmPinNames.f9[0] = '1';
  iobj_0->AvailablePwmPinNames.f9[1] = '0';
  iobj_0->AvailablePwmPinNames.f10[0] = '1';
  iobj_0->AvailablePwmPinNames.f10[1] = '1';
  iobj_0->AvailablePwmPinNames.f11[0] = '1';
  iobj_0->AvailablePwmPinNames.f11[1] = '2';
  iobj_0->AvailablePwmPinNames.f12[0] = '1';
  iobj_0->AvailablePwmPinNames.f12[1] = '3';
  obj->Hw = iobj_0;
}

static void SystemProp_matlabCodegenSetAnyP(codertarget_arduinobase_inter_T *obj,
  e_codertarget_arduinobase_int_T *iobj_0)
{
  iobj_0->AvailablePwmPinNames.f1 = '2';
  iobj_0->AvailablePwmPinNames.f2 = '3';
  iobj_0->AvailablePwmPinNames.f3 = '4';
  iobj_0->AvailablePwmPinNames.f4 = '5';
  iobj_0->AvailablePwmPinNames.f5 = '6';
  iobj_0->AvailablePwmPinNames.f6 = '7';
  iobj_0->AvailablePwmPinNames.f7 = '8';
  iobj_0->AvailablePwmPinNames.f8 = '9';
  iobj_0->AvailablePwmPinNames.f9[0] = '1';
  iobj_0->AvailablePwmPinNames.f9[1] = '0';
  iobj_0->AvailablePwmPinNames.f10[0] = '1';
  iobj_0->AvailablePwmPinNames.f10[1] = '1';
  iobj_0->AvailablePwmPinNames.f11[0] = '1';
  iobj_0->AvailablePwmPinNames.f11[1] = '2';
  iobj_0->AvailablePwmPinNames.f12[0] = '1';
  iobj_0->AvailablePwmPinNames.f12[1] = '3';
  obj->Hw = iobj_0;
}

/* Model step function */
void untitled_step(void)
{
  int16_T b_output[3];
  uint8_T status;
  uint8_T output_raw[6];
  uint8_T y[2];
  uint8_T b_x[2];
  uint8_T SwappedDataBytes[8];
  uint8_T b_SwappedDataBytes[9];
  real_T b_x_0;
  int16_T b_output_0;

  /* MATLABSystem: '<Root>/I2C Read' */
  if (untitled_DW.obj.SampleTime != untitled_P.I2CRead_SampleTime) {
    untitled_DW.obj.SampleTime = untitled_P.I2CRead_SampleTime;
  }

  status = 59U;
  status = MW_I2C_MasterWrite(untitled_DW.obj.MW_I2C_HANDLE, 104UL, &status, 1UL,
    true, false);
  if (0 == status) {
    MW_I2C_MasterRead(untitled_DW.obj.MW_I2C_HANDLE, 104UL, output_raw, 6UL,
                      false, true);
    memcpy((void *)&b_output[0], (void *)&output_raw[0], (uint16_T)((size_t)3 *
            sizeof(int16_T)));
    b_output_0 = b_output[0];
    memcpy((void *)&y[0], (void *)&b_output_0, (uint16_T)((size_t)2 * sizeof
            (uint8_T)));
    b_x[0] = y[1];
    b_x[1] = y[0];
    memcpy((void *)&b_output[0], (void *)&b_x[0], (uint16_T)((size_t)1 * sizeof
            (int16_T)));
    b_output_0 = b_output[1];
    memcpy((void *)&y[0], (void *)&b_output_0, (uint16_T)((size_t)2 * sizeof
            (uint8_T)));
    b_x[0] = y[1];
    b_x[1] = y[0];
    memcpy((void *)&b_output[1], (void *)&b_x[0], (uint16_T)((size_t)1 * sizeof
            (int16_T)));
    b_output_0 = b_output[2];
    memcpy((void *)&y[0], (void *)&b_output_0, (uint16_T)((size_t)2 * sizeof
            (uint8_T)));
    b_x[0] = y[1];
    b_x[1] = y[0];
    memcpy((void *)&b_output[2], (void *)&b_x[0], (uint16_T)((size_t)1 * sizeof
            (int16_T)));
  } else {
    b_output[0] = 0;
    b_output[1] = 0;
    b_output[2] = 0;
  }

  /* Gain: '<Root>/Gain' incorporates:
   *  MATLABSystem: '<Root>/I2C Read'
   */
  untitled_B.Sum[0] = (int32_T)untitled_P.Gain_Gain * b_output[0];

  /* Sum: '<S1>/Sum' incorporates:
   *  Gain: '<S1>/Gain'
   *  Sum: '<S1>/Diff'
   *  UnitDelay: '<S1>/UD'
   *
   * Block description for '<S1>/Sum':
   *
   *  Add in CPU
   *
   * Block description for '<S1>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S1>/UD':
   *
   *  Store in Global RAM
   */
  untitled_B.Sum[0] += mul_s32_loSR_near(untitled_P.TransferFcnFirstOrder_PoleZ,
    untitled_DW.UD_DSTATE[0] - untitled_B.Sum[0], 31UL);

  /* Gain: '<Root>/Gain' incorporates:
   *  MATLABSystem: '<Root>/I2C Read'
   */
  untitled_B.Sum[1] = (int32_T)untitled_P.Gain_Gain * b_output[1];

  /* Sum: '<S1>/Sum' incorporates:
   *  Gain: '<S1>/Gain'
   *  Sum: '<S1>/Diff'
   *  UnitDelay: '<S1>/UD'
   *
   * Block description for '<S1>/Sum':
   *
   *  Add in CPU
   *
   * Block description for '<S1>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S1>/UD':
   *
   *  Store in Global RAM
   */
  untitled_B.Sum[1] += mul_s32_loSR_near(untitled_P.TransferFcnFirstOrder_PoleZ,
    untitled_DW.UD_DSTATE[1] - untitled_B.Sum[1], 31UL);

  /* Gain: '<Root>/Gain' incorporates:
   *  MATLABSystem: '<Root>/I2C Read'
   */
  untitled_B.Sum[2] = (int32_T)untitled_P.Gain_Gain * b_output[2];

  /* Sum: '<S1>/Sum' incorporates:
   *  Gain: '<S1>/Gain'
   *  Sum: '<S1>/Diff'
   *  UnitDelay: '<S1>/UD'
   *
   * Block description for '<S1>/Sum':
   *
   *  Add in CPU
   *
   * Block description for '<S1>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S1>/UD':
   *
   *  Store in Global RAM
   */
  untitled_B.Sum[2] += mul_s32_loSR_near(untitled_P.TransferFcnFirstOrder_PoleZ,
    untitled_DW.UD_DSTATE[2] - untitled_B.Sum[2], 31UL);

  /* Gain: '<Root>/Gain1' incorporates:
   *  Fcn: '<Root>/Fcn'
   *  Product: '<Root>/Divide'
   */
  untitled_B.Gain1 = (real32_T)atan((real32_T)untitled_B.Sum[0] * 3.7252903E-9F /
    ((real32_T)untitled_B.Sum[2] * 3.7252903E-9F)) * untitled_P.Gain1_Gain;

  /* MATLABSystem: '<Root>/I2C Write' incorporates:
   *  Constant: '<Root>/Constant'
   */
  memcpy((void *)&SwappedDataBytes[0], (void *)&untitled_P.Constant_Value,
         (uint16_T)((size_t)8 * sizeof(uint8_T)));
  status = SwappedDataBytes[0];
  SwappedDataBytes[0] = SwappedDataBytes[7];
  SwappedDataBytes[7] = status;
  status = SwappedDataBytes[1];
  SwappedDataBytes[1] = SwappedDataBytes[6];
  SwappedDataBytes[6] = status;
  status = SwappedDataBytes[2];
  SwappedDataBytes[2] = SwappedDataBytes[5];
  SwappedDataBytes[5] = status;
  status = SwappedDataBytes[3];
  SwappedDataBytes[3] = SwappedDataBytes[4];
  SwappedDataBytes[4] = status;
  memcpy((void *)&b_x_0, (void *)&SwappedDataBytes[0], (uint16_T)((size_t)1 *
          sizeof(real_T)));
  memcpy((void *)&SwappedDataBytes[0], (void *)&b_x_0, (uint16_T)((size_t)8 *
          sizeof(uint8_T)));
  b_SwappedDataBytes[0] = 107U;
  for (b_output_0 = 0; b_output_0 < 8; b_output_0++) {
    b_SwappedDataBytes[b_output_0 + 1] = SwappedDataBytes[b_output_0];
  }

  MW_I2C_MasterWrite(untitled_DW.obj_p.MW_I2C_HANDLE, 104UL, b_SwappedDataBytes,
                     9UL, false, false);

  /* End of MATLABSystem: '<Root>/I2C Write' */

  /* Update for UnitDelay: '<S1>/UD'
   *
   * Block description for '<S1>/UD':
   *
   *  Store in Global RAM
   */
  untitled_DW.UD_DSTATE[0] = untitled_B.Sum[0];
  untitled_DW.UD_DSTATE[1] = untitled_B.Sum[1];
  untitled_DW.UD_DSTATE[2] = untitled_B.Sum[2];

  /* External mode */
  rtExtModeUploadCheckTrigger(1);

  {                                    /* Sample time: [0.2s, 0.0s] */
    rtExtModeUpload(0, (real_T)untitled_M->Timing.taskTime0);
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.2s, 0.0s] */
    if ((rtmGetTFinal(untitled_M)!=-1) &&
        !((rtmGetTFinal(untitled_M)-untitled_M->Timing.taskTime0) >
          untitled_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(untitled_M, "Simulation finished");
    }

    if (rtmGetStopRequested(untitled_M)) {
      rtmSetErrorStatus(untitled_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  untitled_M->Timing.taskTime0 =
    (++untitled_M->Timing.clockTick0) * untitled_M->Timing.stepSize0;
}

/* Model initialize function */
void untitled_initialize(void)
{
  /* Registration code */
  rtmSetTFinal(untitled_M, -1);
  untitled_M->Timing.stepSize0 = 0.2;

  /* External mode info */
  untitled_M->Sizes.checksums[0] = (2618385146U);
  untitled_M->Sizes.checksums[1] = (1665524796U);
  untitled_M->Sizes.checksums[2] = (3575937151U);
  untitled_M->Sizes.checksums[3] = (613321552U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[3];
    untitled_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(untitled_M->extModeInfo,
      &untitled_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(untitled_M->extModeInfo, untitled_M->Sizes.checksums);
    rteiSetTPtr(untitled_M->extModeInfo, rtmGetTPtr(untitled_M));
  }

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    untitled_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 21;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  {
    codertarget_arduinobase_int_b_T *obj;
    uint32_T i2cname;
    codertarget_arduinobase_inter_T *obj_0;

    /* Start for MATLABSystem: '<Root>/I2C Read' */
    untitled_DW.obj.matlabCodegenIsDeleted = true;
    untitled_DW.obj.isInitialized = 0L;
    untitled_DW.obj.SampleTime = -1.0;
    untitled_DW.obj.matlabCodegenIsDeleted = false;
    SystemProp_matlabCodegenSetAn_b(&untitled_DW.obj, &untitled_DW.gobj_0);
    untitled_DW.obj.SampleTime = untitled_P.I2CRead_SampleTime;
    obj = &untitled_DW.obj;
    untitled_DW.obj.isSetupComplete = false;
    untitled_DW.obj.isInitialized = 1L;
    i2cname = 0;
    obj->MW_I2C_HANDLE = MW_I2C_Open(i2cname, 0);
    MW_I2C_SetBusSpeed(untitled_DW.obj.MW_I2C_HANDLE, 100000.0);
    untitled_DW.obj.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/I2C Write' */
    untitled_DW.obj_p.matlabCodegenIsDeleted = true;
    untitled_DW.obj_p.isInitialized = 0L;
    untitled_DW.obj_p.matlabCodegenIsDeleted = false;
    SystemProp_matlabCodegenSetAnyP(&untitled_DW.obj_p, &untitled_DW.gobj_0_b);
    obj_0 = &untitled_DW.obj_p;
    untitled_DW.obj_p.isSetupComplete = false;
    untitled_DW.obj_p.isInitialized = 1L;
    i2cname = 0;
    obj_0->MW_I2C_HANDLE = MW_I2C_Open(i2cname, 0);
    MW_I2C_SetBusSpeed(untitled_DW.obj_p.MW_I2C_HANDLE, 100000.0);
    untitled_DW.obj_p.isSetupComplete = true;

    /* InitializeConditions for UnitDelay: '<S1>/UD'
     *
     * Block description for '<S1>/UD':
     *
     *  Store in Global RAM
     */
    untitled_DW.UD_DSTATE[0] = untitled_P.TransferFcnFirstOrder_ICPrevOut;
    untitled_DW.UD_DSTATE[1] = untitled_P.TransferFcnFirstOrder_ICPrevOut;
    untitled_DW.UD_DSTATE[2] = untitled_P.TransferFcnFirstOrder_ICPrevOut;
  }
}

/* Model terminate function */
void untitled_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/I2C Read' */
  matlabCodegenHandle_matlabCod_b(&untitled_DW.obj);

  /* Terminate for MATLABSystem: '<Root>/I2C Write' */
  matlabCodegenHandle_matlabCodeg(&untitled_DW.obj_p);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
