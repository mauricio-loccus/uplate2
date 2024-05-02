/*
*********************************************************************************************************
*
*	模块名称 : web server 演示
*	文件名称 : http_server.c
*	版    本 : V1.0
*	说    明 : 提供WEB服务器功能。主要目的是测试DM9000AEP网卡电路和DM9161 PHY电路。
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2013-01-01 armfly  正式发布
*
*	Copyright (C), 2012-2013, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/

#include "stdio.h"
#include "uip.h"
#include "uip_arp.h"
#include "tapdev.h"
#include "timer.h"
#include "dm9k_uip.h"
//#include "bsp.h"
//#include "num_pad.h"
#include "param.h"

/* for LwIP */
//#include "stm32f4x7_eth.h"
//#include "netconf.h"
//#include "main_lwip.h"
#include "httpd_w.h"
#include "stm32f4x7_eth_bsp.h"

struct timer periodic_timer, arp_timer;
#define BUF ((struct uip_eth_hdr *)&uip_buf[0])


/*
*********************************************************************************************************
*	函 数 名: uip_start
*	功能说明: 启动uip， 网络参数存在在全局变量 g_tParam.uip_ip, g_tParam.uip_net_mask, 
*			  g_tParam.uip_gateway 
*	形    参: 无
*	返 回 值: 无
*******************************************************************************************************
*/
void uip_start(void)
{
	timer_set(&periodic_timer, CLOCK_SECOND / 2);
	timer_set(&arp_timer, CLOCK_SECOND * 10);

	tapdev_init();	/* 初始化网卡硬件 */
	uip_init();

	//uip_ipaddr(ipaddr, 192,168,1,10);	/* 缺省IP */
	uip_sethostaddr((uint16_t *)g_tParam.uip_ip);

	//uip_ipaddr(ipaddr, 255,255,255,0);	/* 地址掩码 */
	uip_setnetmask((uint16_t *)g_tParam.uip_net_mask);

	//uip_ipaddr(ipaddr, 192,168,1,1);	/* 默认网关 */
	uip_setdraddr((uint16_t *)g_tParam.uip_gateway);

	httpd_init();
}

/*
*********************************************************************************************************
*	函 数 名: uip_pro
*	功能说明: uip 轮询，插入到主循环中
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void uip_pro(void)
{
	uint16_t i;

	uip_len = tapdev_read();
	if(uip_len > 0)
	{
		if (BUF->type == htons(UIP_ETHTYPE_IP))
		{
			uip_arp_ipin();
			uip_input();
			/* If the above function invocation resulted in data that
			should be sent out on the network, the global variable
			uip_len is set to a value > 0. */
			if (uip_len > 0)
			{
				uip_arp_out();
				tapdev_send();
			}
		}
		else if (BUF->type == htons(UIP_ETHTYPE_ARP))
		{
			uip_arp_arpin();
			/* If the above function invocation resulted in data that
			should be sent out on the network, the global variable
			uip_len is set to a value > 0. */
			if (uip_len > 0)
			{
				tapdev_send();
			}
		}
	}
	else if(timer_expired(&periodic_timer))
	{
		//printf("  0.5s periodic timer expired\n\r");
		timer_reset(&periodic_timer);
		for(i = 0; i < UIP_CONNS; i++)
		{
			uip_periodic(i);
			/* If the above function invocation resulted in data that
			should be sent out on the network, the global variable
			uip_len is set to a value > 0. */
			if(uip_len > 0)
			{
				uip_arp_out();
				tapdev_send();
			}
		}

		#if UIP_UDP
		for(i = 0; i < UIP_UDP_CONNS; i++)
		{
			uip_udp_periodic(i);
			/* If the above function invocation resulted in data that
			should be sent out on the network, the global variable
			uip_len is set to a value > 0. */
			if(uip_len > 0)
			{
				uip_arp_out();
				tapdev_send();
			}
		}
		#endif /* UIP_UDP */

		/* Call the ARP timer function every 10 seconds. */
		if (timer_expired(&arp_timer))
		{
			//printf("  10s periodic timer expired\n\r");
			timer_reset(&arp_timer);
			uip_arp_timer();
		}
	}
}

/*---------------------------------------------------------------------------*/
void uip_log(char *m)
{
	printf("uIP log message: %s\n", m);
}

void resolv_found(char *name, u16_t *ipaddr)
{
	//  u16_t *ipaddr2;

	if (ipaddr == NULL)
	{
		printf("Host '%s' not found.\n", name);
	}
	else
	{
		printf("Found name '%s' = %d.%d.%d.%d\n", name,
		htons(ipaddr[0]) >> 8,
		htons(ipaddr[0]) & 0xff,
		htons(ipaddr[1]) >> 8,
		htons(ipaddr[1]) & 0xff);
		/*    webclient_get("www.sics.se", 80, "/~adam/uip");*/
	}
}

#ifdef __DHCPC_H__
	void dhcpc_configured(const struct dhcpc_state *s)
	{
		uip_sethostaddr(s->ipaddr);
		uip_setnetmask(s->netmask);
		uip_setdraddr(s->default_router);
		resolv_conf(s->dnsaddr);
	}
#endif /* __DHCPC_H__ */