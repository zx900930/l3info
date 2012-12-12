#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/tty.h>
#include<linux/kd.h>
#include<linux/vt_kern.h>
#include<linux/timer.h>

#define ALL_LEDS_ON 0x07
#define ALL_LEDS_OFF 0x00
#define RESTORE_LEDS 0xFF
#define BLANK_DELAY (HZ/5)

struct timer_list alarme;

void clignote(unsigned long p){
	int *s = (int *)p;
	if(*s == ALL_LEDS_ON) *s = ALL_LEDS_OFF;
	else *s = ALL_LEDS_ON;
	
	my_driver->ops->ioctl(vc_cons[fg_console].d->vc_tty, NULL, KDSETLED, *s);
	alarme.expires = jiffies + BLANK_DELAY;
	add_timer (&alarme);
}

int init_module(){

	init_timer(&alarme);
	alarme.function = clignote;
	alarme.expires=jiffies + BLANK_DELAY;
	add_timer (&alarme);
	
	return 0;
}
