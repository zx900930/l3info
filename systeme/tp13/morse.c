#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/tty.h>
#include<linux/kd.h>
#include<linux/vt_kern.h>
#include<linux/timer.h>

#define ALL_LEDS_ON 0x07
#define ALL_LEDS_OFF 0x00
#define RESTORE_LEDS 0xFF

struct tty_driver * my_driver;

int init_module(){

	my_driver = vc_cons[fg_console].d->vc_tty->driver;
	(my_driver->ops->ioctl)(vc_cons[fg_console].d->vc_tty, NULL, KDSETLED, ALL_LEDS_ON);

	return 0;
}

void cleanup_module(){
	my_driver = vc_cons[fg_console].d->vc_tty->driver;
	(my_driver->ops->ioctl)(vc_cons[fg_console].d->vc_tty, NULL, KDSETLED, RESTORE_LEDS);

}
