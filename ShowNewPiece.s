RNGMAX          RN 0        ; argument to random_next_range
RET             RN 0        ; return from functions (r0)

TMP             RN 1
TMP1            RN 2
SCOREVAL        RN 3
HSV             RN 4

        AREA    ShowNewPiece, CODE, READONLY
        THUMB
        EXPORT  show_new_piece

        IMPORT  random_next_range

        ; IMPORTANT: change this to your real exported name:
        ;   if your collision func is "check_collision" -> IMPORT/BL check_collision
        ;   if it's "checkCollision" -> IMPORT/BL checkCollision
        IMPORT  checkCollision

        IMPORT  reset_game_to_empty_paused

        IMPORT  current_type
        IMPORT  current_rotation
        IMPORT  current_x
        IMPORT  current_y

        IMPORT  has_active_piece
        IMPORT  game_paused
        IMPORT  need_redraw

        IMPORT  score
        IMPORT  high_score

;------------------------------------------------------------
; void show_new_piece(void)
;------------------------------------------------------------
show_new_piece    PROC
        PUSH    {R4-R7,LR}

        ; current_type = random_next_range(7)
        MOVS    RNGMAX, #7
        BL      random_next_range
        LDR     TMP, =current_type
        STR     RET, [TMP]

        ; current_rotation = 0
        LDR     TMP, =current_rotation
        MOVS    RET, #0
        STR     RET, [TMP]

        ; current_x = 3
        LDR     TMP, =current_x
        MOVS    RET, #3
        STR     RET, [TMP]

        ; current_y = 0
        LDR     TMP, =current_y
        MOVS    RET, #0
        STR     RET, [TMP]

        ; has_active_piece = 1
        LDR     TMP, =has_active_piece
        MOVS    RET, #1
        STR     RET, [TMP]

        ; if (checkCollision(current_x, current_y, current_rotation)) { ... }
        LDR     RET, =current_x
        LDR     RET, [RET]              ; r0 = current_x
        LDR     TMP, =current_y
        LDR     TMP, [TMP]              ; r1 = current_y
        LDR     TMP1, =current_rotation
        LDR     TMP1, [TMP1]            ; r2 = current_rotation
        BL      checkCollision
        CMP     RET, #0
        BEQ     ok_spawn

        ; game_paused = 1
        LDR     TMP, =game_paused
        MOVS    RET, #1
        STR     RET, [TMP]

        ; has_active_piece = 0
        LDR     TMP, =has_active_piece
        MOVS    RET, #0
        STR     RET, [TMP]

        ; if (score > high_score) high_score = score;
        LDR     TMP, =score
        LDR     SCOREVAL, [TMP]         ; score
        LDR     TMP1, =high_score
        LDR     HSV, [TMP1]             ; high_score
        CMP     SCOREVAL, HSV
        BLE     no_hs_update
        STR     SCOREVAL, [TMP1]
no_hs_update

        ; reset_game_to_empty_paused();
        BL      reset_game_to_empty_paused

ok_spawn
        ; need_redraw = 1
        LDR     TMP, =need_redraw
        MOVS    RET, #1
        STRB    RET, [TMP]              ; ??? need_redraw int ??? -> STR

        POP     {R4-R7,LR}
        BX      LR
        ENDP

        END
