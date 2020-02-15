#ifndef BASE_DATOS_H
#define BASE_DATOS_H
#define MAX_LON_TIT 80
#define MAX_LON_TIP 1
#define MAX_LON_OP 80
#define MAX_LON_NOM 50



//LAS DOS ESTRUCTURAS

struct sLector //Estructura lector
{
int numero;
char nombre[MAX_LON_NOM+1];

};

struct sRef                  //Estructura referencia
{
char nombre [MAX_LON_NOM+2];
char titulo [MAX_LON_TIT+2];
char tipo [MAX_LON_TIP+2];
int anho;
int votantes;
long votos;
int criticos;
int lector[50]; //
char opinion [MAX_LON_OP+2][50]; //50 numero de comentarios maximo
long signatura;

};


//FUNCION BASEDATOS

int baseDatos(struct sLector *Lector, int *i, struct sRef *Ref, int *j);

//FUNCIONES LECTOR

int numLector();
int compNom(char nombre[]);
int lector(struct sLector *Lector, int numero);


//FUNCIONES AGREGAR REFERENCIA

void referencia(struct sRef *Ref, int elementosRef);
int compAnho(int anho);


//FUNCIONES AGREGAR OPINION

void opinion(struct sRef *Ref, int elementosRef, struct sLector *Lector, int elementosLector);


//FUNCIONES OBTENER INFORME

void informa(struct sRef *Ref, int elementosRef, struct sLector *Lector, int elementosLector);

//FUNCIONES EMITIR VOTO

void voto(struct sRef *Ref, int elementos);
int compvoto(int voto);


//FUNCIONES CALCULAR NOTA MEDIA

void nota(struct sRef *Ref, int elementosRef);

//FUNCIONES LISTAR REFERNCIA

void listar(struct sRef *Ref, int elementosRef);

//FUNCIONES BUSCAR REFERENCIA

void buscar(struct sRef *Ref, int elementosRef,struct sLector *Lector, int elementosLector);

//FUNCIONES CAMBIAR LECTOR

void cambiar(struct sLector *Lector, int elementosLector);



#endif





