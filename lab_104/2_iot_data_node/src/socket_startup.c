/*
 * socket_startup.c
 *
 * initialise the wifi module and connect to the specified access point
 * using the supplied credentials
 *
 * author:    Dr. Alex Shenfield
 * date:      17/11/2020
 * purpose:   55-604481 embedded computer networks - lab 104
 */

// include functions from the standard c libraries
#include <stdint.h>
#include <string.h>
#include <stdio.h>

// include the ARM CMSIS-Driver WiFi driver
#include "Driver_WiFi.h"

// include the header file with the WiFi credentials in
#include "my_credentials.h"

// the wifi driver is defined and created elsewhere, but we'll use it here
extern ARM_DRIVER_WIFI Driver_WiFi0;

// WIFI INITIALISATION CODE

// start up the wifi connection
int32_t socket_startup(void)
{
  // wifi configuration structure
  ARM_WIFI_CONFIG_t wifi_config;

  // print a status message
  printf("connecting to WiFi ...\r\n");

  // initialise the wifi driver
  Driver_WiFi0.Initialize(NULL);
  Driver_WiFi0.PowerControl(ARM_POWER_FULL);

  // zero the wifi configuration structure and set it up with the supplied
  // values
  memset((void *)&wifi_config, 0, sizeof(wifi_config));
  wifi_config.ssid     = SSID;
  wifi_config.pass     = PASSWORD;
  wifi_config.security = SECURITY_TYPE;
  wifi_config.ch       = 0U;

  // activate the wifi driver and connect to the specified access point
  // using the supplied credentials
  Driver_WiFi0.Activate(0U, &wifi_config);

  // check whether we connected ok and display an appropriate status message
  if(Driver_WiFi0.IsConnected() == 0U)
  {
    printf("WiFi network connection failed!\r\n");
    return (-1);
  }
  else
  {
    printf("WiFi network connection succeeded!\r\n");
  }

  // get the ip address assigned to the embedded board via dhcp and print
  // it as a status message
  uint8_t ip[4];
  Driver_WiFi0.GetOption(0U, ARM_WIFI_IP, &ip, (uint32_t *)sizeof(ip));
  printf("IP = %d.%d.%d.%d\r\n", ip[0], ip[1], ip[2], ip[3]);

  // return success
  return 0;
}
