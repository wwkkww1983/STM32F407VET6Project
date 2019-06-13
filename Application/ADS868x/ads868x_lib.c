#include "ADS868X_lib.h"

UINT8_T ADS868XLib_SPI_Init(ADS868X_HandlerType* ADS868xx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHW)
{

}
UINT8_T ADS868XLib_SPI_WriteCommandReg(ADS868X_HandlerType* ADS868xx, UINT32_T cmd)
{

}
UINT8_T ADS868XLib_SPI_WriteProgramReg(ADS868X_HandlerType* ADS868xx, UINT8_T addr, UINT8_T val)
{

}
UINT8_T ADS868XLib_SPI_ReadProgramReg(ADS868X_HandlerType* ADS868xx, UINT8_T addr, UINT8_T* pVal)
{

}
UINT8_T ADS868XLib_SPI_ReadCommandBack(ADS868X_HandlerType* ADS868xx, UINT8_T* pVal)
{
}
UINT8_T ADS868XLib_SPI_NO_OP(ADS868X_HandlerType* ADS868xx)
{

}
UINT8_T ADS868XLib_SPI_STDBY(ADS868X_HandlerType* ADS868xx)
{
}
UINT8_T ADS868XLib_SPI_PWRDN(ADS868X_HandlerType* ADS868xx)
{

}
UINT8_T ADS868XLib_SPI_Reset(ADS868X_HandlerType* ADS868xx)
{

}
UINT8_T ADS868XLib_SPI_AUTORST(ADS868X_HandlerType* ADS868xx)
{

}
UINT8_T ADS868XLib_SPI_ManualChannel(ADS868X_HandlerType* ADS868xx, UINT16_T manualCHCmd)
{

}
UINT8_T ADS868XLib_SPI_WriteChipID(ADS868X_HandlerType* ADS868xx, UINT8_T devid)
{

}
UINT8_T ADS868XLib_SPI_ReadChipID(ADS868X_HandlerType* ADS868xx, UINT8_T* pDevID)
{

}
UINT8_T ADS868XLib_SPI_CheckChipID(ADS868X_HandlerType* ADS868xx)
{

}
UINT8_T ADS868XLib_SPI_DetectionDevice(ADS868X_HandlerType* ADS868xx)
{

}
UINT8_T ADS868XLib_SPI_WriteAUTOSEQEN(ADS868X_HandlerType* ADS868xx, UINT8_T seq)
{

}
UINT8_T ADS868XLib_SPI_ReadAUTOSEQEN(ADS868X_HandlerType* ADS868xx, UINT8_T* pAutoSeqEn)
{

}
UINT8_T ADS868XLib_SPI_WriteChannelPWRDN(ADS868X_HandlerType* ADS868xx, UINT8_T ch)
{

}
UINT8_T ADS868XLib_SPI_ReadChannelPWRDN(ADS868X_HandlerType* ADS868xx, UINT8_T* pPWRDN)
{

}
UINT8_T ADS868XLib_SPI_WriteFeature(ADS868X_HandlerType* ADS868xx, UINT8_T feature)
{

}
UINT8_T ADS868XLib_SPI_ReadFeature(ADS868X_HandlerType* ADS868xx, UINT8_T* pFeature)
{

}
UINT8_T ADS868XLib_SPI_WriteChannelRange(ADS868X_HandlerType* ADS868xx, UINT8_T chReg, UINT8_T range)
{

}
UINT8_T ADS868XLib_SPI_ReadChannelRange(ADS868X_HandlerType* ADS868xx, UINT8_T chReg, UINT8_T* pRange)
{

}
UINT8_T ADS868XLib_SPI_ChannelRange(ADS868X_HandlerType* ADS868xx, UINT8_T chIndex)
{

}
UINT8_T ADS868XLib_SPI_CalcChannelPower(ADS868X_HandlerType* ADS868xx, UINT8_T chIndex, UINT8_T isCalcDelta)
{

}
UINT8_T ADS868XLib_SPI_GetAutoRSTResult(ADS868X_HandlerType* ADS868xx, UINT8_T chNum)
{

}
UINT8_T ADS868XLib_SPI_GetAutoRSTNSampleResult(ADS868X_HandlerType* ADS868xx, UINT8_T chNum)
{

}
UINT8_T ADS868XLib_SPI_GetManualChannelResult(ADS868X_HandlerType* ADS868xx, UINT16_T manualChannel)
{

}
UINT8_T ADS868XLib_SPI_GetManualChannelNSampleResult(ADS868X_HandlerType* ADS868xx, UINT16_T manualChannel)
{

}
UINT8_T ADS868XLib_SPI_CalibrationChannelErr(ADS868X_HandlerType* ADS868xx)
{

}
UINT8_T ADS868XLib_SPI_ConfigInit(ADS868X_HandlerType* ADS868xx)
{

}