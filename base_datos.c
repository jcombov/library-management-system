#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "CABECERAS/pantalla.h"
#include "CABECERAS/biblioteca.h"
#include "CABECERAS/base_datos.h"





int baseDatos(struct sLector *Lector,int *elementos, struct sRef *Ref, int *elementosRef)
{

    int valido=1, repetido;

    char eleccion;

    eleccion=menu(); //Llamo a la funcion menu, que me devolvera el valor de eleccion, ubicada en el archivo pantalla.c

    switch(eleccion)  //Segun el valor devuelto, elijo que hacer
    {
    case '1':
        // Seleccion 1

        repetido=lector(Lector, *elementos); //Le paso a lector la estructura y el numero de elementos
        if(repetido!=1)* elementos = *elementos +1; //Cada vez que se ejecuta la instruccion se añade un lector mas
        break;
    case '2':
        referencia( Ref, *elementosRef ); //Le paso a referencia la estructura y su numero de elementos
        * elementosRef = *elementosRef + 1; //Cada vez que se ejecuta, el numero de elementos aumenta en 1
        break;
    case '3':

        if (*elementosRef==0  || *elementos==0)
        {
            printf("\nOperacion imposible en este momento\n"); //Si no hay ningun elemento de referencia o lector operacion no valida
        }
        else  opinion(Ref , *elementosRef, Lector, *elementos); //Le paso a opinion la estructura referencia y sus elementos y la estructura lector y sus elementos
        break;
    case '4':
        if (*elementosRef==0)
        {
            printf("\nOperacion imposible en este momento\n"); //Si no hay ningun elemento de referencia o lector operacion no valida
        }
        else informa(Ref, *elementosRef, Lector, *elementos);

        break;
    case '5':

        if (*elementosRef==0)
        {
            printf("\nOperacion imposible en este momento\n"); //Si no hay referencias no valido
        }
        else voto(Ref, *elementosRef); // Le paso la estructura referencia y el numero de elementos

        break;
    case '6':
        if (*elementosRef==0)
        {
            printf("\nOperacion imposible en este momento\n"); //Si no hay referencias no valido
        }

        else nota(Ref,*elementosRef);
        break;
    case   '7':
        listar(Ref,*elementosRef);
        break;

    case '8':

        buscar(Ref,*elementosRef, Lector, *elementos);
        break;

    case '9':

	cambiar(Lector, *elementos);
	break;

    case '0':

        valido=confirmar(); //Llamo a la funcion confirmar, ubicada en pantalla.c
        break;



    default:
        printf("\nHas realizado una seleccion no valida\n");
        break;


    }

    return valido;
}





/*------------------------------FUNCION LECTOR------------------------------*/


int lector(struct sLector *Lector,int elementos) //Hay que pasar la estructura como puntero para poder hacer modificaciones
{

    int correcto=1,i;
    char nombre[51] ;


    FILE*ptr;


    do
    {

        printf("\nEscribe el nombre del lector: ");
        fgets(nombre,sizeof(nombre),stdin);


        correcto=compNom(nombre); //Llamo a la funcion compNom

        for(i=0; i<elementos; i++)
        {

            if(strcmp(nombre,Lector[i].nombre)==0)  //Compruebo que el usuario no este repetido
            {
                correcto=0;
                printf("\nLector repetido\n");
                return 1;
                break;
            }

        }

    }
    while(correcto==0);

    if(elementos==0)Lector[elementos].numero=1;
    else
        Lector[elementos].numero=Lector[elementos-1].numero+1; //Al numero del usuario anterior le sumo 1



    strcpy(Lector[elementos].nombre, nombre); //Copio la cadena en memoria


    ptr=fopen("lectores.txt", "at"); //Abro el archivo en modo añadir texto


    printf("\nLector %s: asignado %d\n", Lector[elementos].nombre, Lector[elementos].numero);

    fprintf(ptr, ":%i:%s:\n", Lector[elementos].numero, Lector[elementos].nombre); //Escribo en el fichero con el formato indicado

    fclose(ptr); //Cierro el archivo

    return 0;
}




//FUNCION COMPROBAR NOMBRE


int compNom(char nombre[])
{
    int correcto=1,k;


    if(nombre[strlen(nombre)-1]!='\n') // Si el penultimo caracter no es un \n significa que se han escrito mas caracteres de los definidos
    {
        printf ("\nLongitud de la cadena excesiva\n");
        while(fgetc(stdin)!='\n');
        correcto=0;
        return correcto;

    }

    if(strlen(nombre)==1) // Si la cadena tiene longitud 1 solo se ha introducido un enter
    {
        printf("\nCadena vacia\n");
        correcto=0;
        return correcto;
    }

    for(k=0; k<strlen(nombre); k++)
    {
        if (nombre[k]==':')   //Si algun caracter es ':', es invalido
        {
            printf("\nCaracter invalido\n");
            correcto=0;
            return correcto;
        }
    }
    nombre[strlen(nombre)-1]= '\0';  // En el lugar del '/n' escribo un '/0' (final de cadena)
    return correcto;
}




/*--------------------FUNCION AGREGAR REFERENCIA------------------*/


void referencia(struct sRef *Ref, int elementosRef)  //Estructura ubicada en la cabecera
{

    int correcto;
    char nombre[52], titulo[82], tipo[3],anho[6];

    if (elementosRef!=0) Ref[elementosRef].signatura= Ref[elementosRef-1].signatura+1; //Si hay mas de 0 elementos se le suma 1 a la signatura de la anterior referencia
    else Ref[elementosRef].signatura= 1;

    Ref[elementosRef].votantes= 0;

    Ref[elementosRef].votos= 0;

    Ref[elementosRef].criticos= 0;




    do
    {
        printf("\nEscribe el autor de la referencia: ");
        fgets(nombre,sizeof(nombre),stdin); //Pido el nombre del autor


        correcto=compNom(nombre); //Llamo a la funcion compNom ubicada en lector


    }
    while (correcto!=1);  //Bucle hasta que correcto sea 1

    strcpy(Ref[elementosRef].nombre, nombre);

    do
    {
        printf("\nEscribe el titulo: ");
        fgets(titulo,sizeof(titulo),stdin); //Pido el titulo

        correcto=compNom(titulo); //Llamo a la funcion compNom ubicada en lector



    }
    while (correcto!=1);  //Bucle hasta que correcto sea 1

    strcpy(Ref[elementosRef].titulo, titulo);


    do
    {
        printf("\nEscribe el anho: "); //Pido el anho
        fgets(anho,sizeof(anho),stdin);

        if(anho[strlen(anho)-1]!='\n') while(fgetc(stdin)!='\n'); //Vaciamos buffer si se introduce mas de 4 caracteres

        Ref[elementosRef].anho=atoi(anho);
        correcto=compAnho(Ref[elementosRef].anho); //Llamo a la funcion COMPROBAR ANHO

    }
    while (correcto!=1);  //Bucle hasta que correcto sea 1




    do
    {
        printf("\nEscribe el tipo: ");
        fgets(tipo,sizeof(tipo),stdin); //Pido el tipo

        correcto=compNom(tipo); //Llamo a la funcion compNom ubicada en lector
        tipo[0]=toupper(tipo[0]);

        if((tipo[0]=='A' || tipo[0]=='L') && correcto==1) // Si tipo es A o L correcto
        {
            correcto=1;
        }
        else if(correcto==0) continue; // Para evitar dos mensajes de error
        else 				// Si no es A ni L Caracter invalido y correcto 0
        {
            printf("\nCaracter invalido\n");
            correcto=0;
        }


    }
    while (correcto!=1);  //Bucle hasta que correcto sea 1

    strcpy(Ref[elementosRef].tipo, tipo);

    FILE*ptr;

    ptr=fopen("referencias.txt", "at"); //Abro el archivo referencias en modo añadir texto

    fprintf(ptr,":%ld:%s:%s:%s:%i:%i:%ld:%i:\n",Ref[elementosRef].signatura,Ref[elementosRef].tipo,Ref[elementosRef].nombre,Ref[elementosRef].titulo,Ref[elementosRef].anho,Ref[elementosRef].votantes,Ref[elementosRef].votos,Ref[elementosRef].criticos);

    fclose(ptr);

    printf("\nReferencia %s:%s:%s:%i: asignada %ld\n", Ref[elementosRef].tipo, Ref[elementosRef].nombre, Ref[elementosRef].titulo, Ref[elementosRef].anho, Ref[elementosRef].signatura); //Mensaje por pantalla


    return;
}



//FUNCION COMPROBAR ANHO


int compAnho(int anho)
{

    if(anho>=1450 && anho<=2017) return 1; //El anho tiene que estar comprendido entre 1450 y 2017
    else
    {
        printf("\nValor seleccionado incorrecto\n");

        return 0;
    }

}




/*--------------------FUNCION AGREGAR OPINION------------------*/


void opinion(struct sRef *Ref, int elementosRef, struct sLector *Lector, int elementosLector)
{

    int codigo, correcto=1, i,signatura, j, validar;
    char signaturaaux[4], codigoaux[4];
    char comentario[80];



    do
    {

        printf("\nEscribe la signatura:");//se pide la signatura y se comprueba si cumple los requisitos
        fgets(signaturaaux, sizeof(signaturaaux), stdin);

        for(i=0; i<strlen(signaturaaux)-1; i++)
        {
            validar=isdigit(signaturaaux[i]);
            if(validar==0)break;

        }

        if(signaturaaux[strlen(signaturaaux)-1]!='\n')  while(fgetc(stdin)!='\n'); //Vaciamos buffer si se introduce mas de un caracter
        else if (validar==0) correcto=1;
        else
        {

            signatura= atoi(signaturaaux);
            for(i=0; i<elementosRef; i++)
            {
                if(signatura==Ref[i].signatura) //Comparamos la signatura con los datos en memoria
                {
                    correcto=0;
                    break;
                }

            }
        }


        if(correcto!=0)
        {
            printf("\nValor seleccionado incorrecto\n");
        }

    }
    while(correcto != 0);

    do
    {

        printf("\nEscribe el codigo: "); //se pide el codigo y se comprueba si cumple los requisitos
        correcto=1;
        fgets(codigoaux, sizeof(codigoaux), stdin);

        for(i=0; i<strlen(codigoaux)-1; i++)
        {
            validar=isdigit(codigoaux[i]);
            if(validar==0)break;

        }

        if(codigoaux[1]!='\n' && codigoaux[2]!='\n')  while(getchar()!='\n'); //vaciamos el buffer si se han introducido mas de dos digitos
        else if (validar==0) correcto=1;
        else
        {

            codigo= atoi(codigoaux); //Convertimos en int

            for(i=0; i<elementosLector; i++)

            {
                if(Lector[i].numero==codigo) //Comparamos con los datos en memoria
                {
                    correcto=0;
                    break;
                }
            }
        }

        if(correcto!=0)
        {
            printf("\nValor seleccionado incorrecto\n");
        }

    }
    while(correcto != 0);


    do
    {
        printf("\nEscribe el comentario: "); //se pide el comentario a almecenar
        fgets(comentario,80,stdin);
        correcto= compNom(comentario); //LLamamos a compNom en lector



    }
    while(correcto != 1);

    strcpy(Ref[signatura-1].opinion[Ref[signatura-1].criticos], comentario);  //Copiamos cadena a memoria
    Ref[signatura-1].lector[Ref[signatura-1].criticos]=codigo; //Copiamos el codigo a memoria

    Ref[signatura-1].criticos++; //Sumamos uno al numero de criticos

    FILE*ptr;

    ptr=fopen("referencias.txt", "w"); //Reescribimos el archivo de texto

    for(i=0; i<elementosRef; i++ )
    {
        if(Ref[i].criticos>0)
        {
            fprintf(ptr,":%ld:%s:%s:%s:%i:%i:%ld:%i:\n",Ref[i].signatura,Ref[i].tipo,Ref[i].nombre,Ref[i].titulo,Ref[i].anho,Ref[i].votantes,Ref[i].votos,Ref[i].criticos);

            for(j=0; j<Ref[i].criticos; j++) //Si hay mas de 0 criticos escribimos las opiniones
            {
                fprintf(ptr,"#%i:%s:\n", Ref[i].lector[j], Ref[i].opinion[j]);
            }




        }

        if (Ref[i].criticos==0)fprintf(ptr,":%ld:%s:%s:%s:%i:%i:%ld:%i:\n",Ref[i].signatura,Ref[i].tipo,Ref[i].nombre,Ref[i].titulo,Ref[i].anho,Ref[i].votantes,Ref[i].votos,Ref[i].criticos);



    }

    fclose(ptr);


    printf("\nOpinion registrada\n");//todo se ha realizado correctamente y el comentario ha sido guardado

    return;
}






/*--------------------FUNCION OBTENER INFORME------------------*/



void informa(struct sRef *Ref, int elementosRef, struct sLector *Lector, int elementosLector)
{

    int correcto=1,validar, signatura, i, j,k;
    char signaturaaux[4];

    do
    {

        printf("\nEscribe la signatura:");//se pide la signatura y se comprueba si cumple los requisitos
        fgets(signaturaaux, sizeof(signaturaaux), stdin);

        for(i=0; i<strlen(signaturaaux)-1; i++)
        {
            validar=isdigit(signaturaaux[i]);
            if(validar==0)break;

        }

        if(signaturaaux[strlen(signaturaaux)-1]!='\n')  while(fgetc(stdin)!='\n'); //Vaciamos buffer si se introduce mas de un caracter
        else if (validar==0) correcto=1;
        else
        {

            signatura= atoi(signaturaaux);


            for(i=0; i<elementosRef; i++)
            {
                if(signatura==Ref[i].signatura)  //comprobamos que la signatura coincida con la que esta guardada en memoria
                {
                    correcto=0;
                    break;
                }

            }
        }


        if(correcto!=0)
        {
            printf("\nValor seleccionado incorrecto\n");
        }

    }
    while(correcto!=0);  //Bucle mientras no sea correcto



    printf("\nNumero de comentarios:%i\n", Ref[i].criticos); //Escribo por pantalla el numero de criticos


    for(j=0; j<Ref[i].criticos; j++) //Bucle para recorrer los comentarios
    {
        for(k=0; k<elementosLector; k++) //Bucle para recorrer los lectores
        {
            if(Ref[i].lector[j]==Lector[k].numero) //Si el lector es igual al numero escribe el nombre del critico y su opinion
            {
                printf("%s:%s\n",Lector[k].nombre, Ref[i].opinion[j]);
                break;
            }
        }


    }


}




/*--------------------FUNCION EMITIR VOTO------------------*/



void voto(struct sRef *Ref, int elementosRef)
{

    int correcto=1, voto, signatura, i, j, validar;
    char signaturaaux[4], votoaux[4];

    do
    {

        printf("\nEscribe la signatura: ");//se pide la signatura y se comprueba si cumple los requisitos
        fgets(signaturaaux, sizeof(signaturaaux), stdin);

        for(i=0; i<strlen(signaturaaux)-1; i++)
        {
            validar=isdigit(signaturaaux[i]);
            if(validar==0)break;

        }

        if(signaturaaux[1]!='\n' && signaturaaux[2]!='\n')  while(getchar()!='\n'); //Vaciamos buffer si se introduce mas de un caracter
        else if(validar==0) correcto=1;
        else
        {

            signatura= atoi(signaturaaux);


            for(i=0; i<elementosRef; i++)
            {
                if(signatura==Ref[i].signatura)  //comprobamos que la signatura coincida con la que esta guardada en memoria
                {
                    correcto=0;
                    break;
                }

            }
        }


        if(correcto!=0)
        {
            printf("\nValor seleccionado incorrecto\n");
        }

    }
    while(correcto!=0);




    do
    {

        printf("\nEscribe el voto: ");//se pide la signatura y se comprueba si cumple los requisitos
        fgets(votoaux, sizeof(votoaux), stdin);
        correcto=1;

        if(votoaux[strlen(votoaux)-1]!='\n')  while(fgetc(stdin)!='\n'); //Vaciamos buffer si se introduce mas de dos caracter
        else if(votoaux[1]!='0' && votoaux[1]!='\n') correcto=1;
        else
        {

            voto= atoi(votoaux);

            correcto=compvoto(voto);

        }


        if(correcto!=0)
        {
            printf("\nValor seleccionado incorrecto\n");
        }

    }
    while(correcto!=0);

    //Ahora procedemos a guardar los datos en memoria

    Ref[i].votantes++;
    Ref[i].votos+=voto;

    FILE*ptr;

    ptr=fopen("referencias.txt", "w"); //Reescribimos el archivo de texto

    for(i=0; i<elementosRef; i++ )
    {
        if(Ref[i].criticos>0)
        {
            fprintf(ptr,":%ld:%s:%s:%s:%i:%i:%ld:%i:\n",Ref[i].signatura,Ref[i].tipo,Ref[i].nombre,Ref[i].titulo,Ref[i].anho,Ref[i].votantes,Ref[i].votos,Ref[i].criticos);

            for(j=0; j<Ref[i].criticos; j++) //Si hay mas de 0 criticos escribimos las opiniones
            {
                fprintf(ptr,"#%i:%s:\n", Ref[i].lector[j], Ref[i].opinion[j]);
            }




        }

        if (Ref[i].criticos==0)fprintf(ptr,":%ld:%s:%s:%s:%i:%i:%ld:%i:\n",Ref[i].signatura,Ref[i].tipo,Ref[i].nombre,Ref[i].titulo,Ref[i].anho,Ref[i].votantes,Ref[i].votos,Ref[i].criticos);



    }

    fclose(ptr);

    printf("\nVoto registrado\n"); //mensaje operacion de operacion correcta



    return;
}


//FUNCION COMPVOTO

int compvoto(int voto)
{

    if(voto >= 0 && voto <= 10) //el voto ha de estar comprendido entre 0 y10
    {

        return 0;//si se cumple se devuelve la llave para salir del bucle

    }
    else
    {

        return 1;//valor incorrecto se retorna al bucle, con el mensaje de error
    }
    return -1;
}




/*--------------------FUNCION CALCULAR NOTA------------------*/



void nota(struct sRef *Ref, int elementosRef)
{

    int i,signatura,correcto=1, validar;
    float Nota_media;
    char signaturaaux[4];

    do
    {

        printf("\nEscribe la signatura: ");//se pide la signatura y se comprueba si cumple los requisitos
        fgets(signaturaaux, sizeof(signaturaaux), stdin);

        for(i=0; i<strlen(signaturaaux)-1; i++)
        {
            validar=isdigit(signaturaaux[i]);
            if(validar==0)break;

        }

        if(signaturaaux[1]!='\n' && signaturaaux[2]!='\n')  while(getchar()!='\n'); //vaciamos el buffer si se han introducido mas de dos digitos
        else if (validar==0)correcto=1;
        else
        {

            signatura= atoi(signaturaaux);
            for(i=0; i<elementosRef; i++)
            {
                if(signatura == Ref[i].signatura) //Comparamos la signatura con los datos en memoria
                {
                    correcto=0;
                    break;
                }

            }
        }


        if(correcto!=0)
        {
            printf("\nValor seleccionado incorrecto\n");
        }

    }
    while(correcto != 0);

    //Ahora procedemos a sacar los datos por pantalla

    if(Ref[signatura-1].votantes == 0)
    {

        printf("\nNumero de votos:0");
        printf("\nNota media:0.00\n");

    }
    else
    {

        Nota_media = (float)Ref[signatura-1].votos / (int)Ref[signatura-1].votantes;
        printf("\nNumero de votos:%i",Ref[signatura-1].votantes);
        printf("\nNota media:%1.2f\n",Nota_media);

    }

    return;
}




/*--------------------FUNCION LISTAR REFERENCIA------------------*/



void listar(struct sRef *Ref, int elementosRef)
{

    char tipo[4];
    int i, correcto;


    do
    {
        printf("\nL) Libros");
        printf("\nA) Articulos");
        printf("\n\nElige el tipo de referencias que quieres listar: ");
        fgets(tipo,sizeof(tipo),stdin); //Pido el tipo
        printf("\n");

        correcto=compNom(tipo); //Llamo a la funcion compNom ubicada en lector
        tipo[0]=toupper(tipo[0]);

        if((tipo[0]=='A' || tipo[0]=='L') && correcto==1) // Si tipo es A o L correcto
        {
            correcto=1;
        }
        else if(correcto==0) continue; // Para evitar dos mensajes de error
        else 				// Si no es A ni L Caracter invalido y correcto 0
        {
            printf("\nTipo seleccionado no valido\n");
            correcto=0;
        }


    }
    while (correcto!=1);  //Bucle hasta que correcto sea 1

    for(i=0; i<elementosRef; i++)
    {

        if(strcmp(tipo,Ref[i].tipo)==0)  //Compruebo que coincida el tipo
        {
            if(tipo[0]=='l' || tipo[0]=='L')
            {
                printf("\n%i) %s. \"%s\" (%i)",i+1,Ref[i].nombre,Ref[i].titulo,Ref[i].anho);
            }
            else if(tipo[0]=='A' || tipo[0]=='a')
            {
                printf("\n%i) %s. \"%s\" (%i)",i+1,Ref[i].nombre,Ref[i].titulo,Ref[i].anho);
            }

        }
    }
    printf("\n");
    return;

}





/*------------------------FUNCION BUSCAR REFERENCIA------------------*/




void buscar(struct sRef *Ref, int elementosRef, struct sLector *Lector, int elementosLector)

{
    char cadena[80],cadenaaux[80];
    int correcto,i,j,k,a,l,error=0,opiniones;

    do
    {
        correcto=1;


        printf("\nDame la cadena de busqueda: ");// se pide y recoge la cadena de busqueda a encontrar
        fgets(cadena,sizeof(cadena),stdin);

        if(strlen(cadena)==1) //si es igual a 1 significa que solo se introdujo un enter
        {
            printf("\nCadena de busqueda vacia\n");
            correcto=0;
        }
        if(cadena[0]==13 || cadena[0]==32 || cadena[0]==9) //si el primer componente de cadea es igual a uno de estas tres condiciones significa que es igual a intro, a espacio, o a tabulador
        {
            printf("\nCadena de busqueda vacia\n");
            correcto=0;
        }
        for(a=0; a<strlen(cadena); a++) //en este bucle miro si el usuario introdujo una cadena entera de espacios
        {
            if(cadena[a]==13) error++;
        }
        if(error==strlen(cadena))//si la variable utilizada para contar el numero de espacios que hay es igual al tamaño de la cadena introducida da error
        {
            printf("\nCadena de busqueda vacia\n");
            correcto=0;
        }


        if(correcto==1) // si se salio del bucle de comprobacion de cadena ahora se pasa a la comprobacion de la busqueda de cadena
        {


            cadena[strlen(cadena)-1]='\0';//introducimos un caracter fin de cadena para simplificar las operaciones
            correcto=0;//variable que vamos a utilizar en el segundo bucle
            for(i=0; i<elementosRef; i++) // Bucle con los elementos de referencias
            {
                if(correcto==1)break; //Si se encuentra una coincidencia correcto sera 1 entonces saldra de todos los bucles
                for(j=0; j<strlen(Ref[i].titulo); j++) //Bucle para titulo
                {
                    if(correcto==1)break; //Si se encuentra una coincidencia correcto sera 1 entonces saldra de todos los bucles

                    if(Ref[i].titulo[j]==cadena[0])  //Si la primera letra coincide se pasa a comparar las siguientes
                    {
                        l=0;
                        for(k=j; k<strlen(cadena)+j; k++) //Se recorren las siguientes posiciones con la longitud de cadena para obtener una de igual tam.
                        {

                            cadenaaux[l]=Ref[i].titulo[k]; //Se almacena en una cadena auxiliar
                            l++;
                        }
                        cadenaaux[strlen(cadena)]='\0'; //Por si hay algo almacenado que no quieres en cadenaaaux
                        if(strcmp(cadena,cadenaaux)==0)correcto=1; // Se comparan y se ve si son iguales, si son iguales correcto hara que se salga
                    }
                }
            }


            if(correcto==0)
            {
                for(i=0; i<elementosRef; i++)
                {
                    if(correcto==1)break;
                    for(j=0; j<strlen(Ref[i].nombre); j++) //Bucle para nombre, funciona igual que el de titulo
                    {
                        if(correcto==1)break;
                        if(Ref[i].nombre[j]==cadena[0])
                        {
                            l=0;
                            for(k=j; k<strlen(cadena)+j; k++)
                            {
                                cadenaaux[l]=Ref[i].nombre[k];
                                l++;
                            }
                            cadenaaux[strlen(cadena)]='\0';
                            if(strcmp(cadena,cadenaaux)==0)correcto=1;

                        }
                    }
                }
            }

            if(correcto==1)
            {
                printf("\n\n%li) [%s] %s. \"%s\" (%i)\n", Ref[i-1].signatura,Ref[i-1].tipo,Ref[i-1].nombre,Ref[i-1].titulo,Ref[i-1].anho);
                for(opiniones=0; opiniones<Ref[i-1].criticos; opiniones++)
                {
                    for(k=0; k<elementosLector; k++) //Bucle para recorrer los lectores
                    {
                        if(Ref[i-1].lector[opiniones]==Lector[k].numero) //Si el lector es igual al numero escribe el nombre del critico y su opinion
                        {
                            printf("%s -> %s\n",Lector[k].nombre,Ref[i-1].opinion[opiniones]);
                        }

                    }
                }
            }
            if(correcto==0)
            {
                printf("\n\nNinguna referencia contiene la cadena de busqueda\n");
                return;
            }

        }


    }
    while(correcto==0);
}




/*--------------------------FUNCION CAMBIAR LECTOR------------------------*/


void cambiar(struct sLector *Lector, int elementosLector)
{

char cadena[80], cadenaaux[80], nuevacadena[80], cadenaaux2[80], enter, eleccion;
int correcto, a, error,i, j, k, l, repetir, coincide, diferencia;
FILE *ptr;

do{
correcto=1;
printf("\nDame el texto de busqueda: ");
fgets(cadena, sizeof(cadena), stdin);


        if(strlen(cadena)==1) //si es igual a 1 significa que solo se introdujo un enter
        {
            printf("\nTexto vacio\n");
            correcto=0;
        }
        if(cadena[0]==13 || cadena[0]==32 || cadena[0]==9) //si el primer componente de cadea es igual a uno de estas tres condiciones significa que es igual a intro, a espacio, o a tabulador
        {
            printf("\nTexto vacio\n");
            correcto=0;
        }
        for(a=0; a<strlen(cadena); a++) //en este bucle miro si el usuario introdujo una cadena entera de espacios
        {
            if(cadena[a]==13) error++;
        }
        if(error==strlen(cadena))//si la variable utilizada para contar el numero de espacios que hay es igual al tamaño de la cadena introducida da error
        {
            printf("\nTexto vacio\n");
            correcto=0;
        }

cadena[strlen(cadena)-1]='\0';
if (correcto==1){
do{
correcto=1;
printf("\nDame el nuevo texto: ");
fgets(nuevacadena, sizeof(nuevacadena), stdin); 

for(i=0;i<strlen(nuevacadena);i++)
{
 if(nuevacadena[i]==':') 
 {
  printf("\nCaracter invalido\n");
  correcto=0;
  break;
 }
}
}while(correcto==0); //Pedimos la nueva cadena y comprobamos que no tenga dos puntos, si los tiene, se vuelve a pedir la cadena

}	

nuevacadena[strlen(nuevacadena)-1]='\0';
	if(correcto==1)
	{
	  
          repetir=0;
          coincide=0;
	  for(i=0; i<elementosLector; i++)
                {
                    if(repetir==1)break;
                    for(j=0; j<strlen(Lector[i].nombre); j++) //Bucle para nombre, funciona igual que el de titulo
                    {
                        if(repetir==1)break;
                        if(Lector[i].nombre[j]==cadena[0]) //Si coincide un caracter se pasa a comprobar los siguientes
                        {
                            l=0;
                            for(k=j; k<strlen(cadena)+j; k++)
                            {
                                cadenaaux[l]=Lector[i].nombre[k]; //Se almacenan los siguientes en una cadena auxiliar
                                l++;
                            }
                            cadenaaux[strlen(cadena)]='\0'; 
                            if(strcmp(cadena,cadenaaux)==0)coincide=1; //Si son iguales paso a preguntar si quiere cambiar el lector
			    if(coincide==1) 
				{printf("\n\nEncontrado: %i) %s\n", Lector[i].numero, Lector[i].nombre);
				 do{printf("\nQuieres cambiar a este lector? (s/n): ");
				
				 eleccion=fgetc(stdin);
 				 enter=getchar();
			         if(enter!='\n') {while(fgetc(stdin)!='\n'); eleccion='a';} //Si el segundo caracter no es un enter vacio el buffer
				 }while(eleccion!='s' && eleccion!='S'  && eleccion!='n' && eleccion!='N'); //Si eleccion es s salgo del bucle para sustituir el nombre, si no, permanezco en él
				 	if(eleccion=='s' || eleccion=='S') repetir=1;
			                else repetir=0;

				}

                        }
                    }
                }




        }

	if(repetir==0)printf("\nNingun lector cambiado\n"); //Si no hay coincidencias o no se ha seleccionado s no se cambia ningun lector
        if(repetir==1)
	{
	  strcpy(cadenaaux2, Lector[i-1].nombre); //Copio el nombre en una cadena auxiliar
          diferencia=strlen(cadena)-strlen(nuevacadena); //Calculo la diferencia entre la cadena de busqueda y la nueva cadena a introducir
 	  l=0;
          do
          {
            Lector[i-1].nombre[j-1]=nuevacadena[l]; //Copio en lector.nombre desde el primer caracter en el que coincidieron nombre y nueva cadena, hasta el final de nueva cadena
            j++;
            l++;
          }while(nuevacadena[l]!='\0'); //Si la longitud de cadena de busqueda y nueva cadena es igual, ya no hacen falta mas cambios

          if(strlen(nuevacadena)<strlen(cadena) || strlen(nuevacadena)>strlen(cadena)) //Si son de diferente tamaño hay que recurrir a la cadena auxiliar guardada anteriormente
          {
	    do{
	    
            Lector[i-1].nombre[j-1]=cadenaaux2[j+diferencia-1]; //Si es mayor nueva cadena que cadena de busqueda, diferencia sera negativa y viceversa, por lo que hara que se mueva a las posiciones de cadenaaux2 que se sobreescribieron, o que sobran en caso contrario, para reescribir la parte con la parte restante, o sin la parte sobrante, el nuevo nombre
	    j++;
	    Lector[i-1].nombre[j-1]='\0';
	    }while(cadenaaux2[j+diferencia-1]!='\0');
          }

          
          ptr=fopen("lectores.txt", "w");
          
	  printf("\n\nLector cambiado a: %i) %s\n", Lector[i-1].numero, Lector[i-1].nombre);

          for(i=0;i<elementosLector;i++)
		{
			fprintf(ptr,":%i:%s:\n", Lector[i].numero, Lector[i].nombre); //Reescribimos el archivo
		}
	fclose(ptr);
        }



}while(correcto==0);





}




