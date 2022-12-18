#include <watchdog.h>
#include <systick.h>
#include <rgbled.h>
#include <sw1.h>
#include <uart0_txirq.h>
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
_Bool print_str(char* printer);

static int color = RGBLED_COLOR_WHITE;
static int top = 1;
static int time = 0;
static int time1 = 0;
uint16_t onTime;
char printbuff[512];
static enum {BUTTON_DOWN, BUTTON_RELEASED, BUTTON_UP, BUTTON_PRESSED} next_state = BUTTON_UP;

void main()
{
	configure_systick();
	configure_watchdog();
	configure_rgb_led();
	configure_sw1();
	configure_uart0();
	uint16_t top = 0x2001;	
	uint16_t onTime = 0x1000;
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
		
		read_switch(); 
		task_flash(100); // 100 hz
		UART0_IRQHandler();
		send_data_to_uart0(top);
		send_data_to_uart0(onTime);
		send_data_to_uart0(0010275411);
		receive_data_from_uart0(printbuff[512]);
	}
}

void read_switch() // fsm
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

// function to flash led at period top
void task_flash(uint16_t freq)
{
	if(onTime)
	{
		top = TIME / freq;
			if(time < top*SECOND/16)
			{
				set_rgbled_color_to(color); // set color one of ten colors array values 0 through 9
			}
			else
			{
				set_rgbled_color_to(RGBLED_COLOR_BLACK);
			} 
			if(next_state == BUTTON_PRESSED)
			{
				onTime = top;
				top = 1; // reset top
			}
	}
}
