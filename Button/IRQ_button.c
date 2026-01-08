#include "LPC17xx.h"
#include "../View.h"
#include "../Main.h"
#define debounce_time 50
extern uint32_t tick;

//key0
uint32_t last_tick0 = 0;
int state0 = 1;
//key1
uint32_t last_tick1 = 0;
int state1 = 1;
//key2
uint32_t last_tick2 = 0;
int state2 = 1;



void random_seed(uint32_t seed);


void EINT0_IRQHandler(void)  
{
//		if(tick<debounce_time && state0==1){
//   		state0=0;
// 		  last_tick0 = tick;
//			
//			 resetGame();
//       need_redraw = 1;
//			
//  		LPC_SC->EXTINT = (1 << 0); /* clear pending interrupt         */
//  		return;
//   	}
//  	if ((tick - last_tick0) < debounce_time) {	
//         LPC_SC->EXTINT = (1 << 0); /* clear pending interrupt         */
//        return;
//   	}
//   	last_tick0 = tick;
//  	state0=1;
		
//    resetGame();
//    need_redraw = 1;
	
    LPC_SC->EXTINT = (1 << 0); 
}

void EINT1_IRQHandler(void)  
{
//	  if(tick<debounce_time && state1==1){
//   		state1=0;
// 		  last_tick1 = tick;
//			
//			if (has_active_piece == 0){
//        showNewPiece();
//				clearBoard();
//				game_paused = 1;
//				need_redraw = 1;
//			}
//	
//			game_paused = !game_paused;
//		
//			need_redraw = 1;  
//		
//  		LPC_SC->EXTINT = (1 << 1); /* clear pending interrupt         */
//  		return;
//   	}
//  	if ((tick - last_tick1) < debounce_time) {	
//         LPC_SC->EXTINT = (1 << 1); /* clear pending interrupt         */
//        return;
//   	}
//   	last_tick1 = tick;
//  	state1=1;
	
    if (has_active_piece == 0){
        showNewPiece();
				clearBoard();
				game_paused = 1;
				need_redraw = 1;
		}
	
    game_paused = !game_paused;
		
		need_redraw = 1;
		
    LPC_SC->EXTINT = (1 << 1);  
	  
}

void EINT2_IRQHandler(void)
{
	
//		if(tick<debounce_time && state2==1){
//   		state2=0;
// 		  last_tick2 = tick;
//			
//			if (game_paused == 0 && has_active_piece == 1) {
//        while (checkCollision(current_x, current_y + 1, current_rotation) == 0) {
//            current_y++;
//        }
//        checkLines();
//				need_redraw = 1;
//      }
//				 
//  		LPC_SC->EXTINT = (1 << 2); /* clear pending interrupt         */
//  		return;
//   	}
//  	if ((tick - last_tick0) < debounce_time) {	
//         LPC_SC->EXTINT = (1 << 2); /* clear pending interrupt         */
//        return;
//   	}
//   	last_tick2 = tick;
//  	state2=1;
		
		
    if (game_paused == 0 && has_active_piece == 1) {
        while (checkCollision(current_x, current_y + 1, current_rotation) == 0) {
            current_y++;
        }
        checkLines();
				need_redraw = 1;
    }

    LPC_SC->EXTINT = (1 << 2);
  
}
