#include "LPC17xx.h"
#include <stdint.h>
#include "View.h"
#include "Main.h"

static int lines_since_powerup = 0;
static int lines_since_malus = 0;

volatile int slowdown_active = 0;
volatile int slowdown_timer = 0;

void clearBoard(void){
    for(int r=0; r< ROWS; r++)
        for(int c=0; c < COLS; c++)
            board[r][c] = 0;
}

void resetGame(void) {
    clearBoard();
    need_redraw = 1;
	
    score = 0;
    lines_cleared = 0;
	
    game_paused = 1;
    has_active_piece = 0;
	
    lines_since_powerup = 0;
    lines_since_malus = 0;
	
    slowdown_active = 0;
	
	  Clear();
}

void showNewPiece(void) {
    current_type = (int)(getRandom() % 7);
    current_rotation = 0;
    if(current_type == 0)
        current_x = 3;
    else
        current_x = 4;
    current_y = 0;

    has_active_piece = 1;
    
    if (checkCollision(current_x, current_y, current_rotation)) {
        game_paused = 1;
        has_active_piece = 0;

        if (score > high_score) 
            high_score = score;
        resetGame();
    }
    need_redraw = 1;
}

void updateDisplay(void) {
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
            display_grid[r][c] = board[r][c];

    if (!has_active_piece) return;

    const unsigned char* shape = shapes[current_type][current_rotation];
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (shape[r * 4 + c] == 1) {
                int ty = current_y + r;
                int tx = current_x + c;
                if (ty >= 0 && ty < ROWS && tx >= 0 && tx < COLS)
                    display_grid[ty][tx] = 1;
            }
        }
    }
}

int checkCollision(int nextX, int nextY, int nextRot) {
    const unsigned char* shapeGrid = shapes[current_type][nextRot];

    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (shapeGrid[r * 4 + c] == 1) {
                int boardX = nextX + c;
                int boardY = nextY + r;

                if (boardX < 0 || boardX >= COLS) 
                    return 1;
                if (boardY >= ROWS) 
                    return 1;
                if (boardY >= 0 && board[boardY][boardX] != 0) 
                    return 1;
            }
        }
    }
    return 0;
}

void processScoring(int lines_at_once) {
	  if(lines_at_once <= 0) return;
	
    int points = 0;
    if (lines_at_once == 1) 
        points += 100;
    else if (lines_at_once == 4) 
        points += 600;
    else if (lines_at_once > 1) 
        points += (100 * lines_at_once);
    score += points;
}

static void clearLine(int row_to_clear) {
    for (int r = row_to_clear; r > 0; r--) {
        for (int c = 0; c < COLS; c++)
            board[r][c] = board[r - 1][c];
    }
    for (int c = 0; c < COLS; c++)
        board[0][c] = 0;

    lines_cleared++;
    lines_since_powerup++;
    lines_since_malus++;
}


void spawnPowerup(void) {
    int block_count = 0;
	
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (board[r][c] == BLOCK)
                block_count++;
        }
    }
    
    if (block_count == 0) 
			return;
    
  
    int target = getRandom() % block_count;
    int current = 0;
    
   
    int powerup_type = (getRandom() % 2 == 0) ? PWR_CLR : PWR_SLOW;
    //int powerup_type = PWR_SLOW;
		//int powerup_type = PWR_CLR;
		
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (board[r][c] == BLOCK) {
                if (current == target) {
                    board[r][c] = powerup_type;
                    return;
                }
                current++;
            }
        }
    }
}


void activateClearHalf(void) {

    int start_row = ROWS / 2;   
    int cleared_lines = 0;


    for (int r = start_row; r < ROWS; r++) {
        int has_any = 0;
        for (int c = 0; c < COLS; c++) {
            if (board[r][c] != 0) {
                has_any = 1;
                break;
            }
        }
        if (has_any) 
					cleared_lines++;
    }


    if (cleared_lines == 0) 
			return;

    
    for (int r = start_row; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            board[r][c] = 0;
        }
    }

    
    lines_cleared        += cleared_lines;
    lines_since_powerup  += cleared_lines;
    lines_since_malus    += cleared_lines;

   
    int remaining = cleared_lines;
    while (remaining > 0) {
        int group = (remaining >= 4) ? 4 : remaining;
        processScoring(group);
        remaining -= group;
    }
}

void addMalusLine(void)
{
    for (int c = 0; c < COLS; c++) {
        if (board[0][c] != 0) {
            game_paused = 1;
            has_active_piece = 0;
            if (score > high_score) high_score = score;
            need_redraw = 1;
            return;
        }
    }

    for (int r = 0; r < ROWS - 1; r++) {
        for (int c = 0; c < COLS; c++)
            board[r][c] = board[r + 1][c];
    }

    for (int c = 0; c < COLS; c++)
        board[ROWS - 1][c] = 0;

   
    int cols[COLS];
    for (int i = 0; i < COLS; i++) 
			cols[i] = i;

    for (int i = COLS - 1; i > 0; i--) {
        int j = (int)(getRandom() % (uint32_t)(i + 1));
        int tmp = cols[i];
        cols[i] = cols[j];
        cols[j] = tmp;
    }

    for (int k = 0; k < 7; k++)
        board[ROWS - 1][cols[k]] = BLOCK;

    need_redraw = 1;
}


void activateSlowdown(void)
{
    slowdown_active = 1;
    slowdown_timer  = 1500;   // 15s * 100 ticks
    need_redraw = 1;
}

void checkLines(void)
{
    const unsigned char* shapeGrid = shapes[current_type][current_rotation];

    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (shapeGrid[r * 4 + c] == 1) {
                int by = current_y + r;
                int bx = current_x + c;
                if (by >= 0 && by < ROWS && bx >= 0 && bx < COLS)
                    board[by][bx] = BLOCK;
            }
        }
    }

    score += 10;

    int cleared_now = 0;
    int powerup_activated = 0;
    int powerup_type = 0;

    for (int r = ROWS - 1; r >= 0; r--) {
        while (1) {
            int full = 1;
            for (int c = 0; c < COLS; c++) {
                if (board[r][c] == 0) { full = 0; break; }
            }
            if (!full) 
							break;

            if (!powerup_activated) {
                for (int c = 0; c < COLS; c++) {
                    if (board[r][c] == PWR_CLR || board[r][c] == PWR_SLOW) {
                        powerup_activated = 1;
                        powerup_type = board[r][c];
                        break;
                    }
                }
            }

            clearLine(r);
            cleared_now++;
        }
    }

    if (cleared_now > 0)
        processScoring(cleared_now);

    if (powerup_activated) {
        if (powerup_type == PWR_CLR) 
					activateClearHalf();
        else if (powerup_type == PWR_SLOW) 
					activateSlowdown();
    }

    while (lines_since_powerup >= 5) {
        spawnPowerup();
        lines_since_powerup -= 5;
    }

    while (lines_since_malus >= 10) {
        addMalusLine();
        lines_since_malus -= 10;

        if (game_paused) {
            need_redraw = 1;
            return;
        }
    }

    showNewPiece();
    need_redraw = 1;
}

