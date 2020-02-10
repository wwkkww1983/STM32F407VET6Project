#include "esp8266_cfg.h"

//===>>>AT命令组	开始	//////////////////////////////////////////////////////////////////////////////////////
//===AT返回命令
const char ESP8266_AT_RESPONSE_OK[] = "OK\r\n";																			//---正确
const char ESP8266_AT_RESPONSE_ERROR[] = "ERROR\r\n";																	//---错误
const char ESP8266_AT_RESPONSE_FAIL[] = "FAIL";																			//---失败
const char ESP8266_AT_RESPONSE_READY[] = "READY!";																		//---准备
const char ESP8266_AT_RESPONSE_RECEIVED[] = "+IPD,";																	//---接收到服务器发来的数据

//===AT基本指令
const char ESP8266_AT_CMD_TEST[] = "";																					//---测试命令
const char ESP8266_AT_CMD_RESET[] = "+RST";																				//---模块重启
const char ESP8266_AT_CMD_VERSION[] = "+GMR";																			//---查看固件版本
const char ESP8266_AT_CMD_DEEP_SLEEP[] = "+GSLP";																		//---进入DepSleep睡眠模式
const char ESP8266_AT_CMD_SET_SLEEP[] = "+SLEEP";																		//---设置休眠模式
const char ESP8266_AT_CMD_ECHO_OPEN[] = "E1";																			//---打开回显
const char ESP8266_AT_CMD_ECHO_CLOSE[] = "E0";																			//---关闭回显
const char ESP8266_AT_CMD_RESTORE[] = "+RESTORE";																		//---恢复出厂设置
const char ESP8266_AT_CMD_UART[] = "+UART";																				//---设置串口模式
const char ESP8266_AT_CMD_UART_CUR[] = "+UART_CUR";																		//---当前临时配置
const char ESP8266_AT_CMD_UART_DEF[] = "+UART_DEF";																		//---UART默认配置，保存到Flash
const char ESP8266_AT_CMD_SYSRAM[] = "+SYSRAM";																			//---查询系统当前剩余内存
const char ESP8266_AT_CMD_SYSMSG_CUR[] = "+SYSMSG_CUR";																	//---设置当前系统消息
const char ESP8266_AT_CMD_SYSMSG_DEG[] = "+SYSMSG_DEF";																	//---设置默认系统消息

//===WIFI功能命令
const char ESP8266_AT_WIFI_MODE[] = "+CWMODE";																			//---设置模式，响应OK
const char ESP8266_AT_WIFI_DEF[] = " +CWMODE_DEF";																		//---配置WiFi模组工作模式为单STA模式，并把配置保存在flash
const char ESP8266_AT_WIFI_CONNECT_AP[] = "+CWJAP";																		//---加入热点，连接路由器，响应OK
const char ESP8266_AT_WIFI_LIST_IP[] = "+CIFSR";																		//---查询设备的IP地址
const char ESP8266_AT_WIFI_LIST_AP[] = "+CWLAP";																		//---产看当前的无线路由器列表
const char ESP8266_AT_WIFI_DISCONNECT[] = "+CWQAP";																		//---退出热点
const char ESP8266_AT_WIFI_AP_CONFIG[] = "+CWSAP";																		//---设置热点
const char ESP8266_AT_WIFI_STA_IP[] = "+CWLIF";																			//---获取连接信息
const char ESP8266_AT_WIFI_DHCP_EN[] = "+CWDHCP";																		//---设置DHCO
const char ESP8266_AT_WIFI_AUTO_CONNECT[] = "+CWAUTOCONN";																//---使能上电自动连接AP
const char ESP8266_AT_WIFI_SET_STA_MAC[] = "+CIPSTAMAC";																//---设置MAC地址							
const char ESP8266_AT_WIFI_SET_STA_IP[] = "+CIPSTA";																	//---设置IP地址
const char ESP8266_AT_WIFI_SET_AP_IP[] = "+CIPAP";																		//---设置热点的IP地址
const char ESP8266_AT_WIFI_STARTSMART[] = "+CWSTARTSMART";																//---无论配网是否成功，都需要释放快连所占的内存
const char ESP8266_AT_WIFI_STOPSMART[] = "+CWSTOPSMART";																//---无论配网是否成功，都需要释放快连所占的内存
const char ESP8266_AT_WIFI_STARTDISCOVER[] = "+CWSTARTDISCOVER";														//---开启可被局域网的微信探测的模式
const char ESP8266_AT_WIFI_STOPDISCOVER[] = "+CWSTOPDISCOVER";															//---关闭可被局域网的微信探测的模式
const char ESP8266_AT_WIFI_WPS[] = "+WPS";																				//---设置WPS
const char ESP8266_AT_WIFI_MDNS[] = "+MDNS";																			//---设置MDNS功能
const char ESP8266_AT_WIFI_SET_STA_NAME[] = "+CWHOSTNAME";																//---设置STA的主机名称
const char ESP8266_AT_WIFI_SET_STA_COUNTRY[] = "+CWCOUNTRY";															//---设置WIFI的国家码

//===TCP/IP Commands
const char ESP8266_TCP_IP_STARTSMART[] = "+CWSTARTSMART";																//---无论配网是否成功，都需要释放快连所占的内存
const char ESP8266_TCP_IP_STOPSMART[] = "+CWSTOPSMART";																	//---无论配网是否成功，都需要释放快连所占的内存
const char ESP8266_TCP_IP_STATUS[] = "+CIPSTATUS";																		//---查询网络连接状态，响应OK
const char ESP8266_TCP_IP_DOMAIN[] = "+CIPDOMAIN";																		//---查域名解析功能
const char ESP8266_TCP_IP_CONNECT[] = "+CIPSTART";																		//---连接服务器
const char ESP8266_TCP_IP_SSL_SIZE[] = "+CIPSSLSIZE";																	//---设置SSL的缓存区大小
const char ESP8266_TCP_IP_SSL_CONF[] = "+CIPSSLCONF";																	//---设置SSL Client
const char ESP8266_TCP_IP_SEND[] = "+CIPSEND";																			//---启动透传
const char ESP8266_TCP_IP_SENDX[] = "+CIPSENDX";																		//---发送数据，达到设置⻓长度，或者遇到字符 \0，则发送数据
const char ESP8266_TCP_IP_SENDBUF[] = "+CIPSENDBUF";																	//---数据写⼊入TCP 发包缓存
const char ESP8266_TCP_IP_BUFRESET[] = "+CIPBUFRESET";																	//---重置计数（TCP 发包缓存）
const char ESP8266_TCP_IP_BUFSTATUS[] = "+CIPBUFSTATUS";																//---查询 TCP 发包缓存的状态
const char ESP8266_TCP_IP_CHECKSEQ[] = "+CIPCHECKSEQ";																	//---查询写⼊入 TCP 发包缓存的某包是否成功发送
const char ESP8266_TCP_IP_CLOSE[] = "+CIPCLOSE";																		//---关闭传输
const char ESP8266_TCP_IP_LIST_IP[] = "+CIFSR";																			//---查询设备的IP地址
const char ESP8266_TCP_IP_IP_MUX[] = "+CIPMUX";																			//---使能多连接
const char ESP8266_TCP_IP_SERVER_CONFIG[] = "+CIPSERVER";																//---建立TCP服务器
const char ESP8266_TCP_IP_SERVER_MAX_COUNT[] = "+CIPSERVERMAXCOUT";														//---设置服务器器允许建⽴立的最⼤大连接
const char ESP8266_TCP_IP_MODE[] = "+CIPMODE";																			//---设置透传模式，0---普通传输模式，1---透传模式，仅⽀支持 TCP 单连接和 UDP 固定通信对端的情况
const char ESP8266_TCP_IP_SAVE_TRANS_LINK[] = "+SAVETRANSLINK";															//---保存透传连接到 Flash
const char ESP8266_TCP_IP_SET_SERVER_TIMEOUT[] = "+CIPSTO";																//---设置作为 TCP 服务器器时的超时时间
const char ESP8266_TCP_IP_PING[] = "+PING";																				//---pin功能
const char ESP8266_TCP_IP_UPDATE[] = "+CIUPDATE";																		//---通过WiFi升级软件
const char ESP8266_TCP_IP_IPDINFO[] = "+CIPDINFO";																		//---接收⽹网络数据时，+IPD 是否提示对端 IP 和端⼝口
const char ESP8266_TCP_IP_RECVMODE[] = "+CIPRECVMODE";																	//---设置 TCP 接收模式
const char ESP8266_TCP_IP_RECVDATA[] = "+CIPRECVDATA";																	//---TCP 被动接收模式下，读取缓存的 TCP 数据
const char ESP8266_TCP_IP_RECVLEN[] = "+CIPRECVLEN";																	//---TCP 被动接收模式下，查询缓存 TCP 数据的⻓长度TCP 数据
const char ESP8266_TCP_IP_SNTPCFG[] = "+CIPSNTPCFG";																	//---设置时域和 SNTP 服务器器
const char ESP8266_TCP_IP_SNTPTIME[] = "+CIPSNTPTIME";																	//---查询 SNTP 时间
const char ESP8266_TCP_IP_DNS[] = "+CIPDNS";																			//---⾃自定义 DNS 服务器器

//===GPIO Commands
const char ESP8266_GPIO_PINMODE[] = "+PINMODE";																			//---配置端口输入输出模式
const char ESP8266_GPIO_PINWRITE[] = "+PINWRITE";																		//---设置的端口输出高低电平
const char ESP8266_GPIO_PINREAD[] = "+PINREAD";																			//---读取端口的电平信号
//===<<<AT命令组	结束//////////////////////////////////////////////////////////////////////////////////////

UINT8_T g_ESP8266_RX_BUFFER[ESP8266_BUFFER_MAX_SIZE] = { 0 };															//---接收缓存区
UINT8_T g_ESP8266_TX_BUFFER[ESP8266_BUFFER_MAX_SIZE] = { 0 };															//---接收缓存区


UINT8_T ESP8266_Init()
{
	return OK_0;
}

UINT8_T ESP8266_SendString(void)
{
	return OK_0;
}

UINT8_T ESP8266_ExitTransparentMode(void)
{
	return OK_0;
}

