#include "LPC17xx.h"
#include <stdint.h>
#include "View.h"
#include "Main.h"


void resetGame(void) {
    clearBoard();
	  need_redraw = 1;
    score = 0;
    lines_cleared = 0;
    game_paused = 1;
    has_active_piece = 0;
}

void showNewPiece(void) {
    current_type = (int)getRandom();
    current_rotation = 0;
    current_x = 3;
    current_y = 0;

    has_active_piece = 1;
    
    if (checkCollision(current_x, current_y, current_rotation)) {
        game_paused = 1;
        has_active_piece = 0;

        if (score > high_score) 
					high_score = score;
        resetGame();
				TetrisView_Init();
    }
		need_redraw = 1;
		
}
void updateDisplay(void) {
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
            display_grid[r][c] = board[r][c];

    if (!has_active_piece) return;

    const unsigned char* shape = shapes[current_type][current_rotation];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shape[i * 4 + j] == 1) {
                int ty = current_y + i;
                int tx = current_x + j;
                if (ty >= 0 && ty < ROWS && tx >= 0 && tx < COLS)
                    display_grid[ty][tx] = 1;
            }
        }
    }
}
int checkCollision(int nextX, int nextY, int nextRot) {
    const unsigned char* shapeGrid = shapes[current_type][nextRot];

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (shapeGrid[row * 4 + col] == 1) {
                int boardX = nextX + col;
                int boardY = nextY + row;

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
    int points = 10;
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
}
void checkLines(void) {
    const unsigned char* shapeGrid = shapes[current_type][current_rotation];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shapeGrid[i * 4 + j] == 1) {
                int by = current_y + i;
                int bx = current_x + j;
                if (by >= 0 && by < ROWS && bx >= 0 && bx < COLS)
                    board[by][bx] = 1;
            }
        }
    }

    int cleared_now = 0;
    for (int r = ROWS - 1; r >= 0; r--) {
        int full = 1;
        for (int c = 0; c < COLS; c++) {
            if (board[r][c] == 0) { full = 0; break; }
        }
        if (full) {
            clearLine(r);
            cleared_now++;
            r++;
        }
    }
    processScoring(cleared_now);
    showNewPiece();
}




