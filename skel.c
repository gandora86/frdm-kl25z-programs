#include <watchdog.h>
#include <oldsystick.h>
#include <redled.h>

void main()
{
	configure_systick();
	configure_watchdog();
	//drivers
	while(1)
	{	if(!systick_has_fired())
			continue;
		// body
		service_watchdog();
	}
}
