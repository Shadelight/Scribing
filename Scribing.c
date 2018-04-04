//==================================================== archivo = Scribing.c ====
//= Scribing - Editor de texto                                                 =
//==============================================================================
//   Scribing es un n  simple editor de texto con la opción de poder corregir  =
//   palabras con mala ortografía y la capacidad para crear y modificar        =
//   archivos de tipo .odt ó txt.                                              =
//   Proyecto de la asignatura: Técnica de Programación 1                      =                                   =
//==============================================================================
//----- Librerias Incluidas ----------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----- Constantes definidas ---------------------------------------------------
#ifdef _WIN32
#define  limpiar  system("cls");
#endif

#ifdef linux
#define limpiar   system("clear");
#endif

//----- Variables globales -----------------------------------------------------
char ruta_dicc[] = "Diccionario.txt";
char ruta_asccii[] = "Ascii.txt";
char ruta_leame[] = "Léame.md";
FILE *pntr_leame;
FILE *pntr_asccii;
FILE *puntr_dicc;
FILE *nuevo_arch;
FILE *abrir_arch;
int opcion;
char caracter;

//----- Prototipos de función 
void ascii_art();
void menu();
void op_menu(int);
void menu_archivo();
void nuevo_archivo();
void abiri_archivo();
void corrector();
void corregir_texto();
void cargar_archivo();
void menu_diccionario();
void add_dicc();
void ver_diccionario();
void Leame();

//----- Programa principal -----------------------------------------------------
int main() { 
	do { 
		menu();
		scanf("%d", &opcion);
		while (getchar() != '\n');
		op_menu(opcion);
	} while(opcion != 5);

	return 0;
}

//----- Cabecera ascii ---------------------------------------------------------
void ascii_art() {
	// definir
	pntr_asccii = fopen(ruta_asccii,"r");
	if (pntr_asccii == NULL) {
    	printf("\nError al cargar la cabecera (%s) ascii del programa. \n\n", ruta_asccii);
    } 
    else {
    	// imprimir por pantalla los caracteres del archivo cabecera
    	while((caracter = fgetc(pntr_asccii)) != EOF) {
            printf("%c", caracter);
        }
    //fclose(pntr_asccii);
    }
}

//----- Menu principal ---------------------------------------------------------
void menu() {
	limpiar;
	ascii_art();
	printf("Menu Principal\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("1. Archivo  |  2. Corrector | 3. Diccionario |  4. Acerca de   |  5. Salir\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("\n>> ");
}

//----- Opciones del menu principal --------------------------------------------
void op_menu(int op) {
	switch(op) { 
			case 1: menu_archivo(); 	break;
			case 2: corrector(); 		break;
			case 3: menu_diccionario(); break;
			case 4: Leame(); getchar(); break;
			case 5:	/* salir */		    break;
		} 
}

//----- Menu Archivo -----------------------------------------------------------
void menu_archivo() {
	do { 
		limpiar;
		ascii_art();
		printf("Menu Archivo\n");
		printf("--------------------------------------------------------------------------------\n");
		printf("1. Nuevo  |  2. Abrir  |  3. Regresar  \n");
		printf("--------------------------------------------------------------------------------\n");
		printf("\n>> ");
		scanf("%d", &opcion);
		while (getchar() != '\n');
		
		switch(opcion) {
			case 1: nuevo_archivo(); getchar(); break;
			case 2: abiri_archivo(); getchar(); break;
			case 3: /* regresar */              break;
			default:
				printf("Opcion incorrecta.\n");
				break;
		}	
	} while( opcion != 3);
}

//----- Crear nuevo archivo ----------------------------------------------------
void nuevo_archivo() {
	limpiar;
	ascii_art();
	FILE *temporal;
	
	char letras, nombre[60], tipo[6], nom_compl[100];
	temporal = fopen("temporal.txt","w");

	printf("Nuevo archivo\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("Ingrese el contenido para su archivo\n");
	printf("(pulse ENTER para guardar)\n");
	printf("--------------------------------------------------------------------------------\n");
 	printf("\n~ ");
 	// escribir datos en archivo temporal hasta pulsar enter
	while((letras = getchar()) != '\n')
 	{ 
		fputc(letras, temporal); 
	}
	limpiar;
	ascii_art();
	printf("Nuevo archivo\n");
	printf("--------------------------------------------------------------------------------\n");
 	printf(">> Gurdar Como:\n");
	printf("--------------------------------------------------------------------------------\n");
 	printf("\nNombre >> ");
 	//leer nombre
 	fgets(nombre, sizeof(nombre), stdin);
 	// eliminar espacio capturado en fgets
	nombre[strlen(nombre) - 1] = '\0';
 	printf("\n\nTipo (.txt o .odt) >> ");
 	// leer la extencion
 	fgets(tipo, sizeof(tipo), stdin);
 	// eliminar espacio capturado en fgets
	tipo[strlen(tipo) - 1] = '\0';

 	// concatenar nombre + tipo
    strcpy( nom_compl, nombre );
    strcat( nom_compl, tipo );
    // definir nuevo archivo con la concatenacion
    nuevo_arch = fopen(nom_compl,"w");
    // cerrar temporal para reabrirlo mas tarde
	fclose(temporal);

    if(nuevo_arch == NULL) {
    	limpiar;
    	ascii_art();
    	printf("Nuevo archivo\n");
    	printf("--------------------------------------------------------------------------------\n");
		printf("\nNo se pudo crear el archivo . . .");
		printf("--------------------------------------------------------------------------------\n");
	}
	else {
		// reabrir temporal, pero ahora en modo lectura
		temporal = fopen("temporal.txt", "r");
		// copiar contenido de temporal al nuevo archivo
		while((caracter=fgetc(temporal))!=EOF && !ferror(temporal) && !ferror(nuevo_arch))
		fputc(caracter,nuevo_arch);
    	limpiar;
		ascii_art();
		printf("Nuevo archivo:\n");
		printf("--------------------------------------------------------------------------------\n");
 		printf(">> Gurdar Como\n");
		printf("--------------------------------------------------------------------------------\n");

		printf("\nEl archivo (%s) ha sido creado y guardado con exito . . .", nom_compl);
		// cerrar los archivos
		fclose(temporal);
		fclose(nuevo_arch);
		// eliminar archivo temporal
		remove("temporal.txt");
    }

}
//----- Leer un archivo --------------------------------------------------------
void abiri_archivo() {
	limpiar;
	ascii_art();
	
	char  nombre[60], tipo[6], nom_compl[100];
	
	printf("Abrir Archivo\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("Ingrese el nombre y luego el tipo del archivo que desea abrir:\n");
	printf("--------------------------------------------------------------------------------\n");	
	printf("\nNombre:\n");
 	printf(">> ");
 	fgets(nombre, sizeof(nombre), stdin);
	nombre[strlen(nombre) - 1] = '\0';
 	printf("\n\nTipo: \n");
 	printf("(.txt o .odt)\n");
 	printf(">> ");
 	fgets(tipo, sizeof(tipo), stdin);
	tipo[strlen(tipo) - 1] = '\0';

 	// Concatenar el nombre del archivo con el tipo
    strcpy( nom_compl, nombre );
    strcat( nom_compl, tipo );
    // abrir archivo en modo lectura
    abrir_arch = fopen(nom_compl,"r");

	if(abrir_arch == NULL) {
		limpiar;
		ascii_art();
		printf("Nuevo Archivo\n");
		printf("--------------------------------------------------------------------------------\n");
		printf("No se pudo abrir el archivo . . .");
		printf("--------------------------------------------------------------------------------\n");
	}
	else {
		limpiar;
		ascii_art();
		printf(">> %s\n", nom_compl);
		printf("--------------------------------------------------------------------------------\n");
		printf("(pulse ENTER para regresar)\n");
		printf("--------------------------------------------------------------------------------\n");
		printf("\n~ ");
		// imprimir caracter a caracter los datos del archivo
        while((caracter = fgetc(abrir_arch)) != EOF) {
			printf("%c",caracter);
	    }

		fclose(abrir_arch);
	}
}

//----- Corrector Ortografico -----------------------------------------------------
void corrector() {
		do{ 
		limpiar;
		ascii_art();
		printf("Corrector Ortografico\n");
		printf("--------------------------------------------------------------------------------\n");
		printf("1. Abrir Archivo  |  2. Regresar\n");
		printf("--------------------------------------------------------------------------------\n");
		printf("\n>> ");
		scanf("%d", &opcion);
		while (getchar() != '\n');

		switch(opcion) {
			case 1:
				limpiar;
				ascii_art();
				corregir_texto();
				getchar();
				break;
			case 2:
				break;
			default:
				printf("Opcion incorrecta.\n");
				break;
		}	
	} while( opcion != 2);
	
}

// corrector ortografico
void corregir_texto() {
	printf("Corrector Ortografico\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("Funcion en desarrollo . . .\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("\n>> ");
}



void menu_diccionario(){
	do{
		limpiar;
		ascii_art();
		printf("Menu Diccionario\n");
		printf("--------------------------------------------------------------------------------\n");
		printf("1. Añadir palabras  |  2. Ver Diccionario  |  3. Regresar\n");
		printf("--------------------------------------------------------------------------------\n");
		printf("\n>> ");
		scanf("%d", &opcion);
		while (getchar() != '\n');

		switch(opcion)
		{
			case 1:
				limpiar;
				ascii_art();
				add_dicc();
				getchar();
				break; 
			case 2:
				limpiar;
				ascii_art();
				ver_diccionario();
				getchar();
				break;
			case 3: 
				break;
			default:
				printf("Opcion incorrecta.\n");
				getchar(); 
				break;
		}
	}while(opcion !=3);
}

// añadir palabras al diccionario
void add_dicc(){
	puntr_dicc = fopen(ruta_dicc,"at"); //modo agregar texto

	if (puntr_dicc == NULL)
    {
    	printf("Menu Diccionario\n");
    	printf("--------------------------------------------------------------------------------\n");
    	printf("ERROR al cargar (%s)\n", ruta_dicc);
    	printf("--------------------------------------------------------------------------------\n");
    }
    else
    {	
    	limpiar;
    	ascii_art();
    	printf("Menu Diccionario\n");
    	printf("--------------------------------------------------------------------------------\n");
    	printf("Ingrese la palabra que desea agregar al diccionario\n");
    	printf("--------------------------------------------------------------------------------\n\n");
    	printf("~ ");
		// insertar salto de linea antes de agregar la nueva palabra
        fputs("\n",puntr_dicc); 

			while((caracter = getchar()) != '\n')
        	{
            		fputc(caracter, puntr_dicc);
        	}
    }
    fclose(puntr_dicc);
}

// abrir archivo de diccionario
void ver_diccionario() {
	// definir modo lectura  
	puntr_dicc = fopen(ruta_dicc,"r");

	if (puntr_dicc == NULL)
    {
    	printf("Menu Diccionario\n");
    	printf("--------------------------------------------------------------------------------\n");
    	printf("ERROR al cargar (%s)\n", ruta_dicc);
    	printf("--------------------------------------------------------------------------------\n");
    }
    else
    {	
    	printf("Menu Diccionario\n");
    	printf("--------------------------------------------------------------------------------\n");
    	printf("Palabras almacenadas en (%s)\n", ruta_dicc);
    	printf("--------------------------------------------------------------------------------\n\n");
		
		while((caracter = fgetc(puntr_dicc)) != EOF)
        {
            printf("%c", caracter);
        }
    }
    fclose(puntr_dicc);
}

//----- Acerca del programa ----------------------------------------------------
void Leame() {
	limpiar;
	ascii_art();

	pntr_leame = fopen(ruta_leame,"r");
	if (pntr_leame == NULL) {
    	printf("\nError al cargar el archivo (%s)\n\n", ruta_leame);
    } 
    else {
    	while((caracter = fgetc(pntr_leame)) != EOF) {
            printf("%c", caracter);
        }
    fclose(pntr_leame);
    }
}
