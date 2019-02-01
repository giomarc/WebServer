#ifndef init_server_h
#define init_server_h

int connected_clients;


struct sockaddr_in *malloc_sock_addr();
int listen_socket(struct sockaddr_in *server);


#endif