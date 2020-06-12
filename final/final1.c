#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
    int legajo;
    char categoria;
    float sueldo;
}empleado;
int menu();
void crear_archivo(FILE *archivo);
void set_empleado(FILE *archivo);
void show_empleados(FILE *archivo);
void incrementar(FILE *archivo);
void baja_empleado(FILE *archivo);
void main(){
    FILE *archivo;
    int opcion;
    do{
    opcion =menu();
    switch(opcion){
case 1:
    crear_archivo(archivo);
    break;
case 2:
    set_empleado(archivo);
    break;
case 3:
    show_empleados(archivo);
    break;

case 4:
    incrementar(archivo);
    break;
case 5:
    baja_empleado(archivo);
    break;
case 6:
    printf("\n GRACIAS VUELVAS PRONTOS (APUS STORE)\n");
    break;
}
    }while(opcion!=6);

}
void baja_empleado(FILE *archivo){
FILE *temp;
empleado esclavo;
temp = fopen("temp.dat","wb");
int legajo_2 =0;
if((archivo =fopen("empleados.dat","r+b"))==NULL){
 printf("\n no se pudo abrir el archivo");
}else{
    printf("\n Ingrese numero de legajo: ");
    scanf("%d",&legajo_2);
    while(!feof(archivo)){
        if((fread(&esclavo,sizeof(empleado),1,archivo))==1){
                if(esclavo.legajo==legajo_2){
                printf("equals %d y %d",(esclavo.legajo),(legajo_2));
                }else{
                fwrite(&esclavo,sizeof(empleado),1,temp);
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



void crear_archivo(FILE *archivo){
if((archivo =fopen("empleados.dat","wb"))==NULL){
    printf("\nNO se creo con exito el archivo");
}else{
printf("\n Se creo con exito el archivo");
}
fclose(archivo);
}
void set_empleado(FILE *archivo){
    empleado esclavo;
if((archivo =fopen("empleados.dat","a+b"))==NULL){
    printf("\nNO se creo con exito el archivo");
}else{
printf("\n Se creo con exito el archivo\n");
printf("\n Ingrese el numero de legajo");
scanf("%d",&esclavo.legajo);
fflush(stdin);
printf("\n Ingrese categoria:");
scanf("%c",&esclavo.categoria);
fflush(stdin);
printf("\n Ingrese sueldo del empleado");
scanf("%f",&esclavo.sueldo);
fflush(stdin);
fwrite(&esclavo,sizeof(empleado),1,archivo);

}
fclose(archivo);
getchar();

}
void show_empleados(FILE *archivo){
empleado esclavo;
if((archivo =fopen("empleados.dat","rb"))==NULL){
    printf("\ncant open file");
}else{
    printf("\nOpen file");
    printf("\nLegajo \t Categoria \t Sueldo\n");
    while(!feof(archivo)){
        if((fread(&esclavo,sizeof(empleado),1,archivo) ) ==1 ){
            printf("%d \t %c \t\t %.2lf\n",(esclavo.legajo),(esclavo.categoria),(esclavo.sueldo));
        }
    }
}
fclose(archivo);
}
void incrementar(FILE *archivo){
empleado esclavo;
char cat;
float porcentaje ,incremental , new_sueldo;
incremental=0;
new_sueldo=0;
if((archivo =fopen("empleados.dat","r+b"))==NULL){
 printf("\ncant open file");
}else{
    fflush(stdin);
    printf("\n Ingrese categoria :");
    scanf("%c",&cat);
    fflush(stdin);
    printf("\n Ingrese porcentaje :");
    scanf("%f",&porcentaje);
    while((!feof(archivo))){
            incremental=0;
        if((fread(&esclavo,sizeof(empleado),1,archivo))==1 ){
        if (esclavo.categoria== cat){

            incremental= (esclavo.sueldo*(porcentaje/10));
            esclavo.sueldo = (esclavo.sueldo)+incremental;

            fseek(archivo,-sizeof(empleado),SEEK_CUR);
            fwrite(&esclavo,sizeof(empleado),1,archivo);
            fseek(archivo,sizeof(empleado),SEEK_CUR);
        }
        }
    }


}
fclose(archivo);
}












int menu(){
    int opcion;
    printf("\nElige una opcion: \n",162);
    printf("1) Crear el archivo \n");
    printf("2) Guardar empleado \n");
    printf("3) Listar empleados\n");
    printf("4) Incrementar sueldo por categoria \n");
    printf("5) Dar de baja empleado \n");
    printf("6) Salir \n");
    scanf("%d" ,&opcion);
    return opcion;}
