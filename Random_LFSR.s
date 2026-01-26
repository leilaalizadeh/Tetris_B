VAL     RN 0
STAT    RN 1
TMP     RN 2
TMP1    RN 3

        AREA RANDOM_CODE, CODE, READONLY
			
        EXPORT getRandom
        EXPORT randomSeed
			
        IMPORT LFSR_STATE

randomSeed PROC
        CMP     VAL, #0
        BNE     SEED
        LDR     VAL, =0x1ACEB00C
SEED
        LDR     STAT, =LFSR_STATE
        STR     VAL, [STAT]
        BX      LR
        ENDP

getRandom PROC
RETRY
        LDR     STAT, =LFSR_STATE
        LDR     VAL, [STAT]          

        ANDS    TMP, VAL, #1       
        LSRS    VAL, VAL, #1        

        CMP     TMP, #0
        BEQ     NO_XOR
        LDR     TMP1, =0x80200003
        EORS    VAL, VAL, TMP1
NO_XOR
        STR     VAL, [STAT]          
        BX      LR
        ENDP

        END
