#include "LPC17xx.h"
#include <stdint.h>
#include "GLCD/GLCD.h" 
#include "Main.h"

static unsigned char snap[ROWS][COLS];
static unsigned char snap2[ROWS][COLS];
/* ---- Layout ---- */
#define CELL      10      
#define FIELD_X   20
#define FIELD_Y   20
#define FIELD_W   (COLS * CELL)
#define FIELD_H   (ROWS * CELL)

/* HUD position */
#define HUD_X    140
#define HUD_Y     20
#define HUD_DY    15

static unsigned char prev_grid[ROWS][COLS];
static volatile uint8_t lcd_dirty = 1;
static int prev_paused = -1;

extern void LCD_FillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

static void Draw_Cell(int r, int c, unsigned char v) {
    uint16_t x = (uint16_t)(FIELD_X + c * CELL);
    uint16_t y = (uint16_t)(FIELD_Y + r * CELL);
    LCD_FillRect(x, y, CELL, CELL, (v==1) ? White : Black);
}


static void Draw_Field_Border(void) {
  uint16_t x0 = FIELD_X - 1;
  uint16_t y0 = FIELD_Y - 1;
  uint16_t x1 = FIELD_X + FIELD_W;
  uint16_t y1 = FIELD_Y + FIELD_H;

  LCD_DrawLine(x0, y0, x1, y0, Yell);
  LCD_DrawLine(x0, y1, x1, y1, Yell);
  LCD_DrawLine(x0, y0, x0, y1, Yell);
  LCD_DrawLine(x1, y0, x1, y1, Yell);
}


static void u32_to_str(uint32_t v, uint8_t *out) {
  uint8_t tmp[11];
  int i = 0, j = 0;

  if (v == 0) { out[0] = '0'; out[1] = 0; return; }

  while (v > 0 && i < 10) {
    tmp[i++] = (uint8_t)('0' + (v % 10));
    v /= 10;
  }
  while (i > 0) out[j++] = tmp[--i];
  out[j] = 0;
}

void TetrisView_Init(void) {
  LCD_Clear(Black);
  Draw_Field_Border();

  for (int r = 0; r < ROWS; r++)
    for (int c = 0; c < COLS; c++)
      prev_grid[r][c] = 0;   

  lcd_dirty = 1;
  prev_paused = -1;

  GUI_Text(HUD_X, HUD_Y + 0*HUD_DY, (uint8_t*)"SCORE:", White, Black);
  GUI_Text(HUD_X, HUD_Y + 1*HUD_DY, (uint8_t*)"HIGH :", White, Black);
  GUI_Text(HUD_X, HUD_Y + 2*HUD_DY, (uint8_t*)"LINES:", White, Black);
}

void TetrisView_Redraw(void) {
  lcd_dirty = 1;
}
void clear(void){	
	  for (int r = 0; r < ROWS; r++)
    for (int c = 0; c < COLS; c++)
      snap[r][c] = 0;
}
void TetrisView_Render(void) {
	 if (!lcd_dirty) return;
		lcd_dirty = 0;
	
	
  __disable_irq();
  for (int r = 0; r < ROWS; r++)
    for (int c = 0; c < COLS; c++)
			snap[r][c] = (display_grid[r][c] !=0) ? 1: 0;
  __enable_irq();  
			
  for (int r = 0; r < ROWS; r++) {
    for (int c = 0; c < COLS; c++) {
      unsigned char cur = display_grid[r][c];
			if(cur == 1 || cur == 0){
        if (cur != prev_grid[r][c]) {
					Draw_Cell(r, c, cur);
					prev_grid[r][c] = cur;
				}
      }
    }
  }

	uint8_t buf[12];

	u32_to_str((uint32_t)score, buf);
	GUI_Text((uint16_t)(HUD_X + 50), HUD_Y + 0*HUD_DY, (uint8_t*)"        ", White, Black);
	GUI_Text((uint16_t)(HUD_X + 50), HUD_Y + 0*HUD_DY, buf, White, Black);

	u32_to_str((uint32_t)high_score, buf);
	GUI_Text((uint16_t)(HUD_X + 50), HUD_Y + 1*HUD_DY, (uint8_t*)"        ", White, Black);
	GUI_Text((uint16_t)(HUD_X + 50), HUD_Y + 1*HUD_DY, buf, White, Black);

	u32_to_str((uint32_t)lines_cleared, buf);
	GUI_Text((uint16_t)(HUD_X + 50), HUD_Y + 2*HUD_DY, (uint8_t*)"        ", White, Black);
	GUI_Text((uint16_t)(HUD_X + 50), HUD_Y + 2*HUD_DY, buf, White, Black);

  if (prev_paused != (int)game_paused) {
    prev_paused = (int)game_paused;
    GUI_Text(HUD_X, HUD_Y + 3*HUD_DY, (uint8_t*)"        ", White, Black);
    GUI_Text(HUD_X, HUD_Y + 3*HUD_DY, (uint8_t*)(game_paused ? "PAUSED " : "PLAYING"),White, Black);
  }
	
}
