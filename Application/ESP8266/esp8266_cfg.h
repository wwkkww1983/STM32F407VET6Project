#ifndef ESP8266_CFG_H_
#define ESP8266_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "systick_task.h"
	#include "usart_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	
	//===消息只是
	typedef enum
	{
		ESP8266_SUCCESS = 0,																							//---成功
		ESP8266_BUSY,																									//---忙碌状态
		ESP8266_ERROR_ERR ,																								//---错误
		ESP8266_ERROR_FAIL,																								//---失败
		ESP8266_ERROR_READY ,																							//---准备
		ESP8266_ERROR_BUSY ,																							//---忙碌
		ESP8266_ERROR_UNKNOWN ,																							//---不是被
		ESP8266_ERROR_TIMEOUT ,																							//---超时
		ESP8266_ERROR_CMD ,																								//---AT命令错误
	}ESP8266_MESSAGE;

	//===工作模式
	typedef enum
	{
		ESP8266_STA = 1,																								//---Station模式
		ESP8266_AP = 2,																									//---AP模式
		ESP8266_STA_AP = 3																								//---AP+Station模式
	}ESP8266_MODE;
	
	//===命令模式
	typedef enum
	{
		ESP8266_CMD_QUERY=0,																							//---查询命令
		ESP8266_CMD_SETUP,																								//---设置命令
		ESP8266_CMD_EXECUTE																								//---执行命令
	}ESP8266_CMD_TYPE;

	//===WIFI热点加密方式
	typedef enum
	{
		ESP8266_OPEN=0,
		ESP8266_WPA_PSK,
		ESP8266_WPA2_PSK,
		ESP8266_WPA_WPA2_PSK
	}ESP8266_WIFI_ENCRYPTION;
	
	typedef enum
	{
		ESP8266_GOTIP = 2,																								//---获取IP
		ESP8266_CONNECTED = 3,																							//---连接状态
		ESP8266_DISCONNECTED = 4,																						//---未连接状态
		ESP8266_NOWIFI = 5,																								//---没有WIFI
	}ESP8266_STATUS;

	//===连接状态
	typedef enum
	{
		ESP8266_TCP=0,																									//---TCP模式
		ESP8266_UDP,																									//---UDP模式
		ESP8266_UNKNOWN																									//---不识别模式
	}ESP8266_CONNECTION_TYPE;
	
	//===网络连接模式
	typedef enum
	{
		ESP8266_CLIENT=0,																								//---客户端
		ESP8266_SERVER																									//---服务端
	}esp8266_NET_TYPE;

	#define ESP8266_BUFFER_MAX_SIZE						1024															//---定义缓存区的大小
	#define ESP8266_USART								pUsart3															//---ESP8266使用的

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*ESP8266_CFG_H_ */