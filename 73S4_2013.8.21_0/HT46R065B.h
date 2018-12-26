//
//Holtek C header file.
//File name: HT46R065B.H
//

#ifndef _HOLTEK_H_
#define _HOLTEK_H_
unsigned char _iar0	@0x00;
unsigned char _iar1	@0x02;
unsigned char _mp0	 @0x01;
unsigned char _mp1	 @0x03;
unsigned char _acc	 @0x05;
unsigned char _pcl	 @0x06;
unsigned char _tblp	 @0x07;
unsigned char _tblh	 @0x08;
unsigned char _wdts	 @0x09;
#define _ws0	 _09_0
#define _ws1	 _09_1
#define _ws2	 _09_2
unsigned char _status	 @0x0a;
#define _c	 _0a_0
#define _ac	 _0a_1
#define _z	 _0a_2
#define _ov	 _0a_3
#define _pdf	 _0a_4
#define _to	 _0a_5
unsigned char _intc0	 @0x0b;
#define _emi	 _0b_0
#define _inte	 _0b_1
#define _t0e	 _0b_2
#define _t1e	 _0b_3
#define _intf	 _0b_4
#define _t0f	 _0b_5
#define _t1f	 _0b_6
unsigned char _tmr0	 @0x0c;
unsigned char _tmr0c	 @0x0d;
#define _t0psc0	 _0d_0
#define _t0psc1	 _0d_1
#define _t0psc2	 _0d_2
#define _t0eg	 _0d_3
#define _t0on	 _0d_4
#define _t0s	 _0d_5
#define _t0m0	 _0d_6
#define _t0m1	 _0d_7
unsigned char _tmr1	 @0x0e;
unsigned char _tmr1c	 @0x0f;
#define _t1eg	 _0f_3
#define _t1on	 _0f_4
#define _t1s	 _0f_5
#define _t1m0	 _0f_6
#define _t1m1	 _0f_7
unsigned char _pa	 @0x10;
#define _pa0	 _10_0
#define _pa1	 _10_1
#define _pa2	 _10_2
#define _pa3	 _10_3
#define _pa4	 _10_4
#define _pa5	 _10_5
#define _pa6	 _10_6
#define _pa7	 _10_7
unsigned char _pac	 @0x11;
#define _pac0	 _11_0
#define _pac1	 _11_1
#define _pac2	 _11_2
#define _pac3	 _11_3
#define _pac4	 _11_4
#define _pac5	 _11_5
#define _pac6	 _11_6
#define _pac7	 _11_7
unsigned char _papu	 @0x12;
#define _papu0	 _12_0
#define _papu1	 _12_1
#define _papu2	 _12_2
#define _papu3	 _12_3
#define _papu4	 _12_4
#define _papu5	 _12_5
#define _papu6	 _12_6
unsigned char _pawk	 @0x13;
#define _pawk0	 _13_0
#define _pawk1	 _13_1
#define _pawk2	 _13_2
#define _pawk3	 _13_3
#define _pawk4	 _13_4
#define _pawk5	 _13_5
#define _pawk6	 _13_6
#define _pawk7	 _13_7
unsigned char _pb	 @0x14;
#define _pb0	 _14_0
#define _pb1	 _14_1
#define _pb2	 _14_2
#define _pb3	 _14_3
#define _pb4	 _14_4
#define _pb5	 _14_5
unsigned char _pbc	 @0x15;
#define _pbc0	 _15_0
#define _pbc1	 _15_1
#define _pbc2	 _15_2
#define _pbc3	 _15_3
#define _pbc4	 _15_4
#define _pbc5	 _15_5
unsigned char _pbpu	 @0x16;
#define _pbpu0	 _16_0
#define _pbpu1	 _16_1
#define _pbpu2	 _16_2
#define _pbpu3	 _16_3
#define _pbpu4	 _16_4
#define _pbpu5	 _16_5
unsigned char _pc	 @0x17;
#define _pc0	 _17_0
#define _pc1	 _17_1
#define _pc2	 _17_2
#define _pc3	 _17_3
#define _pc4	 _17_4
#define _pc5	 _17_5
#define _pc6	 _17_6
#define _pc7	 _17_7
unsigned char _pcc	 @0x18;
#define _pcc0	 _18_0
#define _pcc1	 _18_1
#define _pcc2	 _18_2
#define _pcc3	 _18_3
#define _pcc4	 _18_4
#define _pcc5	 _18_5
#define _pcc6	 _18_6
#define _pcc7	 _18_7
unsigned char _pcpu	 @0x19;
#define _pcpu0	 _19_0
#define _pcpu1	 _19_1
#define _pcpu2	 _19_2
#define _pcpu3	 _19_3
#define _pcpu4	 _19_4
#define _pcpu5	 _19_5
#define _pcpu6	 _19_6
#define _pcpu7	 _19_7
unsigned char _ctrl0	 @0x1a;
#define _clkmod	 _1a_0
#define _lxtlp	 _1a_1
#define _pfdc	 _1a_2
#define _pwmc0	 _1a_3
#define _pwmsel	 _1a_5
#define _pfdcs	 _1a_6
unsigned char _ctrl1	 @0x1b;
#define _wdten0	 _1b_0
#define _wdten1	 _1b_1
#define _wdten2	 _1b_2
#define _wdten3	 _1b_3
#define _tbsel0	 _1b_4
#define _tbsel1	 _1b_5
#define _integ0	 _1b_6
#define _integ1	 _1b_7
unsigned char _scomc	 @0x1c;
#define _com0en	 _1c_0
#define _com1en	 _1c_1
#define _com2en	 _1c_2
#define _com3en	 _1c_3
#define _scomen	 _1c_4
#define _isel0	 _1c_5
#define _isel1	 _1c_6
unsigned char _intc1	 @0x1e;
#define _ade	 _1e_0
#define _tbe	 _1e_1
#define _adf	 _1e_4
#define _tbf	 _1e_5
unsigned char _pwm0	 @0x1f;
unsigned char _adrl	 @0x20;
unsigned char _adrh	 @0x21;
unsigned char _adcr	 @0x22;
#define _acs0	 _22_0
#define _acs1	 _22_1
#define _acs2	 _22_2
#define _pcr0	 _22_3
#define _pcr1	 _22_4
#define _pcr2	 _22_5
#define _eocb	 _22_6
#define _start	 _22_7
unsigned char _acsr	 @0x23;
#define _adcs0	 _23_0
#define _adcs1	 _23_1
#define _adcs2	 _23_2
#define _adonb	 _23_6
#define _test	 _23_7
#endif
