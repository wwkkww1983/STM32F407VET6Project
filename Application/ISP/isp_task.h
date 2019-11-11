#ifndef ISP_TASK_H_
#define ISP_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "isp_lib.h"
	#include "usart_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===打开或者关闭ISP
	#define	CMD_ISP_OPEN_CLOSE							0x10	
	//===ISP擦除芯片
	#define	CMD_ISP_ERASE								0x11	
	//===ISP按页读取Flash
	#define CMD_ISP_FLASH_PAGE_READ						0x12	
	//===ISP按页写入Flash
	#define CMD_ISP_FLASH_PAGE_WRITE					0x13		
	//===ISP按页读取Eeeprom
	#define	CMD_ISP_EEPROM_PAGE_READ					0x14		
	//===ISP按页写入Eeprom
	#define CMD_ISP_EEPROM_PAGE_WRITE					0x15		
	//===ISP读取熔丝位和锁定位
	#define CMD_ISP_FUSE_LOCK_READ						0x16		
	//===ISP写入熔丝位
	#define CMD_ISP_FUSE_WRITE							0x17	
	//===ISP写入锁定位
	#define CMD_ISP_LOCK_WRITE							0x18		
	//===ISP读取芯片标识
	#define CMD_ISP_ID_READ								0x19	
	//===ISP读取校准字
	#define CMD_ISP_CALIBRATIONBYTE_READ				0x1A		
	//===ISP读取ROM信息
	#define CMD_ISP_ROM_PAGE_READ						0x1B		

	//===定义实验室自动化测试
	#define LAB_AUTO_ISP_TEST

	//===函数定义
	UINT8_T ISPTask_Init(ISP_HandlerType *ISPx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void));
	UINT8_T ISPTask_DeInit(ISP_HandlerType *ISPx);
	UINT8_T ISPTask_EnterProg(ISP_HandlerType *ISPx, UINT8_T isPollReady);
	UINT8_T ISPTask_ExitProg(ISP_HandlerType *ISPx);
	UINT8_T ISPTask_AddWatch(ISP_HandlerType* ISPx);
	UINT8_T ISPTask_RemoveWatch(ISP_HandlerType* ISPx);
	UINT8_T ISPTask_RefreshWatch(ISP_HandlerType* ISPx);
	UINT8_T ISPTask_ReadReady(ISP_HandlerType *ISPx);
	UINT8_T ISPTask_EraseChip(ISP_HandlerType *ISPx);
	UINT8_T ISPTask_ReadChipID(ISP_HandlerType *ISPx, UINT8_T *pVal);
	UINT8_T ISPTask_ReadChipCalibration(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T length);
	UINT8_T ISPTask_ReadChipFuse(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse);
	UINT8_T ISPTask_ReadChipLock(ISP_HandlerType *ISPx, UINT8_T *pVal);
	UINT8_T ISPTask_ReadChipRom(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T addr, UINT16_T length);
	UINT8_T ISPTask_WriteChipFuse(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse);
	UINT8_T ISPTask_WriteChipLock(ISP_HandlerType *ISPx, UINT8_T *pVal);
	UINT8_T ISPTask_ReadChipEepromAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length);
	UINT8_T ISPTask_ReadChipEepromLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length);
	UINT8_T ISPTask_WriteChipEepromAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length);
	UINT8_T ISPTask_WriteChipEepromLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length);
	UINT8_T ISPTask_WriteChipEepromAddrWithJumpEmpty(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length);
	UINT8_T ISPTask_WriteChipEepromLongAddrWithJumpEmpty(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length);
	UINT8_T ISPTask_UpdateExternAddr(ISP_HandlerType *ISPx, UINT8_T addr);
	UINT8_T ISPTask_UpdateExternLongAddr(ISP_HandlerType *ISPx, UINT32_T addr);
	UINT8_T ISPTask_ReadChipFlashAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length);
	UINT8_T ISPTask_ReadChipFlashLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT32_T addr, UINT16_T length);
	UINT8_T ISPTask_UpdateChipFlashBuffer(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T index, UINT16_T length);
	UINT8_T ISPTask_UpdateChipFlashAddr(ISP_HandlerType *ISPx, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr);
	UINT8_T ISPTask_UpdateChipFlashLongAddr(ISP_HandlerType *ISPx, UINT32_T addr);
	UINT8_T ISPTask_USARTCmd_Task(ISP_HandlerType* ISPx, USART_HandlerType* USARTx);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*ISP_TASK_H_ */
