#include "ADS869X_lib.h"

UINT8_T ADS869XLib_SPI_Init(ADS869X_HandlerType* ADS869xx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHW)
{

}
UINT8_T ADS869XLib_SPI_WriteCommandReg(ADS869X_HandlerType* ADS869xx, UINT32_T cmd)
{

}
UINT8_T ADS869XLib_SPI_WriteProgramReg(ADS869X_HandlerType* ADS869xx, UINT8_T addr, UINT8_T val)
{

}
UINT8_T ADS869XLib_SPI_ReadProgramReg(ADS869X_HandlerType* ADS869xx, UINT8_T addr, UINT8_T* pVal)
{

}
UINT8_T ADS869XLib_SPI_ReadCommandBack(ADS869X_HandlerType* ADS869xx, UINT8_T* pVal)
{
}
UINT8_T ADS869XLib_SPI_NO_OP(ADS869X_HandlerType* ADS869xx)
{

}
UINT8_T ADS869XLib_SPI_STDBY(ADS869X_HandlerType* ADS869xx)
{
}
UINT8_T ADS869XLib_SPI_PWRDN(ADS869X_HandlerType* ADS869xx)
{

}
UINT8_T ADS869XLib_SPI_Reset(ADS869X_HandlerType* ADS869xx)
{

}
UINT8_T ADS869XLib_SPI_AUTORST(ADS869X_HandlerType* ADS869xx)
{

}
UINT8_T ADS869XLib_SPI_ManualChannel(ADS869X_HandlerType* ADS869xx, UINT16_T manualCHCmd)
{

}
UINT8_T ADS869XLib_SPI_WriteChipID(ADS869X_HandlerType* ADS869xx, UINT8_T devid)
{

}
UINT8_T ADS869XLib_SPI_ReadChipID(ADS869X_HandlerType* ADS869xx, UINT8_T* pDevID)
{

}
UINT8_T ADS869XLib_SPI_CheckChipID(ADS869X_HandlerType* ADS869xx)
{

}
UINT8_T ADS869XLib_SPI_DetectionDevice(ADS869X_HandlerType* ADS869xx)
{

}
UINT8_T ADS869XLib_SPI_WriteAUTOSEQEN(ADS869X_HandlerType* ADS869xx, UINT8_T seq)
{

}
UINT8_T ADS869XLib_SPI_ReadAUTOSEQEN(ADS869X_HandlerType* ADS869xx, UINT8_T* pAutoSeqEn)
{

}
UINT8_T ADS869XLib_SPI_WriteChannelPWRDN(ADS869X_HandlerType* ADS869xx, UINT8_T ch)
{

}
UINT8_T ADS869XLib_SPI_ReadChannelPWRDN(ADS869X_HandlerType* ADS869xx, UINT8_T* pPWRDN)
{

}
UINT8_T ADS869XLib_SPI_WriteFeature(ADS869X_HandlerType* ADS869xx, UINT8_T feature)
{

}
UINT8_T ADS869XLib_SPI_ReadFeature(ADS869X_HandlerType* ADS869xx, UINT8_T* pFeature)
{

}
UINT8_T ADS869XLib_SPI_WriteChannelRange(ADS869X_HandlerType* ADS869xx, UINT8_T chReg, UINT8_T range)
{

}
UINT8_T ADS869XLib_SPI_ReadChannelRange(ADS869X_HandlerType* ADS869xx, UINT8_T chReg, UINT8_T* pRange)
{

}
UINT8_T ADS869XLib_SPI_ChannelRange(ADS869X_HandlerType* ADS869xx, UINT8_T chIndex)
{

}
UINT8_T ADS869XLib_SPI_CalcChannelPower(ADS869X_HandlerType* ADS869xx, UINT8_T chIndex, UINT8_T isCalcDelta)
{

}
UINT8_T ADS869XLib_SPI_GetAutoRSTResult(ADS869X_HandlerType* ADS869xx, UINT8_T chNum)
{

}
UINT8_T ADS869XLib_SPI_GetAutoRSTNSampleResult(ADS869X_HandlerType* ADS869xx, UINT8_T chNum)
{

}
UINT8_T ADS869XLib_SPI_GetManualChannelResult(ADS869X_HandlerType* ADS869xx, UINT16_T manualChannel)
{

}
UINT8_T ADS869XLib_SPI_GetManualChannelNSampleResult(ADS869X_HandlerType* ADS869xx, UINT16_T manualChannel)
{

}
UINT8_T ADS869XLib_SPI_CalibrationChannelErr(ADS869X_HandlerType* ADS869xx)
{

}
UINT8_T ADS869XLib_SPI_ConfigInit(ADS869X_HandlerType* ADS869xx)
{

}