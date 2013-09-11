// Codigo By JuanK Thor Alias "Don Root"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <curses.h>
#define TOPE 8192 // Max cantidad de bytes a enviar
int main ()
{
	char txt[TOPE]; // Cadena o string
	char t; // Para leer una tecla...
	int opc; // Opcion del usuario
	int largo; // Largo que seleccionara el usuario
	int i; // Para rellenar "string"
	
	do
	{
		system ("clear");
		printf ("MENU\n====\n\n");
		printf ("1) 8 Bytes\n");
		printf ("2) 32 Bytes\n");
		printf ("3) 512 Bytes\n");
		printf ("4) 2 KB (2048 Bytes)\n");
		printf ("5) 8 KB (8192 Bytes)\n");
		printf ("0) SALIR\n\n");
		printf ("Seleccione opcion -> ");
		scanf ("%d", &opc);
		switch (opc)
		{
			case 0:
				exit (0); // Sale del programa!
				break;
			case 1:
				largo = 8;
				break;
			case 2:
				largo = 32;
				break;
			case 3:
				largo = 512;
				break;
			case 4:
				largo = 2048;
				break;
			case 5:
				largo = 8192;
				break;
			default:
				largo = 0;
				system ("clear");
				printf ("\nERROR: Opcion no valida!\n\n");
				printf ("\n\nPresione una tecla...\n\n");
				system ("read x");
				break;
		}
		if (largo > 0)
		{
			printf ("%d", largo);
			txt [0] = '\0'; // Borra cadena, equivale a guardar ""
			for (i=0; i<largo; i++)
			{
				txt[i] = 'A'; // Cualquiera LETRA = 1 Byte!
			}
			printf ("LARGO %d ", strlen (txt));
			// TOME tiempo INICIAL
			printf ("Mensaje = %s\n", txt); // Debe enviar en vez de mostrar!
			printf ("LARGO = %d", strlen(txt));
			// TOME tiempo FINAL
			// Imprima cuanto se DEMORO!
			printf ("\n\nPresione una tecla...\n\n");
			system ("read x");
		}
	} while (opc != 0);
}
