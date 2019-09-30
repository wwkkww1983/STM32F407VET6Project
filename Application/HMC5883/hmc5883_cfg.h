#ifndef HMC5883_CFG_H_
#define HMC5883_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include"complier_lib.h"
	//////////////////////////////////////////////////////////////////////////////////////

	//===���üĴ���A(Configuration Register A)
	#define	HMC5883_CRA_REG			0x00	
	//===���üĴ���B
	#define HMC5883_CRB_REG			0x01	
	//===ģʽ�Ĵ���
	#define HMC5883_MR_REG			0x02			
	//===�������X MSB�Ĵ���
	#define HMC5883_DXRA_REG		0x03		
	//===�������X LSB�Ĵ���
	#define HMC5883_DXRB_REG		0x04			
	//===�������Z MSB�Ĵ���
	#define HMC5883_DZRA_REG		0x05		
	//==�������Z LSB�Ĵ���
	#define HMC5883_DZRB_REG		0x06		
	//==�������Y MSB�Ĵ���
	#define HMC5883_DYRA_REG		0x07	
	//==�������Y LSB�Ĵ���
	#define HMC5883_DYRB_REG		0x08	
	//==״̬�Ĵ���
	#define HMC5883_SB_REG			0x09	
	//==ʶ��Ĵ���A
	#define HMC5883_IRA_REG			0x0A			
	//==ʶ��Ĵ���B
	#define HMC5883_IRB_REG			0x0B			

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*HMC5883_CFG_H_ */