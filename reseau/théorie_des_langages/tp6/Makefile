exo : lex.yy.o exo.tab.c
	gcc exo.tab.c lex.yy.o -o exo -ly -lfl
lex.yy.o : lex.yy.c
	gcc -c lex.yy.c
lex.yy.c : exo.l exo.tab.h
	flex exo.l
exo.tab.h : exo.y
	bison -d exo.y
exo.tab.c : exo.y
	bison -d exo.y

clean :
	-rm *.o
	-rm *.tab.c
	-rm *.tab.h
	-rm lex.yy.c
