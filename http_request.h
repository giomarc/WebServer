#ifndef http_request_h
#define http_request_h

//#define ROOT "/home/giorgia/CLionProjects/WebServer/resources"
//#define MAX_MSG 4096 //prima era 512

void get_user_agent(char *message, char *useragent);
char *getRequestLine(int clientsock,char *message, char *url, char *method);
int read_from_client(char *message, int filedes);
void find_accept(char *buf, char *accept);
void parse_accept(char *accept, char *q, char *w, char *h);

#endif