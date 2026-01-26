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
extern volatile int current_x, current_y;
extern volatile int current_type, current_rotation;

extern volatile int game_paused;
extern volatile int has_active_piece;

extern volatile uint8_t need_redraw;

extern volatile int base_sps;
extern volatile uint16_t ADC_current;

extern volatile int slowdown_active;
extern volatile int slowdown_timer;

extern unsigned char board[ROWS][COLS];
extern unsigned char display_grid[ROWS][COLS];
extern const unsigned char* shapes[7][4];


/* Functions */
extern int checkCollision(int next_x, int next_y, int next_rot);
extern void updateDisplay(void);
extern void checkLines(void);

extern uint32_t getRandom(void);
extern void randomSeed(uint32_t seed);
extern volatile uint32_t LFSR_STATE;