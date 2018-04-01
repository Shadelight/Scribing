/* *************************************************************************
 * Scribing  -- Un  simple editor de texto con la opción de poder corregir *
 *         palabras con mala ortografía y la capacidad para crear y        *
 *         modificar un archivo tipo odt ó txt.                            *
 *         proyecto de la asignatura: Técnica de Programación 1            *
 **************************************************************************/
//----- Librerias Incluidas 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----- Variables globales 
char ruta_dicc[] = "Diccionario.txt";
char ruta_asccii[] = "Ascii.txt";
char ruta_leame[] = "Léame.md";
char linea[] = "--------------------------------------------------------------------------------";
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

//----- Programa principal 
int main() { 

	do { 
		menu();
		scanf("%d", &opcion);
		while (getchar() != '\n');
		op_menu(opcion);
	} while(opcion != 5);

	// limpiar
	//fcloseall();
	return 0;
}

//----- Cabecera ascii ---------------------------------------------------------
void ascii_art() {
	pntr_asccii = fopen(ruta_asccii,"r");
	if (pntr_asccii == NULL) {
    	printf("\nError al cargar la cabecera (%s) ascii del programa. \n\n", ruta_asccii);
    } 
    else {
    	while((caracter = fgetc(pntr_asccii)) != EOF) {
            printf("%c", caracter);
        }
    fclose(pntr_asccii);
    }
}

//----- Menu principal ---------------------------------------------------------
void menu() {
	system("clear");
	ascii_art();
	printf("Menu Principal\n");
	printf("%s\n", linea);
	printf("1. Archivo  |  2. Corrector | 3. Diccionario |  4. Acerca de   |  5. Salir\n");
	printf("%s\n", linea);
	printf("\n>> ");
}

void op_menu(int op) {
	switch(op) { 
			case 1:
				menu_archivo();
				break;
			case 2: 
				corrector();
				break;
			case 3:
				menu_diccionario();
				break;
			case 4:
				Leame();
				getchar();
				break;
			case 5:
				break;
		} 
}

//----- Menu Archivo ---------------------------------------------------------
void menu_archivo() {
	do{ 
		system("clear");
		ascii_art();
		printf("Menu Archivo\n");
		printf("%s\n", linea );
		printf("1. Nuevo  |  2. Abrir  |  3. Regresar  \n");
		printf("%s\n", linea );
		printf("\n>> ");
		scanf("%d", &opcion);
		while (getchar() != '\n');

		switch(opcion) {
			case 1:
				system("clear");
				ascii_art();
				nuevo_archivo();
				getchar();
				break;
			case 2:
				abiri_archivo();
				getchar();
				break;
			case 3:
				break;
			default:
				printf("Opcion incorrecta.\n");
				break;
		}	
	} while( opcion != 3);
}

void nuevo_archivo() {
	FILE *temp;
	char letras, nombre[60], tipo[6], nom_compl[100];

	temp = fopen("temp.txt","w");

	printf("Nuevo archivo\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("Ingrese el contenido que desee\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("(presione ENTER para guardar)\n");
 	printf("\n~ ");

		while((letras = getchar()) != '\n')
 		{
 			fputc(letras, temp);
 		}

	system("clear");
	ascii_art();
	printf("Nuevo archivo\n");
	printf("--------------------------------------------------------------------------------\n");
 	printf(">> Gurdar Como:\n");
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

    nuevo_arch = fopen(nom_compl,"w");

    if(nuevo_arch == NULL) {
		printf("\n\nNo se pudo crear el archivo . . .");
	}
	else {

    	system("clear");
		ascii_art();
		printf("Nuevo archivo:\n");
		printf("--------------------------------------------------------------------------------\n");
 		printf(">> Gurdar Como\n");
		printf("--------------------------------------------------------------------------------\n");
		printf("\nSu archivo (%s) se ha guardado con exito . . .", nom_compl);
		fclose(temp);
		fclose(nuevo_arch);
		remove("temp.txt");
    }

}

void abiri_archivo() {
	system("clear");
	ascii_art();
	char  nombre[60], tipo[6], nom_compl[100];
	printf("Menu Archivo\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("Ingrese el nombre + el tipo del archivo que desea abrir:\n");
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

    abrir_arch = fopen(nom_compl,"r");

	char caracter;

	if(abrir_arch == NULL) {
		printf("\nNo se pudo abrir el archivo . . .");
	}
	else {
		system("clear");
		ascii_art();
		printf("%s\n", nom_compl);
		printf("--------------------------------------------------------------------------------\n");
		printf("(presione ENTER para regresar)\n");
		printf("--------------------------------------------------------------------------------\n");
		printf("\n~ ");

        while((caracter = fgetc(abrir_arch)) != EOF) {
			printf("%c",caracter);
	    }

		fclose(abrir_arch);
	}
}

//----- Corrector Ortografico -----------------------------------------------------
void corrector() {
		do{ 
		system("clear");
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
				system("clear");
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
	printf("Funcion en desarrollo...\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("\n>> ");
}



void menu_diccionario(){
	do{
		system("clear");
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
				system("clear");
				ascii_art();
				add_dicc();
				getchar();
				break; 
			case 2:
				system("clear");
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
    	printf("ERROR al abrir (%s)\n", ruta_dicc);
    	printf("--------------------------------------------------------------------------------\n");
    }
    else
    {	
    	system("clear");
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
	puntr_dicc = fopen(ruta_dicc,"r");

	if (puntr_dicc == NULL)
    {
    	printf("Menu Diccionario\n");
    	printf("--------------------------------------------------------------------------------\n");
    	printf("ERROR al abrir (%s)\n", ruta_dicc);
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
	system("clear");
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
