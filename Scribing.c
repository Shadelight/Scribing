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
char ruta_leame[] = "Léame.md";
FILE *pntr_leame;
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
void corrector();
void corregir_texto();
void cargar_archivo();
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

	// limpiar
	//fcloseall();
	return 0;
}

//----- Cabecera ascii ---------------------------------------------------------
void ascii_art() {
	pntr_asccii = fopen(ruta_asccii,"r");
	if (pntr_asccii == NULL) {
    	printf("\nError al cargar la cabecera (%s) ascii del programa \n\n", ruta_asccii);
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
	system("cls");
	ascii_art();
	printf("Menu Principal: \n");
	printf("--------------------------------------------------------------------------------\n");
	printf("1. Archivo  |  2. Corrector | 3. Diccionario |  4. Acerca de   |  5. Salir\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("\n>> ");
}

void op_menu(int op) {
	switch(op) { 
			case 1:
				menu_archivo();
				break;
			case 2: 
				corrector();
				getchar();
				break;
			case 3:
				getchar();
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
		system("cls");
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
				system("cls");
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

	system("cls");
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
	system("cls");
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

void corrector() {
		do{ 
		system("cls");
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
				system("cls");
				ascii_art();
				corregir_texto();
				getchar();
				break;
			case 2:
				system("cls");
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
	puntr_dicc = fopen(ruta_dicc,"r");

	if (puntr_dicc == NULL)
    {
    	printf("Corrector Ortografico\n");
    	printf("--------------------------------------------------------------------------------\n");
    	printf("\n*** ERROR al abrir el archivo del diccionario (%s) *** ", ruta_dicc);
    	printf("--------------------------------------------------------------------------------\n");
    }
    else
    {	
    	printf("Corrector Ortografico\n");
    	printf("--------------------------------------------------------------------------------\n");
    	printf("Palabras almacenadas en el Diccionario (%s)\n", ruta_dicc);
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
	system("cls");
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
