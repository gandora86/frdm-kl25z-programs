#include <watchdog.h>
#include <oldsystick.h>
#include <rgbled.h>
#include <i2c0_irq.h>
#include <stdint.h>
#include <oldsystick.h>
#include <uart0_txirq.h>
#include <uclib.h>

#define MMA_ADDR 0x3A //Accel. device address


#define REG_XLO 0x02
#define REG_WHOAMI 0x0D //Accel read address
#define REG_CTRL1  0x2A

#define WHOAMI 0x1A

void main()
{
	configure_systick();
	configure_watchdog();
	configure_rgb_led();
	configure_i2c0();
	uint8_t regdata;
	
	uint8_t accel_data[3] = {0,0,0};
	
	while(1)
	{	if(!systick_has_fired())
			continue;
		
		service_watchdog();
		
		
		
		
		print_str("accelerometer register WHOAMI contains ");
		i2c0_read_bytes(MMA_ADDR,REG_WHOAMI,1,&regdata);
		print_hex8(regdata);
		print_str("\n");
		print_str("accelerometer register REG_XLO contains ");
		i2c0_read_bytes(MMA_ADDR,REG_XLO,1,&regdata);
		print_hex8(regdata);
		print_str("\n");
		print_str("accelerometer register REG_CTRL1 contains ");
		i2c0_read_bytes(MMA_ADDR,REG_CTRL1,1,&regdata);
		print_hex8(regdata);
		print_str(" Before Write\n");
		regdata=0
		i2c0_write_byte(MMA_ADDR,REG_CTRL1,regdata);
		print_str("accelerometer register REG_CTRL1 contains ");
		i2c0_read_bytes(MMA_ADDR,REG_CTRL1,1,&regdata);
		print_hex8(regdata);
		print_str(" After Write\n");		
	}
}
