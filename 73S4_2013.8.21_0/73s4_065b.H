/*-----------------------
file name:73s4_065b.h
date:2013.8.5
revise date:2013.8.24
mcu:ht46r065b
-------------------------*/
//LED
#define led1 	_pa5 	
#define led2 	_pa4
#define cb1 	_pb0
#define cb2		_pb1

//led output status
#define LED_ALL_OFF	0xff
#define LED_OFF		1	//set port in
#define LED_ON 		0	//set port out

//led set status
#define LED_STATUS_STOP 		0//DISP_STOP
#define LED_STATUS_CHARGE		1//DISP_RED
#define LED_STATUS_FULL			2//DISP_stop
#define LED_STATUS_INVALID		3//DISP_RED_FLICKER

//switch status 
#define SW_ALL_OFF 0
#define SW_ON	1	//set port out
#define SW_OFF	0	//set port in
	
//set ad function
#define AN0	0b00111000
#define AN1	0b00111001
#define AN2 0b00111010
#define AN3 0b00111011

#define VB1	AN2	//vb1 电压检测
#define VB2	AN3  	
#define VT1 AN1	
#define VT2 AN0

const unsigned int adcAddr[]={
	VB1,VB2,VB1,VB2,VT1,VT2
};

//isr_time.................................
#define TIME_PSC0_2	7	//定时频率fint = fsys/128
#define TIME_TE		0	//上升沿有效
#define TIME_TON	1	//打开定时
#define TIME_TM0_1	2	//定时模式
#define TIME_TMRC	((TIME_PSC0_2)|(TIME_TE<<3)|(TIME_TON<<4)|(TIME_TM0_1<<6))	//0b10010111=0x97
/*
设置定时器中断，每秒128次,
K= fint/128=(fsys/128)/128=(4M/128)/128=0xf4,
TMR=256-K=0x100-0xf4=0x0c
若每分钟按64s计：k=(fint/128)*60/64=229=0xe5
TMR=0x100-0xe5=0x1b
*/
#define TIME_TMR	0x1b

//volt constant 
#define VB_PULLOUT  2267//1.55v
#define VB_FULL		2194//1.5v 
#define VB_NATURAL	1755//1.2v
#define VB_VALID	878	//0.6v
#define VB_INVALID	293	//0.2v
#define DELTA_V			6//4mv
#define DV_CHECK_VOLT	2048//1.4
#define VB_F0	2048//1.4v

#define VOT 	1567//60C
#define VOTR 	1747//55C

//time constant 
#define ONE_SECOND_COUNT 128	//2^7
#define ONE_SECOND_COUNT_MASK ONE_SECOND_COUNT-1

#define LED_FLICKER_COUNT	128	//1S
#define LED_FLICKER_COUNT_MASK LED_FLICKER_COUNT-1
#define LED_FLICKER_COUNT_END	42	//1/3S

#define PWM_CYCLE	64//0.5s
#define PWM_CYCLE_MASK PWM_CYCLE-1
#define PWM_PERCHARGE	32
#define PWM_RESUME 	16 
#define PWM_TRICKLE 4

#define PWM_CHARGE  55
#define ADC_TIME	62
	
#define VT_CHECK_TIME       128
#define VT_CHECK_TIME_MASK VT_CHECK_TIME-1

#define DV_CHECK_TIME       1024//128*8
#define DV_CHECK_TIME_MASK DV_CHECK_TIME-1

#define DV_CHECK_DELAY	900//15min=15*60=900s /delta V check delay 

#define ACTIVE_TIME	20	//20s
#define RESUME_TIME 180	//3min=3*60=180
#define TIME_CHARGE	360	//6h5=6*60=360

#define DV_COUNT 20
#define DV0_COUNT 100

	