    /*
    ** udps.c -- Ejemplo de servidor UDP
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

    #define PUERTO 6000    // puerto al que conectarán los clientes

    #define TOPE 100 // Valor máximo de la cadena

    int main(void)
    {
        int sock_con; // Socket de conexión
        struct sockaddr_in mi_dire;    // información sobre mi dirección
        struct sockaddr_in su_dire; // información sobre la dirección del cliente
        int largo_dire, numbytes;
        char txt[TOPE];  // Variable que recibira la información

        if ((sock_con = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
            perror ("socket");
            exit (1);
        }

        mi_dire.sin_family = AF_INET;         // Ordenación de bytes de máquina
        mi_dire.sin_port = htons(PUERTO);     // short, Ordenación de bytes de la red
        mi_dire.sin_addr.s_addr = INADDR_ANY; // rellenar con mi dirección IP
        memset(&(mi_dire.sin_zero), '\0', 8); // poner a cero el resto de la estructura = relleno

        if (bind(sock_con, (struct sockaddr *)&mi_dire, sizeof(struct sockaddr)) == -1)  // Trata de abrir puerto
	{
            perror ("bind"); // Si hay error, sale y despliega el error
            exit (1);
        }

        largo_dire = sizeof(struct sockaddr);

        if ((numbytes=recvfrom(sock_con,txt, TOPE-1, 0, (struct sockaddr *)&su_dire, &largo_dire)) == -1)
	{
            perror ("recvfrom");  // Si hay error, sale y despliega el error
            exit (1);
        }

        printf ("Paquete recibido desde %s\n", inet_ntoa(su_dire.sin_addr));
        printf("El paquete tiene %d bytes de longitud\n", numbytes);
        txt[numbytes] = '\0'; // Agrega caracter terminador al final
        printf("El paquete contiene el texto: %s\n", txt);

        close(sock_con);

        return 0;
    } 
