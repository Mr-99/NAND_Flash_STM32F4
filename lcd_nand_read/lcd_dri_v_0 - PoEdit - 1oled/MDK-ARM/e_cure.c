#include "e_cure.h"
void mode_1(void);
void mode_2(void);
void mode_3(void);
void mode_4(void);
void mode_5(void);
void mode_6(void);
void mode_7(void);
void mode_8(void);
//(void)(*ele_mode)(void);这种声明不合法(void)相当于强制转换
void (*mode[8])(void) = {mode_1,mode_2,mode_3,mode_4,mode_5,mode_6,mode_7,mode_8};
void plus_unit(void)
{
pwm_init(100);
delay_ms(500);
pwm_stop();
delay_ms(500);
}
void mode_1(void)
{
plus_unit();
}
void mode_2(void)
{
plus_unit();
plus_unit();
}
void mode_3(void)
{
plus_unit();
plus_unit();
plus_unit();
}
void mode_4(void)
{
plus_unit();
plus_unit();
plus_unit();
plus_unit();
}
void mode_5(void)
{
  plus_unit();
	plus_unit();
	plus_unit();
	plus_unit();
	plus_unit();
}
void mode_6(void)
{
  plus_unit();
	plus_unit();
	plus_unit();
	plus_unit();
	plus_unit();
	plus_unit();
}
void mode_7(void)
{

}
void mode_8(void)
{

}
//调用第几个
void e_mode_num(uint8_t n)
{
if(n>=8)
{
return;
}
mode[n]();
}