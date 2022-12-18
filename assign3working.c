#include <watchdog.h>
#include <oldsystick.h>
#include <rgbled.h>
#include <sw1.h>
#include <stdint.h>
#include <uart0.h>
#define SECOND 150000
#define TIME 1000 // period for top

struct flashing_led_hzs
{
	uint16_t top;
	uint16_t onTime; // on_time uses top value as a parameter
	uint32_t pattern[9];
} flashing_led_hz;

void read_switch();
void task_flash(uint16_t top, uint16_t onTime, uint32_t pattern[9]);
void task_switch();
void config_mode();

static int color = RGBLED_COLOR_WHITE;
static int duty_cycle = 15;
static int time = 0;
static int time1 = 0;

static enum {FLASH_MODE, COLOR_MODE} mode = FLASH_MODE;
static enum {BUTTON_DOWN, BUTTON_RELEASED, BUTTON_UP, BUTTON_PRESSED} next_state = BUTTON_UP;
	

void main()
{
	configure_systick();
	configure_watchdog();
	configure_rgb_led();
	configure_sw1();
	configure_uart0();
	uint16_t top = 1;	
	uint16_t onTime = TIME / top;
	uint32_t pattern[9] = {RGBLED_COLOR_BLACK,
	RGBLED_COLOR_RED,
	RGBLED_COLOR_GREEN,
	RGBLED_COLOR_BLUE,
	RGBLED_COLOR_CYAN,
	RGBLED_COLOR_MAGENTA,
	RGBLED_COLOR_YELLOW,
	RGBLED_COLOR_WHITE}; 
	while(1)
	{	if(!systick_has_fired())
			continue;
		
		service_watchdog();
		
		void read_switch();
		// void task_flash(1, 1, 5); // 16 bit variables for top and on_time, and white led color set by default
		void task_switch();
		void config_mode();
	}
}

void read_switch()
{
	switch(next_state)
	{
		case BUTTON_DOWN:
			if(sw1_is_not_pressed())
			{
				next_state = BUTTON_RELEASED;
			}
			else 
			{
				next_state = BUTTON_DOWN;
			}
			time1++; // different timer
		break;
		case BUTTON_RELEASED:
			if(next_state == BUTTON_RELEASED)
			{
				next_state = BUTTON_UP;
			}
			time1 = 0;
		break;
		case BUTTON_UP:
			if(sw1_is_pressed())
			{
				next_state = BUTTON_PRESSED;
			}
			else
			{
				next_state = BUTTON_UP;
			}
		break;
		case BUTTON_PRESSED:
			if(next_state == BUTTON_PRESSED)
			{
				next_state = BUTTON_DOWN;
			}
			time1 = 0;
		break;
	}	
}

// function to flash led at duty cycle
void task_flash(uint16_t top, uint16_t onTime, uint32_t pattern[9])
{
	top = 1000 / top;
	onTime = onTime + 1;
	if(mode == FLASH_MODE)
	{
		time = (time + 1)% SECOND;
			if(time < duty_cycle*SECOND/16)
			{	if(top)
				{
					set_rgbled_color_to(color);
				}
				else
				{
					onTime = top;
				}
			}
			else
			{
				set_rgbled_color_to(RGBLED_COLOR_BLACK);
			} // button press to change duty cycle 
			if(next_state == BUTTON_PRESSED)
			{
				duty_cycle = (duty_cycle + 1)%16;
			}
	}

}

// switch color at freq of 2 Hz based off switch press 
// color select mode
void task_switch()
{
	if(mode == COLOR_MODE)
	{
		time = (time + 1)% SECOND;
		if(time < SECOND/2)
		{
			set_rgbled_color_to(color);
		}
		else
		{
			set_rgbled_color_to(RGBLED_COLOR_BLACK);
		}
		if(next_state == BUTTON_PRESSED)
		{
			color = ((color + 1) % 7) + 1; // change color? has to be at least 1
		}
	}
}

// fsm to change modes 
void config_mode() 
{
	switch(mode)
	{
		default:
		case FLASH_MODE: // condition to enter switch
		if(next_state == BUTTON_DOWN && time1>SECOND)
		{
			mode = COLOR_MODE;
		}
		break;
		
		case COLOR_MODE: // condition to enter flash
		if(next_state == BUTTON_UP && time1>5*SECOND)
		{
			mode = FLASH_MODE;
		}
		break;
	}
}
