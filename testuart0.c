#include <watchdog.h>
#include <systick.h>
#include <uart0.h>
#include <stdint.h>

void main()
{
	uint8_t value;
	configure_systick();
	configure_watchdog();
	configure_uart0();
	while(1)
	{	
		if(!(systick_has_fired()))
		{
			continue;
		}	
		if(receive_data_from_uart0(&value))
		{
			send_data_to_uart0(value);
		}
		service_watchdog();
	}
}
