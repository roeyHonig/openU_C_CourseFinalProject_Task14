MAIN: add $3  ,  $5  , $9
LOOP: add $9,-5,$2
NEXT:  move $20   , $4
loopr: ori $9,-5, $2
jdi: blt $5, $24, NEXT
   sw $0,4,$10
   jmp NEXT
ido:     .db    8   ,   -56   ,   99   ,   +3  
ido1:     .asciz    ""  
   .entry NEXT
   .extern MAINor
      jmp MAIN
      jmp $4
      stop