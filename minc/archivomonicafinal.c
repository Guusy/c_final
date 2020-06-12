#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct producto {
    int articulo;
    char marca [30];
    int stock;
    float precio;
    char valido;
};

void crearbin (FILE *archivo){
if ((archivo = fopen( "stock.dar", "w+b"))== NULL)
    printf("no pudo abrirse el archivo. \n");
else {
    printf("archivo creado exitosamente. \n");
    fclose(archivo);
}
getchar();
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
    printf("X) Actualizar archivo elminado bajas de productos \n",161);
    printf("O) Dar de baja logica de un producto \n",162);
    printf("W) ordenar productos \n");
    printf("S) Salir \n");
    scanf("%c" ,&opcion);
    return toupper(opcion);
    }

void guardarDatos (FILE *archivo){
struct producto prod;
archivo=fopen("stock.dat","a+b");
fseek(archivo,0,SEEK_END);
fflush(stdin);
printf("ingrese codigo numerico del articulo: \n",162,130,161);
scanf("%d",&prod.articulo);
fflush(stdin);
printf("ingrese marca del producto: \n");
gets(prod.marca);
fflush(stdin);
printf("ingrese stock ; \n");
scanf("%d",&prod.stock);
fflush(stdin);
while (prod.stock<0){
    printf("El stock de un producto no puede ser un valor negativo, \n por favor ingrese un valor correcto \n");
    printf("ingrese stock: \n");
    scanf("%d",&prod.stock);
}
    printf("ingrese el precio: \n");
    scanf("%f",&prod.precio);
    while(prod.precio<=0){
        printf("el precio del un producto debe ser mayor a cero , introduzca un valor corecto \n");
        printf("ingrese precio \n");
        scanf("%f",&prod.precio);
    }

    prod.valido= ' ';
    fwrite(&prod,sizeof(struct producto),1,archivo);
    fclose(archivo);
    getchar();
}

void emitirDatos (FILE *archivo,int *cantprod) {
    struct producto prod;
    int i=0;
    archivo = fopen("stock.dat","rb");
    fread(&prod,sizeof(struct producto),1,archivo);
    fseek(archivo,0,SEEK_END);
    *cantprod=ftell(archivo)/sizeof (struct producto);
    printf("*** cantidad de articulos almacenados : %d*** \n",161,*cantprod);
    printf("%-10s%-10s%-6s%-6s\n","Articulo","Marca","stock","precio",161);
    while (i<(*cantprod)) {
        fseek(archivo,i*sizeof(struct producto),SEEK_END);
        fread(&prod,sizeof(struct producto),1,archivo);
        printf("%-10d%-10s%3d%10.2lf %c \n",prod.articulo, prod.marca,prod.stock, prod.precio, prod.valido);
        i++;
    }
    fclose(archivo);
    getchar();
}

int leerArt(){
int art;
printf("ingrese codigo numerico del articulo: \n",162,130,161);
scanf("%d",&art);
return art;
}

void buscarProducto (FILE *archivo) {
    struct producto prod;
    int art;
    art=leerArt();
    archivo=fopen("stock.dat","r+b");
    while (!feof(archivo)){
        if (fread(&prod,sizeof(struct producto),1,archivo)==1){
            if (art == prod.articulo){
                printf("Marca: %s \n Articulo: %d\n Stock: %d Precio: %.2f\n",prod.marca,161,prod.articulo,prod.stock,prod.precio);
            }
        }
    }
fclose(archivo);
getchar();
}

void aumentarStock (FILE * archivo){
struct producto prod;
int art,nstock;
archivo=fopen("stock.dat","r+b");
art=leerArt();
printf("ingrese Stock \n");
scanf("%d",&nstock);
while (!feof(archivo)) {
    if (fread(&prod,sizeof(struct producto),1,archivo)==1){
        if (prod.articulo==art){
            prod.stock=prod.stock+nstock;
            fseek(archivo,-sizeof(struct producto),SEEK_CUR);
            fwrite(&prod,sizeof (struct producto),1,archivo);
            fflush(archivo);
        }
    }
}
printf("Stock modificado correctamente \n");
fclose(archivo);
getchar();
}

void decrementarStock (FILE *archivo){
    struct producto prod;
    int art,nstock;
    archivo=fopen("stock.dat","r+b");
    art=leerArt();
    printf("ingrese cantidad a decrementar \n");
    scanf("%d",nstock);
while(!feof(archivo)){
    if (fread(&prod,sizeof(struct producto),1,archivo)==1){
        if (prod.articulo==art){
            prod.stock = prod.stock - nstock;
            fseek(archivo,-sizeof(struct producto),SEEK_CUR);
            fwrite(&prod,sizeof (struct producto),1,archivo);
            fflush(archivo);
            }
        }
    }
printf("Stock Modificado correctamente \n");
fclose(archivo);
getchar();

}

void modificarPrecio (FILE *archivo){
    int art;
    float nuevoPrecio,temporal;
    art=leerArt();
    struct producto prod;
    FILE *temp;
    printf("ingrese nuevo precio \n");
    scanf("%f",&nuevoPrecio);
    while(nuevoPrecio<=0){
        printf("El precio Debe ser mayor a 0 , ingrese nuevamente \n");
        printf("ingrese nuevo precio \n");
        scanf("%f",&nuevoPrecio);
}
    archivo=fopen("stock.dat","r+b");
    temp=fopen("stock.temp","wb");
    fseek(archivo,0,SEEK_SET);
    while (fread(&prod,sizeof (struct producto),1,archivo)){
        if (prod.articulo==art){
            prod.precio=nuevoPrecio;
        }
        fwrite(&prod,sizeof (struct producto),1,temp);
    }
    fclose(archivo);
    fclose(temp);
    remove("stock.bkp");
    rename("stock.dat","stock.bkp");
    rename("stock.temp","stock.dat");
    printf("\n***--Precio Modificado correctamente \n--***");
    system("pause");

}
void bajaLogica(FILE *archivo){
int art;
struct producto prod;
art=leerArt();
printf("\n articulo leido es: %d",art);
archivo=fopen("stock.dat","r+b");
while (!feof(archivo)){
    if(fread(&prod,sizeof(struct producto),1,archivo)==1){
        if (art==prod.articulo){
            prod.valido='N';
            fseek(archivo,sizeof(struct producto),SEEK_CUR);
            fwrite(&prod,sizeof(struct producto),1,archivo);
            fflush(archivo);
        }
    }
}
fclose(archivo);
printf("\n***--El producto %d se dio de baja correctamente--***\n");
getchar();
}

void bajaFisica (FILE *archivo){
FILE *temp;
struct producto prod;
archivo = fopen("stock.dat","rb");
temp= fopen("stock.temp","w+b");
rewind(archivo);
while (fread(&prod,sizeof(struct producto),1,archivo)){
    if (prod.valido==' '){
        fwrite(&prod,sizeof (struct producto),1,temp);
    }
}
fclose(temp);
fclose(archivo);
remove("stock.bkp");
rename("stock.dat","stock.bkp");
rename("stock.temp","stock.dat");
printf("\n ***-- Archivo Actualizado--*** \n");
}
int main(){
    char opcion;
    int i;
    int cantprod;
    FILE *archivo;
    do {
            opcion=menu();
            switch(opcion){
            case ' Crear Binario ':crearbin(archivo);
                break;
            case ' Guardar datos ':
                guardarDatos(archivo);
                break;
            case 'E':emitirDatos(archivo,&cantprod);
                break;
            case 'B':buscarProducto(archivo);
                break;
            case 'A': aumentarStock(archivo);
            break;
            case 'D':decrementarStock(archivo);
            break;
            case ' M':
                modificarPrecio(archivo);
                break;
            case ' Bfisica':
                bajaFisica(archivo);
                break;
            case 'baja logica':
                bajaLogica(archivo);
                break;
            case 'ordenar':
                ordenar (archivo);
                break;
            }
        }while (opcion!=3);
}
