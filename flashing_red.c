#include <redled.h>
//#include <greenled.h>
//#include <blueled.h>
//#include <uclib.h>
#include <watchdog.h>
#include <systick.h>

void main()
{
	unsigned cntr = 0;
	configure_systick();
	configure_watchdog();
	configure_red_led();
	while(1)
	{	if(!systick_has_fired())
			continue;
		cntr++;
		if(cntr == 500)
			cntr = 0;
		if(cntr == 0)
			toggle_redled();
		service_watchdog();
	}
}
