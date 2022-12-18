#include <watchdog.h>
#include <oldsystick.h>
#include <rgbled.h>
#include <TSI.h>

int value;
void led_colors();
void do_TSI();

void main()
{
	configure_systick();
	configure_watchdog();
	configure_rgb_led();
	configure_TSI();
	start_scan();
	
	while(1)
	{	if(!systick_has_fired())
			continue;
		service_watchdog();
		
		do_TSI();
	}
}

void led_colors()         // algorithm for changing colors based on Touch sensor 
{

                 if(determine_scan_complete())                                   // Checking scan satus

	                      {
				 set_rgbled_color_to( RGBLED_COLOR_WHITE);
			
			          value = extract_result();                      // Storing the sensor value
	
			                if((value>75) && (value<110))            // Comparing the value
				              {
						set_rgbled_color_to( RGBLED_COLOR_RED);
						
  				               }
					if((value>110) && (value<145))
				              {
						set_rgbled_color_to( RGBLED_COLOR_GREEN);
						
  				               }
					if((value>145) && (value<175))
				              {
						set_rgbled_color_to( RGBLED_COLOR_BLUE);
						
  				               }
					if((value>175) && (value<210))
				              {
						set_rgbled_color_to( RGBLED_COLOR_CYAN);
						
  				               }
					if((value>210) && (value<245))
				              {
						set_rgbled_color_to( RGBLED_COLOR_MAGENTA);
						
  				               }
					if(value>245)
				              {
						set_rgbled_color_to( RGBLED_COLOR_YELLOW);
						
  				               }					
				
			
	              start_scan();
 	               
		
         
		
               }
}

void do_TSI()
{
	static enum blink {base, active} blink = base;
	switch(blink)
	{
		default:
		case base:
			set_rgbled_color_to( RGBLED_COLOR_WHITE);
		break;
		
		case active:
			led_colors();
		break;
	
	}

}
