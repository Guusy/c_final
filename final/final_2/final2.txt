#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
    int legajo;
    char categoria;
    int fecha[3];
    char funcion[10];
    float sueldo;
}empleado_;
int menu();
void crear_archi(FILE *archivo);
void guardar_datos(FILE *archivo);
void emitir_datos(FILE *archivo);
void incrementar_by_cat(FILE *archivo);
void max_min_sueldo(FILE *archivo);
void empleado_old(FILE *archivo);
void baja_emp(FILE *archivo);
void main(){
    FILE *archivo;
    int opcion;
do{
    opcion =menu();
    switch(opcion){
    case 0:
        //crear_archi(archivo);
        break;
case 1:
    guardar_datos(archivo);
    break;
case 2:
     emitir_datos(archivo);
    break;
case 3:
    incrementar_by_cat(archivo);
    break;
case 4:
    max_min_sueldo(archivo);
    break;
case 5:
    empleado_old(archivo);
    break;
case 6:
    baja_emp(archivo);
    break;

    }
}while(opcion!=7);

}
int menu(){
    int opcion;
    printf("\nElige una opcion: \n",162);

    printf("1) Guardar empleado \n");
    printf("2) Listar empleados\n");
    printf("3) Incrementar sueldo por categoria \n");
    printf("4) Mayor y menor sueldo \n");
    printf("5) Empleado mas viejo y la funcion \n");
    printf("6) Dar de baja empleado \n");
    printf("7) Salir \n");
    scanf("%d" ,&opcion);
    return opcion;}

void baja_emp(FILE *archivo){
FILE *temp;
empleado_ esclavo;
temp = fopen("temp.dat","wb");
int legajo_2 =0;
if((archivo =fopen("empleados.dat","r+b"))==NULL){
 printf("\n no se pudo abrir el archivo");
}else{
    printf("\n Ingrese numero de legajo: ");
    scanf("%d",&legajo_2);
    while(!feof(archivo)){
        if((fread(&esclavo,sizeof(empleado_),1,archivo))==1){
                if(esclavo.legajo==legajo_2){
                }else{
                fwrite(&esclavo,sizeof(empleado_),1,temp);
                }

        }
    }

}
fclose(archivo);
fclose(temp);
remove("empleados.bkp");
rename("empleados.dat","empleados.bkp");
rename("temp.dat","empleados.dat");
printf("\nSe realizo con exito su baja !");
}
void empleado_old(FILE *archivo){
empleado_ esclavo;
empleado_ old;
int cont=0;
old.fecha[0]= 32;
old.fecha[1]= 13;
old.fecha[2]= 2017;
if( (archivo = fopen("empleados.dat","rb")) ==NULL ){
     printf("\ncan't open file\n");
}else{
    while(!feof(archivo)){
        if((fread(&esclavo,sizeof(empleado_),1,archivo))==1){

            if((esclavo.fecha[2])<(old.fecha[2])){
                old= esclavo;

            }else{
                if((esclavo.fecha[2])==(old.fecha[2])){

                    if((esclavo.fecha[1]) == (old.fecha[1])){
                        if((esclavo.fecha[0]) < (old.fecha[0])){
                        old= esclavo;

                        }
                    }else{

                        if((esclavo.fecha[1]) < (old.fecha[1])){

                            old= esclavo;
                            printf("estoy 2do if");

                    }

                    }
                }else{

                    //printf("\n 3era fecha :%d/%d/%d y old : %d/%d/%d",(esclavo.fecha[0]),(esclavo.fecha[1]),(esclavo.fecha[2]),(old.fecha[0]),(old.fecha[1]),(old.fecha[2]));
                    if((esclavo.fecha[1]) < (old.fecha[1])){
                          if((esclavo.fecha[0]) < (old.fecha[0])){
                            old= esclavo;

                        }
                    }

                }
                }

            cont++;

            } // fread


        }
    }

printf("El empleado mas viejo es %d y ingreso el %d/%d/%d y su funcion es %s \n",old.legajo,old.fecha[0],old.fecha[1],old.fecha[2],old.funcion);
fclose(archivo);
getchar();

}


void max_min_sueldo(FILE *archivo){
empleado_ esclavo;
empleado_ esclavo_min;
empleado_ esclavo_max;
esclavo_min.sueldo= 9999;
esclavo_max.sueldo= -9999;

if( (archivo = fopen("empleados.dat","rb")) ==NULL ){
     printf("\ncan't open file\n");
}else{
    while(!feof(archivo)){
            if((fread(&esclavo,sizeof(empleado_),1,archivo))==1){
                if(esclavo.sueldo> esclavo_max.sueldo){
                    esclavo_max = esclavo;
                }
                if((esclavo.sueldo)< esclavo_min.sueldo){
                    esclavo_min = esclavo;
                }
            }

    }
    printf("\nEl numero de legajo minimo es %d y su sueldo % .2lf", esclavo_min.legajo,esclavo_min.sueldo);
    printf("\nEl numero de legajo maximo es %d y su sueldo % .2lf",esclavo_max.legajo,esclavo_max.sueldo);
}
fclose(archivo);
getchar();
}

void incrementar_by_cat(FILE *archivo){
empleado_ esclavo;
char cat;
float porcentaje,porcentual;
porcentual=0;
porcentaje=0;
if( (archivo = fopen("empleados.dat","r+b")) ==NULL ){
     printf("\ncan't open file\n");
}else{
    fflush(stdin);
    printf("\nIngrese la categoria a aumentar: ");
    scanf("%c",&cat);
    fflush(stdin);
    printf("\nIngrese el porcentaje a subir: ");
    scanf("%f",&porcentaje);
    fflush(stdin);
    while(!feof(archivo)){
        if((fread(&esclavo,sizeof(empleado_),1,archivo))==1){
            if(esclavo.categoria== cat){
            porcentual = (esclavo.sueldo*(porcentaje/10));
            esclavo.sueldo= esclavo.sueldo + porcentual;
            fseek(archivo,-sizeof(empleado_),SEEK_CUR);
            fwrite(&esclavo,sizeof(empleado_),1,archivo);
            fseek(archivo,sizeof(empleado_),SEEK_CUR);
            printf("\n Se modifico con exito");
            }
        }


    }
}

fclose(archivo);
getchar();
}

void guardar_datos(FILE *archivo){
    empleado_ esclavo;
if( (archivo = fopen("empleados.dat","a+b")) ==NULL ){
    printf("\ncan't open file\n");
}else{
printf("\nIngrese legajo: \n");
scanf("%d",&esclavo.legajo);
fflush(stdin);
printf("\nIngrese categoria: \n");
scanf("%c",&esclavo.categoria);
fflush(stdin);
printf("\nIngrese fecha separada con enters :\n");
scanf("%d",&esclavo.fecha[0]);
fflush(stdin);
scanf("%d",&esclavo.fecha[1]);
fflush(stdin);
scanf("%d",&esclavo.fecha[2]);
fflush(stdin);
printf("\nIngrese funcion: \n");
scanf("%s",esclavo.funcion);
fflush(stdin);
printf("\nIngrese Sueldo: \n");
scanf("%f",&esclavo.sueldo);
fflush(stdin);
fwrite(&esclavo,sizeof(empleado_),1,archivo);
}
fclose(archivo);
}
void emitir_datos(FILE *archivo){
empleado_ esclavo;
    if( (archivo = fopen("empleados.dat","rb")) ==NULL ){
printf("\ncan't open file\n");
    }else{
        printf("\nLegajo\tCategoria\tFecha\tFuncion\tSueldo\n");
        while(!feof(archivo)){
                if((fread(&esclavo,sizeof(empleado_),1,archivo))==1){
                    printf("\n%d\t%c\t\t%d/%d/%d\t%s\t%.2lf\n",(esclavo.legajo),(esclavo.categoria),(esclavo.fecha[0]),(esclavo.fecha[1]),(esclavo.fecha[2]),(esclavo.funcion),(esclavo.sueldo));
                }

        }
    }
fclose(archivo);
}
