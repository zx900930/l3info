exo: exo.o semaphore.o
	@echo "Compilation de $@"
	gcc exo.o semaphore.o -o exo

exo.o: exo.c semaphore.h
	@echo "Compilation de exo.c"
	gcc -c exo.c

semaphore.o : semaphore.c semaphore.h
	@echo "Compilation de semaphore.c"
	gcc -c semaphore.c

clean:
	-rm *.o

cleanExo:
	-rm exo
