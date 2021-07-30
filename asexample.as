MAIN: add $3  ,  $5  , $9
LOOP: add $9,-5,$2
NEXT:  move $20   , $4
loopr: ori $9,-5, $2
jdi: blt $5, $24, MAIN
   sw $0,4,$10
   jmp NEXT
ido:     .db 7, -57, 17, +9
      jmp MAIN
      jmp $4
      stop