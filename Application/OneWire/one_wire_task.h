#ifndef ONE_WIRE_TASK_H_
#define ONE_WIRE_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "one_wire_lib.h"
	///////////////////////////////////////////////////////////////////////////////////////
	//===��������
	UINT8_T OneWireTask_Init(OneWire_HandleType *OneWirex, void(*pFuncDelayus)(UINT32_T delay));
	UINT8_T OneWireTask_DeInit(OneWire_HandleType *OneWirex);
	UINT8_T OneWireTask_START(OneWire_HandleType *OneWirex);
	UINT8_T OneWireTask_WriteByte(OneWire_HandleType *OneWirex, UINT8_T val);
	UINT8_T OneWireTask_ReadByte(OneWire_HandleType *OneWirex);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*ONE_WIRE_TASK_H_ */