#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
int numero;
char descripcion[30];
float temp1,temp2,temp3;
int validar;
}zona;
void max_zona(FILE *archivo);
int menu();
void guardar_zona(FILE *archivo);
void list_zona(FILE *archivo);
void modify_temp(FILE *archivo);

void main(){
FILE *archivo;
int opcion;
do{
    opcion= menu();
    switch(opcion){
    case 1:
        guardar_zona(archivo);
                break;
    case 2:
        list_zona(archivo);
        break;
    case 3:
        modify_temp(archivo);
        break;
    case 4:
        max_zona(archivo);
        break;
    }
}while(opcion!=6);
}
void guardar_zona(FILE *archivo){
zona plaza;
if((archivo = fopen("zonas.dat","a+b"))==NULL){
printf("\nCan't open file\n");
}else{
    printf("\nIngrese numero: ");
    scanf("%d",&plaza.numero);
    fflush(stdin);
    printf("\nIngre descripcion: ");
    scanf("%s",plaza.descripcion);
    fflush(stdin);
    printf("\nIngrese temperatura 1: ");
    scanf("%f",&plaza.temp1);
    fflush(stdin);
    printf("\n Ingrese temperatura 2: ");
    scanf("%f",&plaza.temp2);
    fflush(stdin);
    printf("\n Ingrese temperatura 3: ");
    scanf("%f",&plaza.temp3);
    fflush(stdin);
    plaza.validar=1;

    fwrite(&plaza,sizeof(zona),1,archivo);

}
fclose(archivo);
}
void max_zona(FILE *archivo){
zona plaza;
zona plaza_max;
plaza_max.temp1= 999;
plaza_max.temp2= 999;
plaza_max.temp3= 999;
if (( archivo = fopen("zonas.dat","rb"))==NULL){
         printf("\nCant open file\n");
         }else{

             while(!feof(archivo)){
                if((fread(&plaza,sizeof(zona),1,archivo)==1){
                    if(){

                   }
                }
             }


         }

}
void list_zona(FILE *archivo){
    zona plaza;
    if (( archivo = fopen("zonas.dat","rb"))==NULL){
         printf("\nCant open file\n");
         }else{
             printf("\nZona\tDescripcion\ttemp1\ttemp2\ttemp3 \n");
         while(!feof(archivo)){
            if((fread(&plaza,sizeof(zona),1,archivo))==1){
                    if(plaza.validar==1){
                printf("\n%d\t%s\t\t%.2lf\t%.2lf\t%.2lf \n",(plaza.numero),(plaza.descripcion),(plaza.temp1),(plaza.temp2),(plaza.temp3));
                }
            }
         }
         }
fclose(archivo);
getchar();
}
void modify_temp(FILE *archivo){
    FILE *lista;
    zona plaza;
    int numero,temp;
    float new_temp;

    if((archivo = fopen("zonas.dat","r+b"))==NULL){
        printf("\nCan't open file\n");
}else{
    printf("Lista de zonas \n");
    list_zona(lista);
    printf("\n Ingrese numero de zona a modificar temperatura :");
    scanf("%d",&numero);
    fflush(stdin);
    printf("\nIngrese numero de temperatura a modificar: ");
    scanf("%d",&temp);
    fflush(stdin);
    printf("\nIngrese nueva de temperatura : ");
    scanf("%f",&new_temp);
    switch(temp){}
    while(!feof(archivo)){
        if((fread(&plaza,sizeof(zona),1,archivo))==1){
                if(plaza.numero==numero){
                 switch(temp){
            case 1:
                plaza.temp1 = new_temp;
                break;
            case 2:
                plaza.temp2 = new_temp;
                break;
            case 3:
                plaza.temp3 = new_temp;
                break;

            }
            fseek(archivo,-sizeof(zona),SEEK_CUR);
            fwrite(&plaza,sizeof(zona),1,archivo);
            fseek(archivo,sizeof(zona),SEEK_CUR);
                }


        }
    }



}
fclose(archivo);
getchar();

}
int menu(){
    int opcion;
    printf("\nElige una opcion: \n",162);
    printf("1) Guardar zona \n");
    printf("2) Listar zonas \n");
    printf("3) Modificar temperaturas\n");
    printf("4) Mayor temperatura \n");
    printf("5) Dar de baja zona \n");
    printf("6) Salir \n");
    scanf("%d" ,&opcion);
    return opcion;}
