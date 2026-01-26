extern void resetGame(void);
extern void showNewPiece(void);
extern void processScoring(int lines_at_once);

#define EMPTY    0
#define BLOCK    1
#define PWR_CLR  2   // clear half 
#define PWR_SLOW 3   // slow down 