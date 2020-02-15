#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CABECERAS/pantalla.h"

void caratula()
{
    base('#', 80); //Caracter y numero de caracteres
  lados(1, '#', 80); //Repeticion, caracter y numero de caracteres
  lados(1, '#', 80);//Repeticion, caracter y numero de caracteres
  titulo('#',"BIBLIOTECA", 1, 80); //Caracter, mensaje, repeticion y numero de caracteres
  lados(1, '#', 80); //Repeticion, caracter y numero de caracteres
  lados(1, '#', 80); //Repeticion, caracter y numero de caracteres
  base('#', 80); //Caracter y numero de caracteres
 
    return;
}




void base(char caracter, int numChar)

{
  int a;
    if(numChar>MAX_LON_CARACTER) numChar=MAX_LON_CARACTER;
    for(a=0;a<numChar;a++){
      printf("%c", caracter);
    }
    printf("\n");
    return;
}


void lados(int repeticion, char caracter, int numChar){
    int b,i;
    if(numChar>MAX_LON_CARACTER) numChar=MAX_LON_CARACTER;
    for(i=0;i<repeticion;i++){
    printf("%c", caracter);
    
      for(b=0;b<numChar-2;b++){
	printf(" ");
      }
    printf ("%c", caracter);
    printf ("\n");}
    return;
  }

void titulo(char caracter,char nombre[], int repeticion, int numChar){
  int d,e,i;
  d=(numChar-strlen(nombre)-2)/2;
    
  if(numChar>MAX_LON_CARACTER) numChar=MAX_LON_CARACTER;
  for(i=0;i<repeticion;i++){
  printf("%c", caracter);
  for(e=0;e<d;e++){
    printf(" ");
  }
  printf("%s", nombre);
  for(e=0;e<d;e++){
    printf(" ");
  }
  printf("%c", caracter);
  printf("\n");}
  return;
}


int menu()
{

    char eleccion,enter;


    printf("\n1) Incorporar lector\n");
    printf("2) Agregar referencia\n");
    printf("3) Expresar opinion\n");
    printf("4) Obtener informe\n");
    printf("5) Emitir voto\n");
    printf("6) Calcular nota\n");
    printf("7) Listar referencias\n");
    printf("8) Buscar referencia\n");
    printf("9) Cambiar lector\n");
    printf("0) Salir\n\n");
    printf("Siguiente comando? ");

    eleccion= getchar();

    enter=getchar();
    printf("\n");
    if(enter!='\n')
    {
        ; //Si el segundo caracter introducido no es un enter mando un valor de eleccion para el que me de error
        while(getchar()!='\n'); //Si el ultimo caracter no es un enter hacemos un bucle para coger todos los valores y que no se queden en el buffer
        eleccion=-1;
        return eleccion;
    }

    return eleccion;
}




int confirmar()

{

    char salir,enter;
    int valido;

    do                                        //Bucle hasta que la eleccion sea S,s,N o n
    {
        printf("\nSeguro que deseas salir del programa? (s/n): ");

        salir=getchar();
        enter=getchar();
        if(enter!='\n')
        {
            ; //Si el segundo caracter introducido no es un enter mando un valor de eleccion para el que me de error
            while(getchar()!='\n'); //Si el ultimo caracter no es un enter hacemos un bucle para coger todos los valores y que no se queden en el buffer
            valido=1;
            return valido;
        }

        switch(salir)
        {
        case 's':
            valido=0; //Si la eleccion es S ó s hago valido=0, para salir del 1er bucle
            break;
        case 'S':
            valido=0;
            break;
        case 'n':
            break;
        case 'N':
            break;
        default:
            break;


        }
    }
    while (salir!='s' && salir!='S' && salir!='N' && salir!='n');

    return valido;

}


