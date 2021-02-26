objects= hashfuncts.o hashmain.o

runprogram :$(objects)
	gcc -o runprogram $(objects)

dummy.o :hashfuncts.c
	gcc -c hashfuncts.c typedef.h hashfuncts.h

main.o :hashmain.c
	gcc -c hashmain.c typedef.h hashfuncts.h

clean  :
	rm runprogram $(objects) 