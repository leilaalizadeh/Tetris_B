#include "LPC17xx.h"
#include "Timer/timer.h"
#include "Button/button.h"
#include "LED/led.h"
#include "joystick/joystick.h"
#include "RIT/RIT.h"
#include "ADC/adc.h"
#include "GLCD/GLCD.h"
#include "TouchPanel/TouchPanel.h"
#include "DAC/DAC.h"
#include <stdio.h>
#include "View.h"
#include "Game.h"

#define ROWS 20
#define COLS 10

/* Global Variables */
extern volatile int score, high_score, lines_cleared;
extern volatile uint8_t need_redraw;
extern volatile uint8_t rit_tick;
extern unsigned char board[ROWS][COLS];
extern unsigned char display_grid[ROWS][COLS];
extern const unsigned char* shapes[7][4];
extern volatile uint8_t need_redraw;
extern volatile int current_x, current_y;
extern volatile int current_type, current_rotation;
extern volatile int score, high_score;
extern volatile int lines_cleared;
extern volatile int game_paused;
extern volatile int has_active_piece;
extern volatile uint8_t need_redraw;

/* Asembly */
extern const unsigned char I_0, I_1, I_2, I_3;
extern const unsigned char O_0, O_1, O_2, O_3;
extern const unsigned char T_0, T_1, T_2, T_3;
extern const unsigned char L_0, L_1, L_2, L_3;
extern const unsigned char J_0, J_1, J_2, J_3;
extern const unsigned char S_0, S_1, S_2, S_3;
extern const unsigned char Z_0, Z_1, Z_2, Z_3;

extern int checkCollision(int next_x, int next_y, int next_rot);
extern void updateDisplay(void);
extern int clearBoard(void);
extern uint32_t getRandom();
extern volatile uint32_t LFSR_STATE;