#include "init_server.h"
#include "thread_connection_job.h"
#include "threadmanager.h"
#include "http_response.h"
#include "http_request.h"
#include "format.h"
#include "log.h"
#include "cache.h"
#include "libwurfl/src/wurfl.h"
#include </usr/include/libxml2/libxml/xmlstring.h>
#include </usr/include/libxml2/libxml/SAX2.h>
#include </usr/include/libxml2/libxml/xmlversion.h>
#include "util.h"
#include "configuration.h"


#define MAX_CONN 30000
struct Hashmap *hmap = NULL;



int main(int argc, char *argv[])
{
    int caddrlen,yes = 1,timeout = 5,conn_sock;
    connected_clients = 0;
    actual_pool_size = 0;

    if(argc!=1)
    {
        printf("Usage %s: no args\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    init_log_mtx();
    create_threadlog();
    init_logbuf();
    create_threadlog();
    hmap = create_hashmap();
    create_thread_cache(hmap);
    struct sockaddr_in *serveraddr = malloc_sock_addr();
    struct sockaddr_in *clientaddr = malloc(sizeof(struct sockaddr_in));
    caddrlen = sizeof(clientaddr);
    if(clientaddr == NULL)
    {
        perror("malloc client");
        exit(1);
    }

    int listen_sock = listen_socket(serveraddr);
    while(connected_clients <= MAX_CONN)
    {
        if((conn_sock = accept(listen_sock, (struct sockaddr *)&clientaddr,&caddrlen)) <0)
        {
            perror("accept");
            exit(1);
        }

        connected_clients+=1;

        struct thread_node *t = malloc(sizeof(struct thread_node));
        t->clientaddr = (struct sockaddr *)&clientaddr;
        t->tconnsk = conn_sock;
        t->h_map = hmap;

        setsockopt(t->tconnsk,IPPROTO_TCP,SO_KEEPALIVE,&yes,sizeof(yes));
        setsockopt(t->tconnsk,IPPROTO_TCP,SO_RCVTIMEO,&timeout,sizeof(int));
        t->busy = 1;

        if(pthread_create(&t->tid, NULL, accept_connection, (void *) t) != 0)
        {
            perror("thread create");
            exit(1);
        }
    }
    pthread_exit(0);
}


