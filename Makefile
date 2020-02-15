CC	= gcc -Wall
LIBS	= -lm

all: biblioteca

pantalla.o: pantalla.c CABECERAS/pantalla.h CABECERAS/base_datos.h CABECERAS/biblioteca.h
	$(CC) -c pantalla.c

base_datos.o: base_datos.c CABECERAS/pantalla.h CABECERAS/base_datos.h CABECERAS/biblioteca.h
	$(CC) -c base_datos.c




biblioteca: biblioteca.c pantalla.o base_datos.o
	$(CC) pantalla.o base_datos.o biblioteca.c -o biblioteca $(LIBS)

clean:
	rm -f biblioteca *.o *~ *.bak


