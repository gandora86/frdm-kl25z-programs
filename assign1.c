/* Program to randomly cycle through colors of rgbled with rand() function and srand() entropy
assignment 1 by Ashfaq Khan * /
#include <redled.h>
#include <greenled.h>
#include <blueled.h>
#include <uclib.h>
#include <stdint.h>

void main()
{	
	uint32_t p = 0;
	configure_red_led();
	configure_green_led();
	configure_blue_led();
	srand(0xabcd123); //call srand  
	p = rand();
	
	while(1)
	{
		// green
		if (p < 100)
		{
		turn_on_green_led();
		turn_off_red_led();
		turn_off_blue_led();
		delay(1020000);
		p = 100;
		}
		// blue
		else if((p >= 100) & (p <= 500))
		{
		turn_on_blue_led();
		turn_off_red_led();
		turn_off_green_led();
		delay(1020000);
		p = 550;
		}
		//red
		else if((p > 500) & (p <= 1000) )
		{
		turn_off_blue_led();
		turn_on_red_led();
		turn_off_green_led();
		delay(1020000);
		p = 1500;
		}
		//cyan
		else if((p > 1000) & (p <= 2000))
		{
		turn_on_blue_led();
		turn_off_red_led();
		turn_on_green_led();
		delay(1020000);
		p = 2500;
		}
		// magenta
		else if((p > 2000) & (p <= 3000))
		{
		turn_on_blue_led();
		turn_on_red_led();
		turn_off_green_led();
		delay(1020000);
		p = 3500;
		}
		//yellow
		else if((p > 3000) & (p <= 4000))
		{
		turn_off_blue_led();
		turn_on_red_led();
		turn_on_green_led();
		delay(1020000);
		p = 4500;
		}
		// black
		else if((p > 4000) & (p <= 5000))
		{
		turn_off_blue_led();
		turn_off_red_led();
		turn_off_green_led();
		delay(1020000);
		p = 5500;
		}
		// white
		else if(p >= 5500)
		{
		turn_on_blue_led();
		turn_on_red_led();
		turn_on_green_led();
		delay(1020000);
		p = 0;
		}
	}
}
