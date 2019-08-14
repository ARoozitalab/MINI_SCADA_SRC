/*********************************************************************************************************
*
* File                : sample_Server.c
* Version             : V1.0
* modified            : alireza roozitalab (adding modbust tcp for scada)
* email               : alireza.roozitalab@gmail.com
* git user            : ARoozitalab
*                                                
*                                          All Rights Reserved
*
*********************************************************************************************************/

#include "net.h"
#include "ip_arp_udp_tcp.h"
#include "simple_server.h"
#include "stm32f10x_gpio.h"
#include "enc28j60.h"
#include "CONFIG.h"
#include "FreeRTOS.h"
#include "task.h"

extern uint16_t polldata[MAX_REG];



#define PSTR(s) s

//extern void delay_ms(u8 ms);

// please modify the following two lines. mac and ip have to be unique
// in your local area network. You can not have the same numbers in
// two devices:
u8 mymac[6] =
{
   0x54, 0x55, 0x58, 0x10, 0x00, 0x24
};
 u8 myip[4] =
{
   192, 168, 20, 37
};
// base url (you can put a DNS name instead of an IP addr. if you have
// a DNS server (baseurl must end in "/"):
static char baseurl[] = "http://192.168.0.100/";
 u16 mywwwport = 0xf6; // listen port for tcp/www (max range 1-254)
// or on a different port:
//static char baseurl[]="http://10.0.0.24:88/";
//static u16 mywwwport =88; // listen port for tcp/www (max range 1-254)
//
static u16 myudpport = 1200; // listen port for udp
// how did I get the mac addr? Translate the first 3 numbers into ascii is: TUX

#define BUFFER_SIZE 1500//400
static u8 buf[BUFFER_SIZE + 1];




int simple_server(void)
{
   u16 plen;
   u16 dat_p;
   u8 i = 0;
   u8 cmd_pos = 0;
   u8 cmd;
   u8 payloadlen = 0;
   char str[30];
   char cmdval;
 char buffer_S[30];
uint8_t poll2s=0;
	uint8_t regstart=0;

	char j=0;
   // Del_1ms(100);
   /*initialize enc28j60*/
   enc28j60Init(mymac);
   
   str[0]=(char)enc28j60getrev();
   
   init_ip_arp_udp_tcp(mymac, myip, mywwwport);

//   enc28j60PhyWrite(PHLCON, 0x7a4); 
   enc28j60PhyWrite(PHLCON, 0x476);
   enc28j60clkout(1); // change clkout from 6.25MHz to 12.5MHz
   // Del_1ms(20);

   //init the ethernet/ip layer:
   while (1)
   {
      //    OSTimeDlyHMSM(0, 0, 0, 50);
      // get the next new packet:
      plen = enc28j60PacketReceive(BUFFER_SIZE, buf);
      //USART_DMASendData(USART1,buf,plen);

      /*plen will ne unequal to zero if there is a valid packet (without crc error) */
      if (plen == 0)
      {
				 vTaskDelay(10);
         continue;
      }
		
				
      // arp is broadcast if unknown but a host may also
      // verify the mac address by sending it to 
      // a unicast address.
      if (eth_type_is_arp_and_my_ip(buf, plen))
      {
         make_arp_answer_from_request(buf);
				
         //USART_DMASendText(USART1,"make_arp_answer_from_request\n");
         continue;
      }

      // check if ip packets are for us:
      if (eth_type_is_ip_and_my_ip(buf, plen) == 0)
      {
         continue;
      }


      if (buf[IP_PROTO_P] == IP_PROTO_ICMP_V &&
         buf[ICMP_TYPE_P] == ICMP_TYPE_ECHOREQUEST_V)
      {
         // a ping packet, let's send pong	
         make_echo_reply_from_request(buf, plen);
         //USART_DMASendText(USART1,"make_echo_reply_from_request\n");
         continue;
      }
      // tcp port www start, compare only the lower byte
      if (buf[IP_PROTO_P] == IP_PROTO_TCP_V &&
         buf[TCP_DST_PORT_H_P] == 01 &&
         buf[TCP_DST_PORT_L_P] == mywwwport)
      {
         if (buf[TCP_FLAGS_P] & TCP_FLAGS_SYN_V)
         {
            make_tcp_synack_from_syn(buf);
            // make_tcp_synack_from_syn does already send the syn,ack
            continue;
         }
         if (buf[TCP_FLAGS_P] & TCP_FLAGS_ACK_V)
         {
            init_len_info(buf); // init some data structures
            // we can possibly have no data, just ack:
            dat_p = get_tcp_data_pointer();
            if (dat_p == 0)
            {
               if (buf[TCP_FLAGS_P] & TCP_FLAGS_FIN_V)
               {
                  // finack, answer with ack
                  make_tcp_ack_from_any(buf);
               }
               // just an ack with no data, wait for next packet
               continue;
            }
            if (buf[dat_p+6]>=0)
            {
							//read holding register
	             if (buf[dat_p+7] ==04)
								{
									regstart=buf[dat_p+9];
									poll2s=buf[dat_p+11];
									
									if((poll2s+regstart)>MAX_REG)
										poll2s=MAX_REG-regstart;
									
									
									buffer_S[0]=buf[dat_p];
									buffer_S[1]=buf[dat_p+1];
									buffer_S[2]=0;
									buffer_S[3]=0;
									//lengh
									buffer_S[4]=0;
									buffer_S[5]=(poll2s*2)+3;
									//id
									buffer_S[6]=buf[dat_p+6];
									//function
									buffer_S[7]=0x04;
									//data lenght
									buffer_S[8]=poll2s*2;
									//data
									for(j=0;j<=poll2s*2;j=j+2)
									{
									buffer_S[j+9]=((polldata[(j/2)+regstart]&0xff00)>>8);
									buffer_S[j+10]=polldata[(j/2)+regstart];
//										buffer_S[j+9]=0;
//										buffer_S[j+10]=1;
									}
									 plen = fill_tcp_data_p(buf, 0, buffer_S,buffer_S[8]+8);
									 goto SENDTCP;
								}
								
////////////////////////////////////////////////////////////////////////////
	             if (buf[dat_p+7] ==05)
								{

									regstart=buf[dat_p+9];
									if((regstart>0)&(regstart<=4))
									{
									regstart=regstart-1;
									if(buf[dat_p+10])
									polldata[10]=polldata[10]|(1<<regstart);
									else
									polldata[10]=polldata[10]&(~(1<<regstart));
									}
								for(j=0;j<12;j++)
										{
										buffer_S[j]=buf[dat_p+j];
										}						
	
										plen = fill_tcp_data_p(buf, 0, buffer_S,11);
									  goto SENDTCP;
								}			



	             if (buf[dat_p+7] ==01)
								{

								regstart=buf[dat_p+9];
									poll2s=buf[dat_p+11];
									
									if((poll2s+regstart)>18)
										poll2s=MAX_REG-regstart;
									
									
									buffer_S[0]=buf[dat_p];
									buffer_S[1]=buf[dat_p+1];
									buffer_S[2]=0;
									buffer_S[3]=0;
									//lengh
									buffer_S[4]=0;
									if(poll2s<=8)
									{
									buffer_S[5]=1+3;
										//data lenght
									buffer_S[8]=1;
									}
									else if(poll2s<=16)
									{
									buffer_S[5]=2+3;
										//data lenght
									buffer_S[8]=2;
									}
									else
									{
									buffer_S[5]=3+3;
									
									buffer_S[8]=2;	
										
									}
										
									//id
									buffer_S[6]=buf[dat_p+6];
									//function
									buffer_S[7]=0x01;
									//data lenght
									
									//data
									buffer_S[9]=0;
									buffer_S[10]=0;
									for(j=0;j<=poll2s+1;j++)
									{
										
									if(j<8)
									buffer_S[9]=buffer_S[9] |(((polldata[j])&(1<<j)));
									else
									buffer_S[10]=buffer_S[10] |(((polldata[j])&(1<<j)));
//									else if((j>=4)&(j<8))
//									buffer_S[9]=buffer_S[9]|(((polldata[8])&(1<<(j-4)))<<4);
//									else	if((j>=8) & (j<16))
//									buffer_S[10]=buffer_S[10]|(((polldata[8])&(1<<(j-4)))>>4);
//									else
//										buffer_S[11]=polldata[7];
									}
									 plen = fill_tcp_data_p(buf, 0, buffer_S,buffer_S[8]+8);
									 goto SENDTCP;
								}																
////////////////////////////////////////////////////////////////////////////							
								
						else if (buf[dat_p+7] ==03)
								{
									regstart=buf[dat_p+9];
									poll2s=buf[dat_p+11];
									
									if((poll2s+regstart)>MAX_REG)
										poll2s=MAX_REG-regstart;
									
									
									buffer_S[0]=buf[dat_p];
									buffer_S[1]=buf[dat_p+1];
									buffer_S[2]=0;
									buffer_S[3]=0;
									//lengh
									buffer_S[4]=0;
									buffer_S[5]=(poll2s*2)+3;
									//id
									buffer_S[6]=buf[dat_p+6];
									//function
									buffer_S[7]=0x03;
									//data lenght
									buffer_S[8]=poll2s*2;
									//data

									buffer_S[9]=0;
									buffer_S[10]=0x00;

									 plen = fill_tcp_data_p(buf, 0, buffer_S,buffer_S[8]+8);
									 goto SENDTCP;
								}							
								
								
								
								
								
								
/////////////////////////////////////////////////////////		
//Preset Single Register						
								else if (buf[dat_p+7] ==0x6)
								{


	              polldata[(buf[dat_p+9])]=((buf[dat_p+10]<<8)|(buf[dat_p+11]));







								for(j=0;j<12;j++)
										{
										buffer_S[j]=buf[dat_p+j];
										}						
										plen = fill_tcp_data_p(buf, 0, buffer_S,12);
									 goto SENDTCP;


								}									
								
///////////////////////////////////////////////////////////////////								
								
								//write multiple register
								else if (buf[dat_p+7] ==0x10)
								{
									if((buf[dat_p+9]<MAX_REG)&(buf[dat_p+9]>=MAXREG_RO))
									{
									polldata[(buf[dat_p+9])]=((buf[dat_p+13]<<8)|(buf[dat_p+14]));
										for(j=0;j<15;j++)
										{
										buffer_S[j]=buf[dat_p+j];
										}
									}
									plen = fill_tcp_data_p(buf, 0, buffer_S,14);
									goto SENDTCP;
								}						
								else
								{
										for(j=0;j<7;j++)
										{
										buffer_S[j]=buf[dat_p+j];
										}						
										buffer_S[5]=0;
										plen = fill_tcp_data_p(buf, 0, buffer_S,6);										
										
									
								}
            }
            

   SENDTCP : 
            make_tcp_ack_from_any(buf); // send ack for http get
            make_tcp_ack_with_data(buf, plen); // send data
            continue;
         }
      }

   }
   //        return (0);
}
