#ifndef HMC5883_CFG_H_
#define HMC5883_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include"complier_lib.h"
	//////////////////////////////////////////////////////////////////////////////////////

	//===配置寄存器A(Configuration Register A)
	#define	HMC5883_CRA_REG			0x00	
	//===配置寄存器B
	#define HMC5883_CRB_REG			0x01	
	//===模式寄存器
	#define HMC5883_MR_REG			0x02			
	//===数据输出X MSB寄存器
	#define HMC5883_DXRA_REG		0x03		
	//===数据输出X LSB寄存器
	#define HMC5883_DXRB_REG		0x04			
	//===数据输出Z MSB寄存器
	#define HMC5883_DZRA_REG		0x05		
	//==数据输出Z LSB寄存器
	#define HMC5883_DZRB_REG		0x06		
	//==数据输出Y MSB寄存器
	#define HMC5883_DYRA_REG		0x07	
	//==数据输出Y LSB寄存器
	#define HMC5883_DYRB_REG		0x08	
	//==状态寄存器
	#define HMC5883_SB_REG			0x09	
	//==识别寄存器A
	#define HMC5883_IRA_REG			0x0A			
	//==识别寄存器B
	#define HMC5883_IRB_REG			0x0B			

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*HMC5883_CFG_H_ */