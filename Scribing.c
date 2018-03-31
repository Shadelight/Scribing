/* *************************************************************************
 * Scribing  -- Un  simple editor de texto con la opción de poder corregir *
 *         palabras con mala ortografía y la capacidad para crear y        *
 *         modificar un archivo tipo odt ó txt.                            *
 *         proyecto de la asignatura: Técnica de Programación 1            *
 **************************************************************************/
//----- Librerias Incluidas ----------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----- Variables globales -----------------------------------------------------
char ruta_dicc[] = "Diccionario.txt";
char ruta_asccii[] = "Ascii.txt";
FILE *pntr_asccii;
FILE *puntr_dicc;
FILE *fichero;
int opcion;
char caracter;

//----- Prototipos de función --------------------------------------------------
void ascii_art();
void menu();
void op_menu(int);
void menu_archivo();
void nuevo_archivo();
void abiri_archivo();
void corrector_ort();
void corregir_texto();
void cargar_archivo();
void ver_diccionario();
void acerca_de();

//----- Programa principal -----------------------------------------------------
int main() { 

	ascii_art();
	do { 
		menu();
		scanf("%d", &opcion);
		while (getchar() != '\n');
		op_menu(opcion);

	} while(opcion != 4);
	return 0;
}

//----- Cabecera ascii ---------------------------------------------------------
void ascii_art() {
	pntr_asccii = fopen(ruta_asccii,"r");
	if (pntr_asccii == NULL) {
    	printf("\nError al cargar la cabecera ascii del programa . . .\n\n");
    } 
    else {
    	while((caracter = fgetc(pntr_asccii)) != EOF) {
            printf("%c", caracter);
        }
    fclose(fichero);
    }
}

/* ====================== Menu principal ==================== */

/* En el menu principal se encuentra las llamadas a las todas las funciones.*/

void menu_principal() {
	system("clear");
	ascii_art();
	printf("Menu Principal: \n");
	printf("--------------------------------------------------------------------------------\n");
	printf("1. Archivo  |  2. Corrector | 3. Diccionario |  4. Acerca de   |  5. Salir\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("\n>> ");
}

void op_principal(int op) {
	switch(op) { 
			case 1:
				menu_archivo();
				break;
			case 2: 
				corrector_ort();
				getchar();
				break;
			case 3:
				acerca_de();
				getchar();
				break;
			case 4:
				break;
		} 
}

/* ====================== Menu opcion 1. (Archivo) ==================== */

void menu_archivo() {
	do{ 
		system("clear");
		ascii_art();
		printf("Menu Archivo\n");
		printf("--------------------------------------------------------------------------------\n");
		printf("1. Nuevo  |  2. Abrir  |  3. Regresar  \n");
		printf("--------------------------------------------------------------------------------\n");
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
	printf("(presione ENTER para guardar)\n");
	printf("--------------------------------------------------------------------------------\n");
 	printf("\n~ ");

		while((letras = getchar()) != '\n')
 		{
 			fputc(letras, temp);
 		}

	system("clear");
	ascii_art();
 	printf("Gurdar Como: \n");
	printf("--------------------------------------------------------------------------------\n");
	printf("(presione ENTER para guardar)\n");
	printf("--------------------------------------------------------------------------------\n");
 	printf("Nombre:\n ");
 	gets(nombre);
 	printf("Tipo: \n");
 	gets(tipo);

 	/* Concatenar el nombre del archivo con la extensión */
    strcpy( nom_compl, nombre );
    strcat( nom_compl, tipo );

    fichero = fopen(nom_compl,"w");

    if(fichero == NULL) {
		printf("\n\n\nNo se pudo crear el archivo . . .");
	}
	else {
		/* Copia el contenido guardado en temp al nuevo archivo creado 
		por el usuario */
		while ( (letras = fgetc ( temp )) != EOF ) {
        	fputc ( letras, fichero );
    	}
		printf("\n\n\nSu archivo se ha guardado con exito . . .");
		fclose(temp);
		fclose(fichero);
		remove("temp.txt");
    }

}



void abiri_archivo() {
	system("clear");
	ascii_art();
	fichero = fopen("Nuevo archivo.txt","r");
	char caracter;

	if(fichero == NULL) {
		printf("Menu Archivo\n");
		printf("--------------------------------------------------------------------------------\n");
		printf("(presione ENTER para regresar)\n");
		printf("--------------------------------------------------------------------------------\n");	
		printf("No se pudo abrir el archivo . . .\n");
	}
	else {
		printf("Nuevo archivo.txt\n");
		printf("--------------------------------------------------------------------------------\n");
		printf("(presione ENTER para regresar)\n");
		printf("--------------------------------------------------------------------------------\n");
		printf("~ ");
        while((caracter = fgetc(fichero)) != EOF) {
			printf("%c",caracter);
	    }

		fclose(fichero);
	}
}












/* ====================== Corrector Ortografico ==================== */

void corrector_ort() {
		do{ 
		system("clear");
		ascii_art();
		printf("Corrector Ortografico\n");
		printf("--------------------------------------------------------------------------------\n");
		printf("1. Corregir texto  |  2. Ver Diccionario  |  3. Regresar\n");
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
				system("clear");
				ascii_art();
				ver_diccionario();
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



void corregir_texto() {
	printf("Corrector Ortografico\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("En desarrollo...\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("\n>> ");
}

// abrir archivo de diccionario
void ver_diccionario() {
	char caracter;
	dict_fptr = fopen(arch_dict,"r");

	if (dict_fptr == NULL)
    {
    	printf("Corrector Ortografico\n");
    	printf("--------------------------------------------------------------------------------\n");
    	printf("\n*** ERROR al abrir el archivo del diccionario (%s) *** ", arch_dict);
    	printf("--------------------------------------------------------------------------------\n");
    }
    else
    {	
    	printf("Corrector Ortografico\n");
    	printf("--------------------------------------------------------------------------------\n");
    	printf("\n Las palabras almacenadas en el diccionario son: \n");
    	printf("--------------------------------------------------------------------------------\n");
		
		while((caracter = fgetc(fichero)) != EOF)
        {
            printf("%c", caracter);
        }
    }
    fclose(fichero);
}


























/* ====================== Acerca de ==================== */

void acerca_de() {
	system("clear");
	ascii_art();
	char caracter;
	fichero = fopen("Léame.md","r");
	if (fichero == NULL) {
    	printf("\nError al cargar la cabecera ascii del programa . . .\n\n");
    } 
    else {
    	while((caracter = fgetc(fichero)) != EOF) {
            printf("%c", caracter);
        }
    fclose(fichero);
    }
}














