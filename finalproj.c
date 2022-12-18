/*
 "Implementation of Testing code(Chnage of led colors based on sensing pressure) for Tousch sensor interface , Created by Ashfaq Khan*/

//#include <MKL25Z4.h>
#include "rgbled.h"
//#include "TSI.h"
//#include "watchdog.h"
//#include "oldsystick.h"
//#include <stdint.h>

//int value;

void led_colors();
	 
 void main()
{
//	__disable_irq();
        configure_rgb_led();
    //    configure_TSI();
//	start_scan();
//	configure_watchdog();
//	configure_SysTick();
	__enable_irq();
	
        
          while(1){
                     __WFI();        // Using interrupt
 		    //if(g_flag)
			//{

			//feed_cop_service();
			led_colors();
			
         	    //   }
		     
	}

 }


void led_colors()         // algoritham for changing colors based on Touch sensor 
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
