#include <watchdog.h>
#include <oldsystick.h>
#include <rgbled.h>
#include <i2c0_irq.h>
#include <stdint.h>
#include <uart0_txirq.h>
#include <uclib.h>

void main()
{
	//__disable_irq();
	configure_systick();
	configure_watchdog();
	configure_rgb_led();
	configure_i2c0();
	configure_uart0();
	//__enable_irq();
	
	uint8_t whoami = 0xA5;
	
	if(i2c0_read_bytes(0x1d, 0x0d, 1, &whoami))
		print_hex8(whoami);
	else 
		print_hex8(0x5a);
	i2c0_read_bytes(0x1d, 0x0d, 1, &whoami);
	//if(!i2c0_last_transaction_succeeded())
		print_hex8(whoami);
	uint32_t delay = 0;
	
	while(1)
	{	
		if(!systick_has_fired())
			continue;
		service_watchdog();
		delay++;
		if(delay == 1096)
			i2c0_write_byte(0x1d, 0x2a, 0x05);
		if(!(delay % 1024))
		{
			uint8_t xdata = 0x33;
			if(i2c0_read_bytes(0x1d, 0x01, 1, &xdata))
				print_hex8(xdata);
		}
	}
}
