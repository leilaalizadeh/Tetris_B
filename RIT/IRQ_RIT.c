#include "LPC17xx.h"
#include "RIT.h"
#include <stdint.h>
#include "../Main.h"

#define FALL_NORMAL 60  // 100 * 10ms = 1s
#define FALL_FAST   30  //  50 * 10ms  = 0.5s

static int move_counter = 0;
static int fall_threshold = FALL_NORMAL;

static uint8_t prev_left  = 1;
static uint8_t prev_right = 1;
static uint8_t prev_up    = 1;


void RIT_IRQHandler(void)
{
    if (game_paused == 0 && has_active_piece == 1) {
        uint8_t down_now = ((LPC_GPIO1->FIOPIN & (1 << 26)) == 0) ? 1 : 0;
		   	int fall_threshold = down_now ? FALL_FAST: FALL_NORMAL;
			
//        int new_threshold = (down_now == 0) ? FALL_FAST : FALL_NORMAL;
//        if (new_threshold !=fall_threshold){
//					fall_threshold = new_threshold;
//					if(move_counter > fall_threshold) move_counter = fall_threshold;
//						move_counter = fall_threshold;
//				}
			
        move_counter++;
        if (move_counter >= fall_threshold) {
            move_counter = 0;

            if (checkCollision(current_x, current_y + 1, current_rotation) == 0)
                current_y++;
            else
                checkLines();
        }

        uint8_t left_now  = ((LPC_GPIO1->FIOPIN & (1 << 27)) == 0) ? 0 : 1;
        uint8_t right_now = ((LPC_GPIO1->FIOPIN & (1 << 28)) == 0) ? 0 : 1;
        uint8_t up_now    = ((LPC_GPIO1->FIOPIN & (1 << 29)) == 0) ? 0 : 1;

        if (prev_left == 1 && left_now == 0)
            if (checkCollision(current_x - 1, current_y, current_rotation) == 0)
                current_x--;

        if (prev_right == 1 && right_now == 0)
            if (checkCollision(current_x + 1, current_y, current_rotation) == 0)
                current_x++;

        if (prev_up == 1 && up_now == 0) {
            int nextRot = (current_rotation + 1) % 4;
            if (checkCollision(current_x, current_y, nextRot) == 0)
                current_rotation = nextRot;
        }

        prev_left  = left_now;
        prev_right = right_now;
        prev_up    = up_now;
				
				need_redraw = 1;
    }

    LPC_RIT->RICTRL |= 0x1;     // clear interrupt flag
}
