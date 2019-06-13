#include "dac_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_GPIO_Init(void)
{
	//---ʹ��GPIO��ʱ��
	GPIOTask_Clock(GPIOA, 1);

	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---GPIO�ĳ�ʼ��----
	//---DAC1---PA4
	//---DAC2---PA5
	GPIO_InitStruct.Pin = LL_GPIO_PIN_4 | LL_GPIO_PIN_5;					//---��Ӧ��GPIO������
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;														//---����״̬Ϊģ����������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;														//---���ö˿�����ʹ��

	//---GPIO�ĳ�ʼ��
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_Clock(UINT8_T isEnableid)
{
	//---����DACʱ��
	if (isEnableid)
	{
		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_DAC1);
	}
	else
	{
		LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_DAC1);
	}

	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_DAC1_Init(void)
{
	LL_DAC_InitTypeDef DAC_InitStruct = { 0 };
	//---ʹ���������
	DAC_InitStruct.TriggerSource = LL_DAC_TRIG_SOFTWARE;
	//---��ʹ�ò��η���
	DAC_InitStruct.WaveAutoGeneration = LL_DAC_WAVE_AUTO_GENERATION_NONE;
	//---ʹ��DAC���������
	DAC_InitStruct.OutputBuffer = LL_DAC_OUTPUT_BUFFER_DISABLE;//LL_DAC_OUTPUT_BUFFER_ENABLE;
	//---��ʼ��DAC
	LL_DAC_Init(DAC, LL_DAC_CHANNEL_1, &DAC_InitStruct);
	//---ʹ��DAC
	LL_DAC_Enable(DAC, LL_DAC_CHANNEL_1);
	//---�������������ʽ,�Ҷ��룬12λ����
	LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_1, 0);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_DAC2_Init(void)
{
	LL_DAC_InitTypeDef DAC_InitStruct = { 0 };
	//---ʹ���������
	DAC_InitStruct.TriggerSource = LL_DAC_TRIG_SOFTWARE;
	//---��ʹ�ò��η���
	DAC_InitStruct.WaveAutoGeneration = LL_DAC_WAVE_AUTO_GENERATION_NONE;
	//---ʹ��DAC���������
	DAC_InitStruct.OutputBuffer = LL_DAC_OUTPUT_BUFFER_DISABLE;// LL_DAC_OUTPUT_BUFFER_ENABLE;
	//---��ʼ��DAC
	LL_DAC_Init(DAC, LL_DAC_CHANNEL_2, &DAC_InitStruct);
	//---ʹ��DAC
	LL_DAC_Enable(DAC, LL_DAC_CHANNEL_2);
	//---�������������ʽ,�Ҷ��룬12λ����
	LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_2, 0);

	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_Init(void)
{
	DAC_GPIO_Init();
	DAC_Clock(1);
	DAC_DAC1_Init();
	DAC_DAC2_Init();
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_DAC1_WriteVoltageUV(UINT32_T volUV)
{
	UINT32_T vol = 0;
	//---uv��������
	UINT32_T volBaseUV= (DAC_REF_POWER_UV / 4096);
	//---�ж��Ƿ񳬳�����
	if (volUV > DAC_REF_POWER_UV)
	{
		volUV = DAC_REF_POWER_UV;
	}
	//---ͨ������õ�ģ����
	vol =(UINT32_T) (volUV / volBaseUV);
	//---�ж��Ƿ�����
	if (vol > 0xFFF)
	{
		vol = 0xFFF;
	}
	//---�������������ʽ,�Ҷ��룬12λ����
	LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_1, vol);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_DAC1_WriteVoltageMV(UINT32_T volMV)
{
	return DAC_DAC1_WriteVoltageUV(volMV * 1000);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_DAC1_WriteVoltageV(float volV)
{
	return DAC_DAC1_WriteVoltageUV((UINT32_T)(volV * 1000000));
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_DAC2_WriteVoltageUV(UINT32_T volUV)
{
	UINT32_T vol = 0;
	//---uv��������
	UINT32_T volBaseUV = (DAC_REF_POWER_UV / 4096);
	//---�ж��Ƿ񳬳�����
	if (volUV > DAC_REF_POWER_UV)
	{
		volUV = DAC_REF_POWER_UV;
	}
	//---ͨ������õ�ģ����
	vol = (UINT32_T)(volUV / volBaseUV);
	//---�ж��Ƿ�����
	if (vol > 0xFFF)
	{
		vol = 0xFFF;
	}
	//---�������������ʽ,�Ҷ��룬12λ����
	LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_2, vol);

	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_DAC2_WriteVoltageMV(UINT32_T volMV)
{
	return DAC_DAC2_WriteVoltageUV(volMV * 1000);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_DAC2_WriteVoltageV(float volV)
{
	return DAC_DAC2_WriteVoltageUV((UINT32_T)(volV * 1000000));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_DAC_WriteVoltageUV(UINT32_T volUV)
{
	UINT32_T vol = 0;
	//---uv��������
	UINT32_T volBaseUV = (DAC_REF_POWER_UV / 4096);
	//---�ж��Ƿ񳬳�����
	if (volUV > DAC_REF_POWER_UV)
	{
		volUV = DAC_REF_POWER_UV;
	}
	//---ͨ������õ�ģ����
	vol = (UINT32_T)(volUV / volBaseUV);
	//---�ж��Ƿ�����
	if (vol > 0xFFF)
	{
		vol = 0xFFF;
	}
	//---�������������ʽ,�Ҷ��룬12λ����
	LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_1, vol);
	LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_2, vol);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_DAC_WriteVoltageMV(UINT32_T volMV)
{
	return DAC_DAC_WriteVoltageUV(volMV * 1000);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_DAC_WriteVoltageV(float volV)
{
	return DAC_DAC_WriteVoltageUV((UINT32_T)(volV * 1000000));
}