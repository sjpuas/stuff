    /*
    ** tcpc.c -- Ejemplo de cliente TCP
    */

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <errno.h>
    #include <string.h>
    #include <netdb.h>
    #include <sys/types.h>
    #include <netinet/in.h>
    #include <sys/socket.h>

    #define PORT 3500 // puerto al que se va a conectar

    #define TOPE 100 // m�ximo n�mero de bytes que se pueden leer de una vez

    int main (int argc, char *argv[])
    {
        int sock_con, numbytes;  
        char txt[TOPE]; // txt es un arreglo que recibir� el mensaje
        struct hostent *el;
        struct sockaddr_in su_dire; // informaci�n de la direcci�n de destino 

        if (argc != 2)
	{
            fprintf (stderr,"USO: tcpc ip_servidor\n");
            exit (1);
        }

        if ((el=gethostbyname(argv[1])) == NULL) // obtiene informaci�n de la otra m�quina
	{
            perror ("gethostbyname"); // Si hay error, sale y despliega el error
            exit (1);
        }

        if ((sock_con = socket(AF_INET, SOCK_STREAM, 0)) == -1) // Intenta crear conexi�n
	{
            perror ("socket"); // Si hay error, sale y despliega el error
            exit (1);
        }

        su_dire.sin_family = AF_INET;    // Ordenaci�n de bytes de la m�quina 
        su_dire.sin_port = htons(PORT);  // short, Ordenaci�n de bytes de la red 
        su_dire.sin_addr = *((struct in_addr *)el->h_addr);
        memset(&(su_dire.sin_zero), '\0', 8);  // poner a cero el resto de la estructura = relleno

        if (connect(sock_con, (struct sockaddr *)&su_dire, sizeof(struct sockaddr)) == -1) // Intenta conectar
	{
            perror ("connect"); // Si hay error, sale y despliega el error
            exit (1);
        }

        if ((numbytes=recv(sock_con, txt, TOPE-1, 0)) == -1) // Intenta recibir datos
	{
            perror ("recv");  // Si hay error, sale y despliega el error
            exit (1);
        }

        txt[numbytes] = '\0'; // Agrega el terminador al final de la cadena

        //printf ("Largo del texto: %d\n", numbytes);
	printf ("%s\n", txt);

        close (sock_con); // Cierra conexi�n

        return 0;
    }
