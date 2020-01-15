#ifndef ESP8266_CFG_H_
#define ESP8266_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===AT��������
	const char ESP8266_AT_RESPONSE_OK[]			= "OK\r\n";
	const char ESP8266_AT_RESPONSE_ERROR[]		= "ERROR\r\n";
	const char ESP8266_AT_RESPONSE_FAIL[]		= "FAIL";
	const char ESP8266_AT_RESPONSE_READY[]		= "READY!";
	const char ESP8266_AT_RESPONSE_RECEIVED[]	= "+IPD,";

	//===AT����ָ��
	const char ESP8266_AT_CMD_TEST[]			= "";																																//---��������
	const char ESP8266_AT_CMD_RESET[]			= "+RST";																															//---ģ������
	const char ESP8266_AT_CMD_VERSION[]			= "+GMR";																															//---�鿴�̼��汾
	const char ESP8266_AT_CMD_DEEP_SLEEP[]		= "+GSLP";																															//---����DepSleep˯��ģʽ
	const char ESP8266_AT_CMD_DEEP_SLEEP[]		= "+SLEEP";																															//---��������ģʽ
	const char ESP8266_AT_CMD_ECHO_OPEN[]		= "E1";																																//---�򿪻���
	const char ESP8266_AT_CMD_ECHO_CLOSE[]		= "E0";																																//---�رջ���
	const char ESP8266_AT_CMD_RESTORE[]			= "+RESTORE";																														//---�ָ���������
	const char ESP8266_AT_CMD_UART[]			= "+UART";																															//---���ô���ģʽ

	//===WIFI��������
	const char ESP8266_AT_WIFI_MODE[]			= "+CWMODE";																														//---����ģʽ
	const char ESP8266_AT_WIFI_CONNECT_AP[]		= "+CWJAP";																															//---�����ȵ�
	const char ESP8266_AT_WIFI_LIST_AP[]		= "+CWLAP";																															//---������ǰ������·�����б�
	const char ESP8266_AT_WIFI_DISCONNECT[]		= "+CWQAP";																															//---�˳��ȵ�
	const char ESP8266_AT_WIFI_AP_CONFIG[]		= "+CWSAP";																															//---
	const char ESP8266_AT_WIFI_STATION_IP[]		= "+CWLIF"; // List station IP's connected to softAP
	const char ESP8266_AT_WIFI_DHCP_EN[]		= "+CWDHCP"; // Enable/disable DHCP
	const char ESP8266_AT_WIFI_AUTO_CONNECT[]	= "+CWAUTOCONN"; // Connect to AP automatically
	const char ESP8266_AT_WIFI_SET_STA_MAC[]	= "+CIPSTAMAC"; // Set MAC address of station
	const char ESP8266_AT_WIFI_GET_STA_MAC[]	= "+CIPSTAMAC"; // Get MAC address of station
	const char ESP8266_AT_WIFI_SET_AP_MAC[]		= "+CIPAPMAC"; // Set MAC address of softAP
	const char ESP8266_AT_WIFI_SET_STA_IP[]		= "+CIPSTA"; // Set IP address of ESP8266 station
	const char ESP8266_AT_WIFI_SET_AP_IP[]		= "+CIPAP"; // Set IP address of ESP8266 softAP

	/////////////////////
	// TCP/IP Commands //
	/////////////////////
	const char ESP8266_TCP_STATUS[] = "+CIPSTATUS"; // Get connection status
	const char ESP8266_TCP_CONNECT[] = "+CIPSTART"; // Establish TCP connection or register UDP port
	const char ESP8266_TCP_SEND[] = "+CIPSEND"; // Send Data
	const char ESP8266_TCP_CLOSE[] = "+CIPCLOSE"; // Close TCP/UDP connection
	const char ESP8266_GET_LOCAL_IP[] = "+CIFSR"; // Get local IP address
	const char ESP8266_TCP_MULTIPLE[] = "+CIPMUX"; // Set multiple connections mode
	const char ESP8266_SERVER_CONFIG[] = "+CIPSERVER"; // Configure as server
	const char ESP8266_TRANSMISSION_MODE[] = "+CIPMODE"; // Set transmission mode
	//!const char ESP8266_SET_SERVER_TIMEOUT[] = "+CIPSTO"; // Set timeout when ESP8266 runs as TCP server
	const char ESP8266_PING[] = "+PING"; // Function PING

	//////////////////////////
	// Custom GPIO Commands //
	//////////////////////////
	const char ESP8266_PINMODE[] = "+PINMODE"; // Set GPIO mode (input/output)
	const char ESP8266_PINWRITE[] = "+PINWRITE"; // Write GPIO (high/low)
	const char ESP8266_PINREAD[] = "+PINREAD"; // Read GPIO digital value

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*ESP8266_CFG_H_ */