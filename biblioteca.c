#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "CABECERAS/biblioteca.h"
#include "CABECERAS/base_datos.h"
#include "CABECERAS/pantalla.h"

int main()
{

    int salir=1,elementos=0, elementosRef=0 ,correcto=1,i;

    //VAMOS A COMPROBAR EL ARCHIVO LECTOR.TXT Y A ALMACENAR SUS DATOS EN LA ESTRUCTURA LECTOR

    elementos=numEl(); //Conseguimos el numero de elementos ubicado en

    struct sLector Lector[100]; //Estructura de 100 elementos

    if(elementos!=0)  //Solo se entra en este bucle si el archivo existe y tiene contenido en su interior
    {
        for(i=0; i<elementos; i++) //Bucle para recorrer el archivo y almacenar en la lista los datos del archivo de texto
        {
            correcto=compLect(&Lector[i],i);  //Llamamos a la funcion compLect ubicada en compLector.c
            if (correcto==0)
            {
                printf("Linea mal formada en el fichero (lectores.txt)");
                return 0; //Si es incorrecto la funcion devuelve 0 que finalizara la ejecucion del programa
            }
        }
    }


    //VAMOS A COMPROBAR EL ARCHIVO REFERENCIAS.TXT Y A ALMACENAR SUS DATOS EN LA ESTRUCTURA REFERENCIAS

    elementosRef=numElRef();
    struct sRef Ref[100];
    correcto=1;

    if (elementosRef!=0)
    {

        for(i=0; i<elementosRef; i++)
        {
            correcto=compRef(Ref, i);

            if (correcto==0)
            {
                printf("Linea mal formada en el fichero (referencias.txt)");
                return 0;
            }
        }
    }

    caratula();  //Funcion caratula



    do     //Bucle hasta que se seleccione salir
    {

        salir=baseDatos(Lector,&elementos, Ref, &elementosRef); //Ubicado en base_datos.c

    }
    while (salir!=0);   //Solo sera 0 cuando se seleccione s o S en el bucle de salir ubicado en base_datos.c y pantalla.c



    return 0;

}




/*-------------------FUNCION COMPROBAR LECTOR--------------*/

//FUNCION COMPROBAR LECTOR

int compLect(struct sLector *Lector, int k)
{

    FILE*ptr;
    char linea[80]; // Longitud nombre 50,Longitud \n 1, Longitud numero 5, Longitud : 3, Longitud \0 1
    int correcto=1,i=1,j=0,l,m=0;
    char aux[10];


    ptr=fopen("lectores.txt", "rt");



    for(l=0; l<k+1; l++)
    {
        fgets(linea,sizeof(linea),ptr);
        if(linea[strlen(linea)-1]!='\n') return 0; //Cadena excesivamente grande
    }


    if(linea[strlen(linea)-2]!=':')
    {
        return 0;   //Devuelve 0 que es incorrecto
    }

    linea[strlen(linea)-2]='\0';


    if(linea[0]!=':') return 0; //Devuelve 0 que es incorrecto


    while (isdigit(linea[i])) //Almacena los numeros en una cadena auxiliar
    {

        aux[j]=linea[i];


        i++;
        j++;

    }

    if(j==0)return 0; // Si no se ha leido ningun numero incorrecto

    if(linea[i]!=':')return 0; //Si el caracter siguiente al numero no es : es incorrecto

    Lector->numero=atoi(aux); //Almaceno el numero en la estructura Lector.numero

    i++;

    if(linea[i]=='\0')return 0; //Si el caracter siguiente al numero es \0 es que la cadena está vacía


    do                        //Almacena los numeros la estructura Lector.nombre
    {

        if(linea[i]==':')return 0; //Si encuentra : en el medio de la cadena, incorrecto

        Lector->nombre[m]=linea[i];

        Lector->nombre[m+1]='\0'; //Asi si hay algun dato en la direccion de memoria nombre lo sustituyo por un final de cadena para no tener problemas despues al leerlo

        if(m>=50)return 0; // Si la longitud de la cadena es mayor de 50, finaliza el programa

        i++;
        m++;

    }
    while (linea[i]!='\0');


    return correcto;
}








//FUNCION NUMERO ELEMENTOS PARA LA ESTRUCTURA

int numEl()
{
    FILE*ptr;
    int lineas=0;
    char ch;

    ptr=fopen("lectores.txt", "r");

    if(ptr==NULL)
    {

        ptr=fopen("lectores.txt", "w");
        fclose(ptr);

        return lineas; // Si el fichero no existe, se abre uno en blanco y se devuelve 1, que es correcto

    }

    do
    {

        ch=fgetc(ptr);
        if(ch=='\n')lineas++;

    }
    while(feof(ptr)==0);  //Cada vez que detecta un salto de linea supone un elemento mas

    fclose(ptr);

    return lineas;
}




/*-------------------FUNCION COMPROBAR REFERENCIA--------------*/



int compRef(struct sRef *Ref, int numero)
{

    FILE*ptr;
    char linea[100], aux[15], aux2[100];
    int i,j,k;

    ptr=fopen("referencias.txt", "r");


    for(i=0; i<=numero; ++i)
    {


        fgets(linea, sizeof(linea), ptr);

        if(Ref[i].criticos>0)
        {
            for(j=0; j<Ref[i].criticos; j++)
            {
                fgets(aux2, sizeof(aux2), ptr);


            }

        }

    }


    if(linea[0]!=':') return 0; //Si el primer caracter no es : error
    if(linea[strlen(linea)-2]!=':')return 0; //Si el penultimo caracter no es : error
    if(linea[strlen(linea)-1]!='\n')return 0; //Si el ultimo caracter no es un salto de linea error

    i=1;
    j=0;


    do
    {

        aux[j]=linea[i]; //Almaceno los numeros de signatura en una cadena auxiliar

        i++;
        j++;
        aux[j]='\0';

    }
    while(isdigit(linea[i]));

    Ref[numero].signatura= atoi(aux); //Convierto en entero y almaceno en la estructura

    if(linea[i]!=':') return 0; //Si el siguiente caracter no es : error

    i++;


    if(linea[i]!='L' && linea[i]!='A') return 0; //Si el siguiente caracter no es de tipo L o A error

    Ref[numero].tipo[0]= linea[i];
    Ref[numero].tipo[1]= '\0';

    i++;

    if(linea[i]!=':') return 0; //Si el siguiente caracter no es : error

    j=0;
    i++;

    do
    {


        Ref[numero].nombre[j]= linea[i]; //Almaceno el autor en la estructura
        i++;
        j++;

        Ref[numero].nombre[j]='\0';

        if(j>50) return 0; //Si autor es mayor de 50 error


    }
    while (linea[i]!=':');

    i++;
    j=0;

    do
    {
        Ref[numero].titulo[j]= linea[i]; //Almaceno el titulo en la estructura
        i++;
        j++;

        Ref[numero].titulo[j]='\0';

        if(j>80) return 0; //Si titulo es mayor de 80 error


    }
    while (linea[i]!=':');

    i++;

    j=0;


    do
    {

        aux[j]=linea[i]; //Almaceno los numeros del anho en una cadena auxiliar

        i++;
        j++;

        aux[j]='\0';


    }
    while(isdigit(linea[i]));


    Ref[numero].anho = atoi(aux); //Convierto en entero y almaceno en la estructura

    if(Ref[numero].anho <1450 && Ref[numero].anho>2018 ) return 0; //Si el anho es menor que 1450 o mayor que 2017 error

    if(linea[i]!=':') return 0;

    i++;

    j=0;


    do
    {

        aux[j]=linea[i]; //Almaceno el numero del votante en una cadena auxiliar

        i++;
        j++;

        aux[j]='\0';


    }
    while(isdigit(linea[i]));


    Ref[numero].votantes = atoi(aux); //Convierto en entero y almaceno en la estructura

    if(linea[i]!=':') return 0;


    i++;

    j=0;


    do
    {

        aux[j]=linea[i]; //Almaceno el numero de votos en una cadena auxiliar

        i++;
        j++;

        aux[j]='\0';


    }
    while(isdigit(linea[i]));



    Ref[numero].votos = atoi(aux); //Convierto en entero y almaceno en la estructura

    if(linea[i]!=':') return 0;


    i++;

    j=0;


    do
    {

        aux[j]=linea[i]; //Almaceno el numero de criticos en una cadena auxiliar

        i++;
        j++;

        aux[j]='\0';


    }
    while(isdigit(linea[i]));


    Ref[numero].criticos = atoi(aux); //Convierto en entero y almaceno en la estructura

    if(linea[i]!=':') return 0;


    if (Ref[numero].criticos==0)return 1;

    else

    {

        for(i=0; i<Ref[numero].criticos; i++)
        {
            fgets(linea, sizeof(linea), ptr);

            if (linea[0]!= '#') return 0;
            if (linea[strlen (linea)-2]!= ':') return 0;

            j=0;
            k=1;

            do
            {

                aux[j]=linea[k]; //Almaceno el numero del lector en una cadena auxiliar

                k++;
                j++;

                aux[j]='\0';


            }
            while(isdigit(linea[k]));


            Ref[numero].lector[i]=atoi(aux);

            if(linea[k]!=':') return 0;


            j=0;
            k++;


            do
            {


                Ref[numero].opinion[i][j]= linea[k]; //Almaceno el comentario en su correspondiente array

                k++;
                j++;

                Ref[numero].opinion[i][j]='\0';



                if(j>80) return 0; //Si autor es mayor de 50 error


            }
            while (linea[k]!=':');





        }

    }
    return 1;
}



//FUNCION COMPROBAR NUMERO DE LINEAS EN ARCHIVO REFERENCIAS



int numElRef()
{
    FILE*ptr;
    int lineas=0;
    char ch;

    ptr=fopen("referencias.txt", "r");

    if(ptr==NULL)
    {

        ptr=fopen("referencias.txt", "w");
        fclose(ptr);

        return lineas; // Si el fichero no existe, se abre uno en blanco y se devuelve 0

    }

    do
    {

        ch=fgetc(ptr);
        if(ch=='\n')lineas++;
        if(ch=='#')lineas--;

    }
    while(feof(ptr)==0);  //Cada vez que detecta un salto de linea supone un elemento mas

    fclose(ptr);

    return lineas;
}


