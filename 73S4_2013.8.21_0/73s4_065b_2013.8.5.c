/*
------------------------------
program name:  73s4_065b_2013.8.5.c
program date:  2013.8.5
revise date：2013.8.21
mcu:ht46r065b

function:
-------------------------------
	VDD =2800mv
  	mv/bit	= VDD/4096
			=0.684mv/bit 

 Mask Option:
 SysVolt	3.000V
 SysFreq	4.000MHz
 PA7/RESB   PA7
 HIRC frequency 4M
 OSC	RC
 LVR	enable 2.1v
 WDT clock source		WDTOSC(12KHz)
 WDT		Enable
 CLRWDT		1 clear instruction		

*/ 
#include <ht46r065b.h>
#include "73s4_065b.h"
#pragma vector isr_timer128	@ 0x08

unsigned int c2 @0x40;
#define c2_0  	_40_0	//flicker	
#define c2_1  	_40_1	//on-off control: 0=on, 1=off	


unsigned int c4 @0x41;
#define c4_0	_41_0	//pwm out according to bat status
#define c4_1	_41_1	//resume 
#define c4_2	_41_2	//trickle
#define c4_3	_41_3	//percharge
#define c4_4	_41_4	//on-off


unsigned int bit_use @0x42;
#define adc_command    	_42_0//vb. adc
#define adc_tag			_42_1
#define dv_check_command    _42_2//vb check
#define dv_check_tag		_42_3



unsigned int bit_use1 @0x43;


unsigned int bit_tag[2];
#define timer_start		0b10000000//bit7

#define ot_tag			0b00010000//bit4
#define ot_tag_mask		0b11101111

#define dv0_tag			0b00001000//bit3
#define dv_tag			0b00000100//bit2
#define vbf_tag			0b00000010//bit1
#define timer_end		0b00000001//bit0


unsigned long int intCount;
unsigned long int batSecond[2];//charge timer
unsigned int ledStatus[2];

unsigned long int adc_value;
unsigned long int vb[2];
unsigned int c_slot;//vb check slot

unsigned long int vt[2];
unsigned long int vt_sum[2];
unsigned int vt_adc_count[2];

unsigned long int vb_max[2];
unsigned int vbf_count[2];//bat. volt. full checked count
unsigned int dv_tag_count[2];
unsigned int vmax_renew_count[2];
unsigned int dv0_tag_count[2];

unsigned int dv_slot;//delta v check slot
unsigned int c1;
unsigned int i;


//led initial
void ledInitial()
{
		
		led1=LED_ON;
		led2=LED_ON;
		
		for(i=0;i<200;i++)
			{
				_clrwdt();
				_delay(5000);
			}
			
		led1=LED_OFF;
		led2=LED_OFF;

		for(i=0;i<200;i++)
			{
				_clrwdt();
				_delay(5000);
			}						
}
void resetBatValue()						
	{	
		_clrwdt();			
		vb[i]=VB_PULLOUT;									
		ledStatus[i]=LED_STATUS_STOP;
		batSecond[i]=0;	
		bit_tag[i]=0;
		
		vb_max[i]=0;
		vmax_renew_count[i]=0;						
		dv_tag_count[i]=0;
		dv0_tag_count[i]=0;
		vbf_count[i]=0;
		
		vt[i]=2926;//25C
		vt_sum[i]=0;
		vt_adc_count[i]=0;	
							
	}

void initial()
{	
	//porta
	_pa	=0x00;
	_pac =0x0f;	//pa0-3 set as in，others set as out	               
	//portb
	_pb=0;
	_pbc =0x00;	//pb set as out
	//portc
	_pc=0;
	_pcc =0;	
	//set ad clock 
	_acsr=0x01;	//设fad=fsys/8

//定时中断设置
	_tmr0= TIME_TMR;
	_tmr0c=TIME_TMRC;
	_intc0=0x00;			//禁止所有中断		
}//end initial
void init_var()
{

	for(i=0;i<2;i++)				
		resetBatValue();				
	ledInitial();		
	bit_use	=0;	
	bit_use1=0;
	
    c_slot=0;
    dv_slot=0;
			
}

//中断服务子程序.......................
void isr_timer128()		
{
	intCount++;
//charge timer	
	if((intCount & ONE_SECOND_COUNT_MASK)==0)
		{
			for(c1=0;c1<2;c1++)
			{
				//if timer_start=1 and timer_end=0 
				if((bit_tag[c1] & 0x81)==0x80)
					batSecond[c1]++;														
			}
		}

//vb check command
	if((intCount & DV_CHECK_TIME_MASK)==0)
		dv_check_command=1;
		else
			{
				dv_check_command=0;
				dv_check_tag=0;	
			} 
			
//adc command
	if((intCount & PWM_CYCLE_MASK)==ADC_TIME)
		adc_command=1;
		else
			{
				adc_command=0;
				adc_tag=0;	
			}
		
			
	//led disp flicker
	c2=LED_ALL_OFF;
	if((intCount & LED_FLICKER_COUNT_MASK)<LED_FLICKER_COUNT_END)
		c2_0 = LED_ON;
	//current pwm
	c4=SW_ALL_OFF;
	if((intCount & PWM_CYCLE_MASK)<PWM_RESUME)
		c4_1 = SW_ON;
	if((intCount & PWM_CYCLE_MASK)<PWM_TRICKLE)
		c4_2 = SW_ON;
	if((intCount & PWM_CYCLE_MASK)<PWM_PERCHARGE)
		c4_3 = SW_ON;
	//switch status
	if((intCount & PWM_CYCLE_MASK)<PWM_CHARGE)
		c4_4 = SW_ON;				


//led disp & charge
	for(c1=0;c1<2;c1++)
	{
		_clrwdt();
		//led disp.
		switch(ledStatus[c1])
			{
				case LED_STATUS_STOP://off
				case LED_STATUS_FULL:		
					c2_1=LED_OFF;
					break;			
				case LED_STATUS_CHARGE://disp. red				
					c2_1=LED_ON;
					break;
				case LED_STATUS_INVALID://disp. red flicker
					c2_1=c2_0;
					break;			
				default:;
					break;
			}
		//charge
		if((bit_tag[c1] & ot_tag)!=0)
			c4_0=SW_OFF;
			else
				{
					if(ledStatus[c1]==LED_STATUS_CHARGE)
						{																																	
							if(vb[c1]<VB_VALID)
								c4_0=c4_1;//resume	
								else if(vb[c1]<VB_NATURAL)
									c4_0=c4_3;//percharge
									else c4_0=c4_4;//SW_ON									
																																			
						}
						else if(ledStatus[c1]==LED_STATUS_FULL)
							c4_0=c4_2;//trickle
							else c4_0=SW_OFF;
													
					if((batSecond[c1]>=(ACTIVE_TIME-8))&(batSecond[c1]<=ACTIVE_TIME))
						c4_0=SW_OFF;	
				}				
		switch(c1)
			{
				case 0:
				{
					led1=c2_1;
					cb1=c4_0;	
				}break;	
				case 1:
				{
					led2=c2_1;
					cb2=c4_0;					
				}break;		
				default:;
					break;							
			}		
		
	}

		
}//end isr

//bat status check 
void batStatusCheck()
	{
		if((vb[i]>=VB_PULLOUT))
			ledStatus[i]=LED_STATUS_STOP;
			else if(batSecond[i]<=ACTIVE_TIME)//bat wackup 20s
				{
					ledStatus[i]=LED_STATUS_CHARGE;
					if(batSecond[i]==(ACTIVE_TIME-1))
						{
							if(vb[i]>=VB_F0)
								bit_tag[i] |= vbf_tag;										
						}
				}
				else if((bit_tag[i] & 0x0f)!=0)	
					ledStatus[i]=LED_STATUS_FULL;					
					else if(vb[i]>VB_VALID)	
						ledStatus[i]=LED_STATUS_CHARGE;	
						else if(vb[i]<VB_INVALID)	
							ledStatus[i]=LED_STATUS_INVALID;					
							else 
								{
									if(batSecond[i]<RESUME_TIME)
										ledStatus[i]=LED_STATUS_CHARGE;
										else ledStatus[i]=LED_STATUS_INVALID;		
								}			
														
			
	}


//bat.full check
void vbf_check()
{																									
	if((bit_tag[i] & vbf_tag)==0)
		{
			if(vb[i]>=VB_FULL)								
				vbf_count[i]++;
				else 
					{
						if(vbf_count[i]<=5)
							vbf_count[i]=0;
							else vbf_count[i]-=5;	
					}					
			if(vbf_count[i]>=20)
				bit_tag[i] |= vbf_tag;
		}
																														
}


//delta v check 
void dv_check()
{
	if(((batSecond[i])>DV_CHECK_DELAY)|(vb[i]>DV_CHECK_VOLT))		
		{
			if((bit_tag[i] & 0x1f)==0)//if bat not full
				{																																							
					//vb_max check
					if(vb_max[i]<vb[i])
						{
							vmax_renew_count[i]++;
							if(vmax_renew_count[i]>=10)
								{
									vb_max[i]=vb[i];
									//dv_tag_count clear
									dv_tag_count[i]=0;
									//dv0_tag_count clear
									dv0_tag_count[i]=0;
								}											
						}
						else
							{
								//vmax_renew_count reset
								if(vmax_renew_count[i]>5)
									vmax_renew_count[i]-=5;
									else vmax_renew_count[i]=0;												
								//zero delta v check
								dv0_tag_count[i]++;
								if(dv0_tag_count[i]>=DV0_COUNT)//need 100 times to confirm 0dv
									bit_tag[i] |= dv0_tag;				
																						
								//minus delta v check
								if((vb_max[i]-vb[i])>=DELTA_V)
									{
										dv_tag_count[i]++;
										if(dv_tag_count[i]>=DV_COUNT)//need 20 times to confirm -dv
											bit_tag[i] |= dv_tag;					
									}
									else//delta_tag_count reset 
										{
											if(dv_tag_count[i]>5)
												dv_tag_count[i] -=5;
												else dv_tag_count[i]=0;
										}
													
							}		
																
																	
				}
				
		}		
										
}//end delta v check
	
void main()
{
	_clrwdt();
	initial();
	init_var();
	_emi=1;		
	_t0e=1;
	while(1)
	{		
		_clrwdt();		
		if((adc_command)&(adc_tag==0))// 0.5s/per time
			{
				adc_tag=1;
				//adc																														
				_adcr=adcAddr[c_slot];
				_delay(50);
				_start=0;
				_start=1;
				_start=0;					
				while(_eocb)
					_clrwdt();						
				adc_value= (((_adrl>>4) & 0x0f)|((unsigned long)_adrh<<4));
				//vb 
				if(c_slot<=3)
					{
						if((c_slot & 0x01)==0)
							i=0;
							else i=1;
						vb[i]=adc_value;
					}
					//vt 
					else if(c_slot<=5)
						{
							if((c_slot & 0x01)==0)
								i=0;
								else i=1;
							vt_adc_count[i]++;						
							vt_sum[i] +=adc_value;
							if(vt_adc_count[i]>=16)
								{
									vt[i]=(vt_sum[i]>>4);
									vt_sum[i]=0;
									vt_adc_count[i]=0;
									//vt judge  64s/per timr
									if(vt[i]<=VOT)
										bit_tag[i] |= ot_tag;
									if(vt[i]>VOTR)
										bit_tag[i] &= ot_tag_mask;
													
								}						
														
												
						}
													
				c_slot++;
				if(c_slot>5)
					c_slot=0;
				_adcr=adcAddr[c_slot];//switch AD channel in advance
				
				//timer check
				if(vb[i]<VB_PULLOUT)
					{
						bit_tag[i] |=timer_start;																															
						if((batSecond[i]>>6)>=TIME_CHARGE)	
							bit_tag[i] |=timer_end;
					
					}			
					else resetBatValue();			
				//bat status check
				batStatusCheck();																
			}						
		if((dv_check_command)&(dv_check_tag==0))
			{
				dv_check_tag=1;
				//slot in turn
				dv_slot++;
				if(dv_slot>1)
					dv_slot=0;					
				i=dv_slot;				
				dv_check();
				vbf_check();				
			}
							
	}		



}
