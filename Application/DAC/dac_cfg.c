#include "dac_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_GPIO_Init(void)
{
	//---使能GPIO的时钟
	GPIOTask_Clock(GPIOA, 1);

	//---GPIO的结构体
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---GPIO的初始化----
	//---DAC1---PA4
	//---DAC2---PA5
	GPIO_InitStruct.Pin = LL_GPIO_PIN_4 | LL_GPIO_PIN_5;					//---对应的GPIO的引脚
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;														//---配置状态为模拟输入引脚
	GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;														//---设置端口下拉使能

	//---GPIO的初始化
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_Clock(UINT8_T isEnableid)
{
	//---配置DAC时钟
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
//////函		数：
//////功		能：
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_DAC1_Init(void)
{
	LL_DAC_InitTypeDef DAC_InitStruct = { 0 };
	//---使用软件触发
	DAC_InitStruct.TriggerSource = LL_DAC_TRIG_SOFTWARE;
	//---不使用波形发生
	DAC_InitStruct.WaveAutoGeneration = LL_DAC_WAVE_AUTO_GENERATION_NONE;
	//---使能DAC输出缓存器
	DAC_InitStruct.OutputBuffer = LL_DAC_OUTPUT_BUFFER_DISABLE;//LL_DAC_OUTPUT_BUFFER_ENABLE;
	//---初始化DAC
	LL_DAC_Init(DAC, LL_DAC_CHANNEL_1, &DAC_InitStruct);
	//---使能DAC
	LL_DAC_Enable(DAC, LL_DAC_CHANNEL_1);
	//---设置数据输出格式,右对齐，12位数据
	LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_1, 0);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_DAC2_Init(void)
{
	LL_DAC_InitTypeDef DAC_InitStruct = { 0 };
	//---使用软件触发
	DAC_InitStruct.TriggerSource = LL_DAC_TRIG_SOFTWARE;
	//---不使用波形发生
	DAC_InitStruct.WaveAutoGeneration = LL_DAC_WAVE_AUTO_GENERATION_NONE;
	//---使能DAC输出缓存器
	DAC_InitStruct.OutputBuffer = LL_DAC_OUTPUT_BUFFER_DISABLE;// LL_DAC_OUTPUT_BUFFER_ENABLE;
	//---初始化DAC
	LL_DAC_Init(DAC, LL_DAC_CHANNEL_2, &DAC_InitStruct);
	//---使能DAC
	LL_DAC_Enable(DAC, LL_DAC_CHANNEL_2);
	//---设置数据输出格式,右对齐，12位数据
	LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_2, 0);

	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数：
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_DAC1_WriteVoltageUV(UINT32_T volUV)
{
	UINT32_T vol = 0;
	//---uv的数字量
	UINT32_T volBaseUV= (DAC_REF_POWER_UV / 4096);
	//---判断是否超出量程
	if (volUV > DAC_REF_POWER_UV)
	{
		volUV = DAC_REF_POWER_UV;
	}
	//---通过计算得到模拟量
	vol =(UINT32_T) (volUV / volBaseUV);
	//---判断是否超量程
	if (vol > 0xFFF)
	{
		vol = 0xFFF;
	}
	//---设置数据输出格式,右对齐，12位数据
	LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_1, vol);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_DAC1_WriteVoltageMV(UINT32_T volMV)
{
	return DAC_DAC1_WriteVoltageUV(volMV * 1000);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_DAC1_WriteVoltageV(float volV)
{
	return DAC_DAC1_WriteVoltageUV((UINT32_T)(volV * 1000000));
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_DAC2_WriteVoltageUV(UINT32_T volUV)
{
	UINT32_T vol = 0;
	//---uv的数字量
	UINT32_T volBaseUV = (DAC_REF_POWER_UV / 4096);
	//---判断是否超出量程
	if (volUV > DAC_REF_POWER_UV)
	{
		volUV = DAC_REF_POWER_UV;
	}
	//---通过计算得到模拟量
	vol = (UINT32_T)(volUV / volBaseUV);
	//---判断是否超量程
	if (vol > 0xFFF)
	{
		vol = 0xFFF;
	}
	//---设置数据输出格式,右对齐，12位数据
	LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_2, vol);

	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_DAC2_WriteVoltageMV(UINT32_T volMV)
{
	return DAC_DAC2_WriteVoltageUV(volMV * 1000);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_DAC2_WriteVoltageV(float volV)
{
	return DAC_DAC2_WriteVoltageUV((UINT32_T)(volV * 1000000));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_DAC_WriteVoltageUV(UINT32_T volUV)
{
	UINT32_T vol = 0;
	//---uv的数字量
	UINT32_T volBaseUV = (DAC_REF_POWER_UV / 4096);
	//---判断是否超出量程
	if (volUV > DAC_REF_POWER_UV)
	{
		volUV = DAC_REF_POWER_UV;
	}
	//---通过计算得到模拟量
	vol = (UINT32_T)(volUV / volBaseUV);
	//---判断是否超量程
	if (vol > 0xFFF)
	{
		vol = 0xFFF;
	}
	//---设置数据输出格式,右对齐，12位数据
	LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_1, vol);
	LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_2, vol);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_DAC_WriteVoltageMV(UINT32_T volMV)
{
	return DAC_DAC_WriteVoltageUV(volMV * 1000);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_DAC_WriteVoltageV(float volV)
{
	return DAC_DAC_WriteVoltageUV((UINT32_T)(volV * 1000000));
}