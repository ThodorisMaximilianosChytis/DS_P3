objects= graphfuncts.o graphfunctmain.o

runprogram :$(objects)
	gcc -o runprogram $(objects)

dummy.o :graphfuncts.c
	gcc -c graphfuncts.c typedef.h graphfuncts.h

main.o :graphfunctmain.c
	gcc -c graphfunctmain.c typedef.h graphfuncts.h

clean  :
	rm runprogram $(objects)

