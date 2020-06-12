#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int articulo;
    char marca [30];
    int stock;
    float precio;
    char valido;
}producto;
int menu ();
void CrearArch(FILE *archivo);
void Guardar_pdr(FILE *archivo);
void buscar_pdr(FILE *archivo);
int leerArt();
void aumentar_stock(FILE *archivo);
void decrementar_stock(FILE *archivo);
void change_price(FILE *archivo);
void baja_fisica_pdr(FILE *archivo);
void baja_logica(FILE *archivo);
void burbujeo (FILE *archivo);
void main(){
char opcion;
FILE *archivo;
do{
   opcion = menu();

switch(opcion){
 case 'C':
     CrearArch(archivo);

     break;
 case 'G':
     Guardar_pdr(archivo);

    break;
 case 'E':
     Listar_pdr(archivo);

    break;
 case 'B':
     buscar_pdr(archivo);

    break;
 case 'A':
    aumentar_stock(archivo);
    break;
 case 'D':
    decrementar_stock(archivo);
    break;
 case 'P':
    change_price(archivo);
    break;
 case 'X':
     baja_fisica_pdr(archivo);
    break;
 case 'O':
     baja_logica(archivo);
    break;
 case 'W':
    burbujeo(archivo);
    break;

}
}while(opcion!='S');



}
int leerArt(){
int art;
printf("\nIngrese codigo numerico del articulo: \n",162,130,161);
scanf("%d",&art);
return art;
}


void burbujeo (FILE *archivo){
    printf("i m in¡?");
FILE *temp;
producto struct_aux1;
producto pdr;
temp = fopen("temp.dat","wb");
if((archivo = fopen("datos.dat","r+b"))==NULL ){

    printf("\nNo se pudo abrir el archivo");
}else{

    while(!feof(archivo)){

        if(( fread(&pdr,sizeof(producto),1,archivo) )==1){

        struct_aux1 = pdr;
        fread(&pdr,sizeof(producto),1,archivo);

        if(pdr.articulo > struct_aux1.articulo){

                fwrite(&pdr,sizeof(producto),1,temp);
                fwrite(&struct_aux1,sizeof(producto),1,temp);

        }else{
                fwrite(&struct_aux1,sizeof(producto),1,temp);
                fwrite(&pdr,sizeof(producto),1,temp);
        }

        }

    }

}
fclose(temp);
fclose(archivo);
remove("datos.bkp");
rename("datos.dat","datos.bkp");
rename("temp.dat","datos.dat");
printf("\nSe burbujeo exitosamente\n");


}


void baja_fisica_pdr(FILE *archivo){
    FILE *temp;
    producto pdr;

temp = fopen("temp.dat","wb");
if ( (archivo = fopen("datos.dat","r+b"))==NULL ){
    printf("no se pudo abrir con exito el archivo");
}else{

    while(!feof(archivo)){
        if(fread(&pdr,sizeof(producto),1,archivo)==1){
            if(pdr.valido=='N'){

            }else{
               fwrite(&pdr,sizeof(producto),1,temp);
            }

        }

    }





}
fclose(temp);
fclose(archivo);
remove("datos.bkp");
rename("datos.dat","datos.bkp");
rename("temp.dat","datos.dat");
printf("Se dio una baja fisica exitosamente");

}
void baja_logica(FILE *archivo){
producto pdr;
FILE *temp;
int number_search ;
temp = fopen("temp.dat","wb");
if ( (archivo = fopen("datos.dat","r+b"))==NULL ){
     printf("\nNo se pudo abrir el archivo");
}else{
    number_search = leerArt();
    fflush(stdin);
    while(!feof(archivo)){
        if((fread(&pdr,sizeof(producto),1,archivo))==1 ){
        if(pdr.articulo == number_search){
            pdr.valido = 'N';
        }
        //fseek(archivo,-sizeof(producto),SEEK_CUR);
        fwrite(&pdr,sizeof(producto),1,temp);
    }
}

}

fclose(archivo);
fclose(temp);
remove("datos.bkp");
rename("datos.dat","datos.bkp");
rename("temp.dat","datos.dat");
printf("Se dio una baja logica exitosamente");

getchar();
}
void change_price(FILE *archivo){
producto pdr;
FILE *temp;
int number_search ;
float modify_price;
if ( (archivo = fopen("datos.dat","r+b"))==NULL ){
    printf("\nNo se pudo abrir el archivo");
}else{
    printf("\nSe pudo abrir el archivo");
    temp = fopen("temp.dat","wb");
    number_search = leerArt();
    fflush(stdin);
     printf("ingrese nuevo precio \n");
    scanf("%f",&modify_price);

    fseek(archivo,0,SEEK_SET);
    while(!feof(archivo)){
        if( (fread(&pdr,sizeof(producto),1,archivo))==1){
            if(pdr.articulo == number_search){
            printf("\n Su producto es :");
            printf("\n%d\t%s\t%d\t%f\t%c \n",(pdr.articulo),(pdr.marca),(pdr.stock),(pdr.precio),(pdr.valido));
            pdr.precio= modify_price;
            //fseek(archivo,-sizeof(producto),SEEK_CUR);
            printf("\n Su producto modificado es :");
            printf("\n%d\t%s\t%d\t%f\t%c \n",(pdr.articulo),(pdr.marca),(pdr.stock),(pdr.precio),(pdr.valido));

            }
            fwrite(&pdr,sizeof(producto),1,temp);
        }
    }


}

fclose(archivo);
fclose(temp);
remove("datos.bkp");
rename("datos.dat","datos.bkp");
rename("temp.dat","datos.dat");
printf("\n***--Precio Modificado correctamente \n--***");
getchar();


}

void buscar_pdr(FILE *archivo){
    int art;
    producto pdr;
 if((archivo =fopen("datos.dat","rb"))==NULL){
     printf("\n No se pudo ingresar al archivo");
}else{
    art = leerArt();
    printf("\nNumero\tMarca\tStock\tPrecio\tValido ");
    fread(&pdr,sizeof(producto),1,archivo);
    while(!feof(archivo)){
    if(pdr.articulo == art){
    printf("\n%d\t%s\t%d\t%f\t%c \n",(pdr.articulo),(pdr.marca),(pdr.stock),(pdr.precio),(pdr.valido));
    }
    fread(&pdr,sizeof(producto),1,archivo);

    }

    }
 fclose(archivo);
 getchar();

}
void decrementar_stock(FILE *archivo){
    producto pdr;
    int art,cant_stock;

if((archivo =fopen("datos.dat","r+b"))==NULL){
     printf("\n No se pudo ingresar al archivo");
}else{
    art = leerArt();
    printf("\nIngrese stock a restare :");
    fflush(stdin);
    scanf("%d",&cant_stock);
    fflush(stdin);

    while(!feof(archivo)){
            if((fread(&pdr,sizeof(producto),1,archivo))==1){
              if(pdr.articulo == art){
    printf("\n%d\t%s\t%d\t%f\t%c \n",(pdr.articulo),(pdr.marca),(pdr.stock),(pdr.precio),(pdr.valido));
    pdr.stock = (pdr.stock) - cant_stock;
    fseek(archivo,-sizeof(producto),SEEK_CUR);
    fwrite(&pdr,sizeof(producto),1,archivo);
    fflush(archivo);
     printf("Articulo modificado\n%d\t%s\t%d\t%f\t%c \n",(pdr.articulo),(pdr.marca),(pdr.stock),(pdr.precio),(pdr.valido));
    }
            }

    }


    printf("\n Se ingreso a el archivo correctamente");
}
fclose(archivo);
getchar();

}
void aumentar_stock(FILE *archivo){
    producto pdr;
    int art,cant_stock;

if((archivo =fopen("datos.dat","r+b"))==NULL){
     printf("\n No se pudo ingresar al archivo");
}else{
    art = leerArt();
    printf("\nIngrese stock a sumar :");
    fflush(stdin);
    scanf("%d",&cant_stock);
    fflush(stdin);

    while(!feof(archivo)){
            if((fread(&pdr,sizeof(producto),1,archivo))==1){
              if(pdr.articulo == art){
    printf("Articulo sin modificar:\n%d\t%s\t%d\t%f\t%c \n",(pdr.articulo),(pdr.marca),(pdr.stock),(pdr.precio),(pdr.valido));
    pdr.stock = (pdr.stock) + cant_stock;
    fseek(archivo,-sizeof(producto),SEEK_CUR);
    fwrite(&pdr,sizeof(producto),1,archivo);
    fflush(archivo);
     printf("Articulo modificado:\n%d\t%s\t%d\t%f\t%c \n",(pdr.articulo),(pdr.marca),(pdr.stock),(pdr.precio),(pdr.valido));
    }
            }




    }


    printf("\n Se ingreso a el archivo correctamente");
}
fclose(archivo);
getchar();

}
void Listar_pdr(FILE *archivo){
    producto pdr;
 if((archivo =fopen("datos.dat","rb"))==NULL){
     printf("\n No se pudo ingresar al archivo");
}else{
    printf("\nNumero\tMarca\tStock\tPrecio\tValido ");
    fread(&pdr,sizeof(producto),1,archivo);
    while(!feof(archivo)){
    printf("\n%d\t%s\t%d\t%f\t%c",(pdr.articulo),(pdr.marca),(pdr.stock),(pdr.precio),(pdr.valido));
    fread(&pdr,sizeof(producto),1,archivo);

    }


    printf("\n Se ingreso a el archivo correctamente");
}
fclose(archivo);
getchar();

}

void Guardar_pdr(FILE *archivo){
 producto struct_pdr;
    if((archivo =fopen("datos.dat","a+b"))==NULL){
     printf("\n No se pudo ingresar al archivo");
}else{

    printf("\n Se ingreso a el archivo correctamente");
}
fseek(archivo,0,SEEK_END);// me posiciono al final del archivo
printf("\ningrese numero de articulo: ");
scanf("%d",&struct_pdr.articulo);
printf("\ningrese la marca: ");
scanf("%s",&struct_pdr.marca);
printf("\ningrese cantidad de stock: ");
scanf("%d",&struct_pdr.stock);
printf("\ningrese precio: ");
scanf("%f",&struct_pdr.precio);
printf("\ningrese si es valido o no : ");
fflush(stdin);
scanf("%c",&struct_pdr.valido);

fwrite(&struct_pdr,sizeof(producto),1,archivo);






fclose(archivo);
getchar();
}
void CrearArch(FILE *archivo){

if((archivo =fopen("datos.dat","w+b"))==NULL){
        printf("\n No se pudo crear el archivo");

}else{
    printf("\n Se creo el archivo correctamente");
}
fclose(archivo);
}

int menu () {
    char opcion;
    printf("Elige una opcion: \n",162);
    printf("C) Crear el archivo \n");
    printf("G) Guardar producto \n");
    printf("E) Listar productos \n");
    printf("B) Buscar producto \n");
    printf("A) Aumentar Stock \n");
    printf("D) Decrementar stock \n");
    printf("P) Modificar Precio \n");
    printf("X) Baja fisica \n",161);
    printf("O) Dar de baja logica de un producto \n",162);
    printf("W) ordenar productos \n");
    printf("S) Salir \n");
    scanf("%c" ,&opcion);
    return toupper(opcion);
    }
