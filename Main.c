#include "LPC17xx.h"
#include "Main.h"
#include <stdint.h>
#include "View.h"
#include "Game.h"

void randomSeed(uint32_t seed);
void resetGame(void);

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
volatile int score = 0, high_score = 0;
volatile int lines_cleared = 0;

volatile int current_x=0, current_y=0;
volatile int current_type=0, current_rotation=0;

volatile int game_paused = 1;
volatile int has_active_piece = 0;

volatile uint8_t need_redraw = 1;

volatile uint32_t LFSR_STATE = 0x1ACEB00C;

volatile int base_sps = 1;

int main(void)
{
    SystemInit();
	
    joystick_init();
    LCD_Initialization();
    BUTTON_init();	
	
    ADC_init();
    ADC_start_conversion();
	
    init_RIT(100000); //10ms 
    enable_RIT();
	
    TetrisView_Init();  
   // TetrisView_Render();
	
    uint32_t seed = 0x1ACEB30C;
    for (int i=0; i<200; i++) {
        seed ^= LPC_RIT->RICOUNTER + (seed << 5) + (seed >> 2);
    }
    randomSeed(seed);
		
    resetGame();
    score = 0;
    high_score = 0;
    lines_cleared = 0;
    need_redraw = 0;

    Update_Values();
		slowdown_active = 0;
		
    while (1) {
            
        uint16_t val;
				__disable_irq();			
			  val = ADC_current;
				__enable_irq(); 
			
				base_sps = 1 + ((val * 4) / 4095);
				
				if (base_sps < 1) base_sps = 1;
				if (base_sps > 5) base_sps = 5;
       
			
        if (need_redraw) {
            need_redraw = 0;
					
            __disable_irq();
            updateDisplay();        
            __enable_irq(); 
					
           	TetrisView_Redraw();			
        }		
				TetrisView_Render(); 				
    }
}