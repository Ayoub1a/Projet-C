output: gestion_emprunts.o emprunts.o adherents.o livres.o *.h
	gcc gestion_emprunts.o emprunts.o adherents.o livres.o -o output
livres.o: livres.c livres.h
	gcc -c livres.c
emprunts.o: emprunts.c emprunts.h
	gcc -c emprunts.c
adherents.o: adherents.c adherents.h
	gcc -c adherents.c
gestion_emprunts.o: gestion_emprunts.c *.h
	gcc -c gestion_emprunts.c
clean: 
	rm *.o output
