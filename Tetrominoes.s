        AREA Tetrominoes, DATA, READONLY

        EXPORT I_0
        EXPORT I_1
        EXPORT I_2
        EXPORT I_3

        EXPORT O_0
        EXPORT O_1
        EXPORT O_2
        EXPORT O_3

        EXPORT T_0
        EXPORT T_1
        EXPORT T_2
        EXPORT T_3

        EXPORT L_0
        EXPORT L_1
        EXPORT L_2
        EXPORT L_3

        EXPORT J_0
        EXPORT J_1
        EXPORT J_2
        EXPORT J_3

        EXPORT S_0
        EXPORT S_1
        EXPORT S_2
        EXPORT S_3

        EXPORT Z_0
        EXPORT Z_1
        EXPORT Z_2
        EXPORT Z_3


;  I PIECE

I_0
        DCB 1,1,1,1
        DCB 0,0,0,0
        DCB 0,0,0,0
        DCB 0,0,0,0

I_1
        DCB 0,1,0,0
        DCB 0,1,0,0
        DCB 0,1,0,0
        DCB 0,1,0,0

I_2
        DCB 0,0,0,0
        DCB 0,0,0,0
        DCB 0,0,0,0
        DCB 1,1,1,1

I_3
        DCB 0,1,0,0
        DCB 0,1,0,0
        DCB 0,1,0,0
        DCB 0,1,0,0

;  O PIECE 

O_0
        DCB 1,1,0,0
        DCB 1,1,0,0
        DCB 0,0,0,0
        DCB 0,0,0,0

O_1
        DCB 1,1,0,0
        DCB 1,1,0,0
        DCB 0,0,0,0
        DCB 0,0,0,0

O_2
        DCB 1,1,0,0
        DCB 1,1,0,0
        DCB 0,0,0,0
        DCB 0,0,0,0

O_3
        DCB 1,1,0,0
        DCB 1,1,0,0
        DCB 0,0,0,0
        DCB 0,0,0,0

;  T PIECE

T_0
		DCB 1,1,1,0
        DCB 0,1,0,0
        DCB 0,0,0,0
        DCB 0,0,0,0
T_1
        DCB 0,1,0,0
        DCB 1,1,0,0
        DCB 0,1,0,0
        DCB 0,0,0,0
T_2       		
        DCB 0,0,0,0
        DCB 0,1,0,0
        DCB 1,1,1,0
        DCB 0,0,0,0
T_3
        DCB 1,0,0,0
        DCB 1,1,0,0
        DCB 1,0,0,0
        DCB 0,0,0,0

;  L PIECE

L_0
        DCB 1,0,0,0
        DCB 1,0,0,0
        DCB 1,1,0,0
        DCB 0,0,0,0

L_1
        DCB 1,1,1,0
        DCB 1,0,0,0
        DCB 0,0,0,0
        DCB 0,0,0,0

L_2
        DCB 1,1,0,0
        DCB 0,1,0,0
        DCB 0,1,0,0
        DCB 0,0,0,0

L_3
        DCB 0,0,1,0
        DCB 1,1,1,0
        DCB 0,0,0,0
        DCB 0,0,0,0

;  J PIECE (reverse L)

J_0
        DCB 0,1,0,0
        DCB 0,1,0,0
        DCB 1,1,0,0
        DCB 0,0,0,0

J_1
        DCB 1,0,0,0
        DCB 1,1,1,0
        DCB 0,0,0,0
        DCB 0,0,0,0

J_2
        DCB 1,1,0,0
        DCB 1,0,0,0
        DCB 1,0,0,0
        DCB 0,0,0,0

J_3
        DCB 1,1,1,0
        DCB 0,0,1,0
        DCB 0,0,0,0
        DCB 0,0,0,0


;  S PIECE

S_0
        DCB 1,0,0,0
        DCB 1,1,0,0
        DCB 0,1,0,0
        DCB 0,0,0,0

S_1
        DCB 0,1,1,0
        DCB 1,1,0,0
        DCB 0,0,0,0
        DCB 0,0,0,0

S_2
        DCB 1,0,0,0
        DCB 1,1,0,0
        DCB 0,1,0,0
        DCB 0,0,0,0

S_3
        DCB 0,1,1,0
        DCB 1,1,0,0
        DCB 0,0,0,0
        DCB 0,0,0,0

;  Z PIECE

Z_0
        DCB 0,1,0,0
        DCB 1,1,0,0
        DCB 1,0,0,0
        DCB 0,0,0,0

Z_1
        DCB 1,1,0,0
        DCB 0,1,1,0
        DCB 0,0,0,0
        DCB 0,0,0,0

Z_2
        DCB 0,1,0,0
        DCB 1,1,0,0
        DCB 1,0,0,0
        DCB 0,0,0,0

Z_3
        DCB 1,1,0,0
        DCB 0,1,1,0
        DCB 0,0,0,0
        DCB 0,0,0,0

        END
