#include <watchdog.h>
#include <systick.h>
#include <rgbled.h>
#include <sw1.h>
#include <uart0.h>
#include <stdint.h>
#define SECOND 150000
#define TIME 1000

struct flashing_led_hzs
{
	uint16_t top;
	uint16_t onTime; // on_time uses top value as a parameter
	uint32_t pattern[9];
} flashing_led_hz;	


void read_switch();
void task_flash(uint16_t freq);

static int color = RGBLED_COLOR_WHITE;
static int top = 1;
static int time = 0;
static int time1 = 0;
	

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
		void task_flash(100, pattern[9]); // 100 hz
	}
}

void read_switch() // fsm
{
	static enum {BUTTON_DOWN, BUTTON_RELEASED, BUTTON_UP, BUTTON_PRESSED} next_state = BUTTON_UP;
	
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

// function to flash led at period top
void task_flash(uint16_t freq)
{
	if(on_time)
	{
		top = TIME / freq;
			if(time < top*SECOND/16)
			{
				//set_rgbled_color_to(color);
				set_rgbled_color_to(pattern[9]); // set color one of ten colors array values 0 through 9
			}
			else
			{
				set_rgbled_color_to(RGBLED_COLOR_BLACK);
			} 
			if(next_state == BUTTON_PRESSED)
			{
				on_time = top;
				top = 1; // reset top
			}
	}
}
