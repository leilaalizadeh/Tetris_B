CNT     RN 0
CNT1    RN 1
TMP     RN 2
ROW		RN 3
COL		RN 4
BOARD	RN 5
TMP1    RN 6
		AREA    ClearBoardEmpty, CODE, READONLY
        EXPORT  clearBoard1
        IMPORT  board 			

clearBoard1     PROC
        PUSH    {R4-R8,LR}                
        LDR 	TMP,=0             

        LDR		ROW,=20             ; ROWS = 20
        LDR     COL,=10             ; COLS = 10

        LDR     CNT,=0              
ROW_LOOP
        CMP     CNT, ROW            
        BGE     ROW_END            
		
        LDR     CNT1,=0              

COLUMN_LOOP
        CMP     CNT1,COL            
        BGE     COLUMN_END       
        LDR     BOARD, =board    
	    MUL     TMP1,CNT,COL        ; 0 * 10,
		ADD     TMP1,CNT1           ; 0 * 10 + 0, 0 * 10 + 1
        STR     TMP, [BOARD,TMP1]   
        ADD     CNT1, CNT1, #1       
        B       COLUMN_LOOP       

COLUMN_END
        ADD     CNT, CNT, #1         
        B       ROW_LOOP           

ROW_END
        POP     {R4-R8,PC}              
        BX      LR                 
                ENDP
		END