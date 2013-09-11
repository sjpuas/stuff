    /*
    ** udpc.c -- ejemplo de cliente UDP
    */

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <errno.h>
    #include <string.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>

    #define PUERTO 6000    // puerto del servidor donde vamos a conectarnos

    int main (int argc, char *argv[])
    {
        int sock_con; // Socket de conexión
        struct sockaddr_in su_dire; // información sobre la dirección del servidor
        struct hostent *el;
        int numbytes;

        if (argc != 3)
	{
            fprintf (stderr,"USO: udpc ip_servidor mensaje\n");
            exit (1);
        }

        if ((el=gethostbyname(argv[1])) == NULL)   // obtener información de máquina
	{
            perror ("gethostbyname"); // Si hay error, sale y despliega el error
            exit (1);
        }

        if ((sock_con=socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
            perror ("socket"); // Si hay error, sale y despliega el error
            exit (1);
        }

        su_dire.sin_family = AF_INET;     // Ordenación de bytes de máquina
        su_dire.sin_port = htons(PUERTO); // short, Ordenación de bytes de la red
        su_dire.sin_addr = *((struct in_addr *)el->h_addr);
        memset(&(su_dire.sin_zero), '\0', 8); // poner a cero el resto de la estructura = relleno

        if ((numbytes=sendto(sock_con, argv[2], strlen(argv[2]), 0, (struct sockaddr *)&su_dire, sizeof(struct sockaddr))) == -1)
	{
            perror ("sendto");  // Si hay error, sale y despliega el error
            exit (1);
        }

        printf ("Cantidad de bytes enviados %d\n", numbytes);
	printf ("Destino %s\n", inet_ntoa(su_dire.sin_addr));

        close(sock_con);

        return 0;
    } 
