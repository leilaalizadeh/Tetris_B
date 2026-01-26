#include "LPC17xx.h"
#include "RIT.h"
#include <stdint.h>
#include "../Main.h"
#include "../View.h"
#include "../Game.h"

static uint8_t prev_left  = 1;
static uint8_t prev_right = 1;
static uint8_t prev_up    = 1;

extern volatile int base_sps;
extern volatile int slowdown_active;
//static int slowdown_timer = 1500;

static int move_counter = 0;

void RIT_IRQHandler(void)
{
	  int change = 0;
	
    if(slowdown_active && game_paused == 0) {
				slowdown_timer--;
				if (slowdown_timer <= 0) {
						slowdown_active = 0;
						slowdown_timer = 0;
						need_redraw = 1;
				}
    }
		
    if (game_paused == 0 && has_active_piece == 1) {

        uint8_t down_now = ((LPC_GPIO1->FIOPIN & (1 << 26)) == 0) ? 1 : 0;
        
        int effective_sps = slowdown_active ? 1 : base_sps;
			
        if (slowdown_active) {
            effective_sps = 1;
        }
				
        if (effective_sps < 1) 
					effective_sps = 1;
        if (effective_sps > 5) 
					effective_sps = 5;
        
        int fall_threshold = 100 / effective_sps;
        if (fall_threshold < 1) 
					fall_threshold = 1;
			
        if (down_now) {
            fall_threshold = fall_threshold / 2; 
            if (fall_threshold < 1) 
                fall_threshold = 1;
        }
      
        move_counter++;
        
        if (move_counter >= fall_threshold) {
            move_counter = 0;

            if (checkCollision(current_x, current_y + 1, current_rotation) == 0) {
                current_y++;
							  change =1;
            } else {
                checkLines();
							  change =1;
            }
            
          
        }

        uint8_t left_now  = ((LPC_GPIO1->FIOPIN & (1 << 27)) == 0) ? 0 : 1;
        uint8_t right_now = ((LPC_GPIO1->FIOPIN & (1 << 28)) == 0) ? 0 : 1;
        uint8_t up_now    = ((LPC_GPIO1->FIOPIN & (1 << 29)) == 0) ? 0 : 1;

        if (prev_left == 1 && left_now == 0) {
            if (checkCollision(current_x - 1, current_y, current_rotation) == 0) {
                current_x--;
							  change =1;
            }
        }

        if (prev_right == 1 && right_now == 0) {
            if (checkCollision(current_x + 1, current_y, current_rotation) == 0) {
                current_x++;
							  change =1;
            }
        }

        if (prev_up == 1 && up_now == 0) {
            int nextRot = (current_rotation + 1) % 4;
            if (checkCollision(current_x, current_y, nextRot) == 0) {
                current_rotation = nextRot;
							  change =1;
            }
        }

        prev_left  = left_now;
        prev_right = right_now;
        prev_up    = up_now;
				
				if(change == 1)
					need_redraw = 1;
    }

    LPC_RIT->RICTRL |= 0x1;     // Clear interrupt flag
}