// Codigo By JuanK Thor Alias "Don Root"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main ()
{
	long demora; // Hara el calculo en microsegundos
	struct timeval tiempo_ini, tiempo_fin;
	// Son 2 structs de tipo "timeval", para uso del tiempo

	gettimeofday (&tiempo_ini, 0); // Saca tiempo inicial
	//*********************** Aqui seria el inicio de enviar
	system ("clear");
	printf ("Hola mundo\n\n\n");
	//*********************** Aqui seria el fin de enviar
	gettimeofday (&tiempo_fin, 0); // Saca tiempo final
	demora = tiempo_fin.tv_usec - tiempo_ini.tv_usec;
	printf ("Se demoro en imprimir %ld microsegundos\n\n", demora);
}
