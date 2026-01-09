#include "LPC17xx.h"
#include "Main.h"
#include <stdint.h>
#include "View.h"

#define ROWS 20
#define COLS 10

void randomSeed(uint32_t seed);
void resetGame(void);

volatile int score, high_score, lines_cleared;
volatile uint8_t need_redraw;
volatile uint8_t rit_tick;

/* Shapes from assembly */
extern const unsigned char I_0, I_1, I_2, I_3;
extern const unsigned char O_0, O_1, O_2, O_3;
extern const unsigned char T_0, T_1, T_2, T_3;
extern const unsigned char L_0, L_1, L_2, L_3;
extern const unsigned char J_0, J_1, J_2, J_3;
extern const unsigned char S_0, S_1, S_2, S_3;
extern const unsigned char Z_0, Z_1, Z_2, Z_3;

unsigned char board[ROWS][COLS] = {0};
unsigned char display_grid[ROWS][COLS] = {0};

const unsigned char* shapes[7][4] = {
    {&I_0, &I_1, &I_2, &I_3},
    {&O_0, &O_1, &O_2, &O_3},
    {&T_0, &T_1, &T_2, &T_3},
    {&L_0, &L_1, &L_2, &L_3},
    {&J_0, &J_1, &J_2, &J_3},
    {&S_0, &S_1, &S_2, &S_3},
    {&Z_0, &Z_1, &Z_2, &Z_3}
};

/* Global Variables */
volatile int current_x, current_y;
volatile int current_type, current_rotation;
volatile int score = 0, high_score = 0;
volatile int lines_cleared = 0;
volatile int game_paused = 1;
volatile int has_active_piece = 0;
volatile uint8_t need_redraw = 1;
volatile uint32_t LFSR_STATE = 0x1ACEB00C;

int main(void)
{
    SystemInit();
	
    joystick_init();
    LCD_Initialization();
     
//		init_timer_SRI(3,25000,0b011);			//1ms delay
//		enable_timer(3);
	
    BUTTON_init();	
	
	  init_RIT(1000000);
    enable_RIT();
	
    TetrisView_Init();  
    //updateDisplay();
    TetrisView_Redraw();  
	
    uint32_t seed = 0x12345678;
		for (int i=0; i<200; i++) {
			seed ^= LPC_RIT->RICOUNTER + (seed << 5) + (seed >> 2);
		}
		randomSeed(seed);
		
		resetGame();
    score = 0;
		high_score =0;
		lines_cleared = 0;
		
    while (1) {
			
			if (need_redraw) {
					need_redraw = 0;
					__disable_irq();
					updateDisplay();        
           __enable_irq();
					TetrisView_Redraw(); 
					TetrisView_Render(); 				
			}
			else
				__WFI();				
    }
}
