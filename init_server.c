#include "configuration.h"
#include "init_server.h"

/*
 * allocates memory for server socket
 */
struct sockaddr_in *malloc_sock_addr(void)
{
    struct sockaddr_in *p = NULL;

    while((p = malloc(sizeof(struct sockaddr_in))) == NULL)
    {
        perror("malloc sock addr");
    }
    return p;
}


/*
 * binds socket and puts it on listen
 */

int listen_socket(struct sockaddr_in *server)
{
    int fd;

    while((fd = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        printf("Error establishing socket\n");
    }

    memset((void *)server,0,sizeof(server));
    server->sin_family = AF_INET;
    server->sin_port = htons(PORT_NUMBER);
    server->sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(fd,(const struct sockaddr *)server, sizeof( const struct sockaddr)) == -1)
    {
        printf("Error in bind\n");
        exit(1);
    }

    while(listen(fd,BACK_LOG)==-1)
    {
        printf("Error in listen\n");
    }

    return fd;
}






