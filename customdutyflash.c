#include <watchdog.h>
#include <systick.h>
#include <redled.h>
#include <stdint.h>

void flash_red_led_1Hz(uint16_t);
void main()
{
	configure_systick();
	configure_watchdog();
	configure_red_led();
	while(1)
	{	if(!systick_has_fired())
			continue;
		flash_red_led_1Hz(10);
		service_watchdog();
	}
}
void flash_red_led_1Hz(uint16_t duty) // led on takes 0, led off takes 1
{
	static enum {LED_ON, LED_OFF} state = LED_ON;
	static uint16_t cntr = 0;
	switch(state)
	{
		default:
		case LED_ON:
			if(cntr < duty)
			{
				cntr++;
			}	
			else 
			{
				state = LED_OFF;
				turn_off_red_led();
			}
		break;
		case LED_OFF:
			if(cntr < 999)
			{	
				cntr++;
			}
			else
			{
				state = LED_ON;
				turn_on_red_led();
				cntr = 0;
			}
		break;
	}
}
