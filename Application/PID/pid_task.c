#include "pid_task.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  PIDTask_Init(PID_HandlerType *PIDx, PID_HandlerType pidx)
{
	return PIDLib_Init(PIDx, pidx);
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
float	 PIDTask_PosCalc(PID_HandlerType *PIDx, float setVal)
{
	return PIDLib_PosCalc(PIDx, setVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
float	 PIDTask_IncCalc(PID_HandlerType *PIDx, float setVal)
{
	return PIDLib_IncCalc(PIDx, setVal);
}