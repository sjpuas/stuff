    /*
    ** Ejemplo de servidor TCP
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
    #include <sys/wait.h>
    #include <signal.h>

    #define PUERTO 3500    // Puerto al que conectarán los usuarios

    #define MAX_CONEX 10     // Cuántas conexiones pendientes se mantienen en cola

    #define TOPE_TEXTO 100 // Tope máximo del mensaje a enviar

    void sigchld_handler(int s)
    {
        while(wait(NULL) > 0);
    }

    int main (void)
    {
	char txt[TOPE_TEXTO];  // Esta variable es el texto
        int sock_con, sock_nuevo;  // Escuchar sobre sock_con, nuevas conexiones sobre sock_nuevo
        struct sockaddr_in mi_dire;    // informacion sobre mi direccion
        struct sockaddr_in su_dire; // informacion sobre la direccion del cliente
        int sin_size;
        struct sigaction sa;
        int si=1;

        if ((sock_con = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
            perror ("socket"); // Si hay error, sale y despliega el error
            exit (1);
        }

        if (setsockopt(sock_con,SOL_SOCKET,SO_REUSEADDR,&si,sizeof(int)) == -1)
	{
            perror ("setsockopt"); // Si hay error, sale y despliega el error
            exit (1);
        }
        
        mi_dire.sin_family = AF_INET;         // Ordenación de bytes de la máquina
        mi_dire.sin_port = htons(PUERTO);     // short, Ordenación de bytes de la red
        mi_dire.sin_addr.s_addr = INADDR_ANY; // Rellenar con mi dirección IP
        memset(&(mi_dire.sin_zero), '\0', 8); // Poner a cero el resto de la estructura = relleno

        if (bind(sock_con, (struct sockaddr *)&mi_dire, sizeof(struct sockaddr)) == -1) // Intenta ocupar el puerto
	{
            perror ("bind"); // Si hay error, sale y despliega el error
            exit (1);
        }

        if (listen(sock_con, MAX_CONEX) == -1)
	{
            perror ("listen"); // Si hay error, sale y despliega el error
            exit (1);
        }

        sa.sa_handler = sigchld_handler; // Elimina procesos muertos
        sigemptyset (&sa.sa_mask);
        sa.sa_flags = SA_RESTART;
        if (sigaction (SIGCHLD, &sa, NULL) == -1)
	{
            perror ("sigaction");  // Si hay error, sale y despliega el error
            exit (1);
        }

        while (1) // Loop principal accept(), se queda "pegado" recibiendo datos
	{
            sin_size = sizeof(struct sockaddr_in);
            if ((sock_nuevo = accept(sock_con, (struct sockaddr *)&su_dire, &sin_size)) == -1) // Trata de aceptar la conexión
	    {
                perror ("accept");  // Si hay error, sale y despliega el error
                continue;
            }
            printf ("Servidor: Se toma conexion desde %s\n", inet_ntoa(su_dire.sin_addr)); // El servidor imprime desde donde se conectó el cliente
            if (!fork()) // No se pudo hacer "proceso hijo" para la conexión nueva
	    {
                close (sock_con); // El hijo no necesita este descriptor (el original)

                strcpy (txt, "MENU\n====\n\n");
send(sock_nuevo, txt, strlen(txt), 0);
		strcpy (txt,"1) 8 Bytes\n");
send(sock_nuevo, txt, strlen(txt), 0);		
strcpy (txt,"2) 32 Bytes\n");
send(sock_nuevo, txt, strlen(txt), 0);
		strcpy (txt,"3) 512 Bytes\n");
send(sock_nuevo, txt, strlen(txt), 0);
		strcpy (txt,"4) 2 KB (2048 Bytes)\n");
send(sock_nuevo, txt, strlen(txt), 0);
		strcpy (txt,"5) 8 KB (8192 Bytes)\n");
send(sock_nuevo, txt, strlen(txt), 0);
		strcpy (txt,"0) SALIR\n\n");
send(sock_nuevo, txt, strlen(txt), 0);
		strcpy (txt,"Seleccione opcion -> ");


                if (send(sock_nuevo, txt, strlen(txt), 0) == -1) // Este mensaje debe ser cambiado, según los tamaños necesitados
                    perror ("send"); // Si hay error, sale y despliega el error
                close (sock_nuevo);
                exit (0);
            }
            close (sock_nuevo);  // El proceso padre no necesita este socket, lo cierra
        }

        return 0; // Termina la ejecución
    }
