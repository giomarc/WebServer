#include "log.h"
#include"file.h"
#include "configuration.h"
#include "http_request.h"
#include "http_response.h"
#include "format.h"
#include "threadmanager.h"
#include "content_adaptation.h"

#define SERVER_STRING "Server: WebServer/0.1\r\n"


/*
 * gets current datetime
 */
char *get_current_time()
{
    char *d = alloc_string(38);
    time_t t = time(NULL);

    struct tm temp = *localtime(&t);
    strftime(d,38,"Date: %a, %d %b %Y %H:%M:%S GMT\r\n",&temp);
    return d;
}


/*
 * gets last modify date of a file
 */
char *get_last_modify_date()
{
    char *moddate = alloc_string(50);
    time_t t = time(NULL);

    struct tm temp = *localtime(&t);
    strftime(moddate,50,"Last-Modified: %a, %d %b %Y %H:%M:%S GMT\r\n",&temp);
    return moddate;
}


/*
 * sends body message to client
 */

void send_body(char *buffer, int connsk, char *filepath)
{
    int filedes, ret;

    //open file
    if((filedes = open(filepath,O_RDONLY)) == -1)
    {
        perror("open img in send body");
    }

    while((ret = read(filedes,buffer,BUFFER_SIZE))>0)
    {
        send(connsk,buffer,ret,0);
    }
    memset(buffer,0, sizeof(buffer));
}


/*
 * sends header in case no error occurred
 */
void responseMsgHeader(int conn, struct sockaddr *client, char *filename_to_send,char *filepath) {

    //char *date = alloc_string(38);
    char date[38];
    char *mod_date = alloc_string(50);
    char *http_msg = alloc_string(256);
    strcpy(date,get_current_time());
    mod_date = get_last_modify_date();
    char *content = alloc_string(64);
    char type[28]= {0};
    char *msg_log = alloc_string(512) ;
    char client_address[24] = {0};
    struct sockaddr_in * caddr = (struct sockaddr_in *) client;
    strcpy(client_address,inet_ntoa(caddr->sin_addr));

    if(strstr(filename_to_send,".html") != NULL)
    {
        sprintf(type, "Content-type: %s\r\n","text/html");
    }
    else if(strstr(filename_to_send,".jpg") != NULL)
    {
        sprintf(type,"Content-type: %s\r\n","image/jpeg");
    }

    sprintf(http_msg, "HTTP/1.1 200 OK\r\n");
    send(conn,http_msg,strlen(http_msg),0);

    sprintf(msg_log,"[ANSWER] to client [%s][%d] on socket [%d]\nfile %s\n%s%s\n",client_address,caddr->sin_port,conn,filename_to_send,date,http_msg);
    write_on_buffer(msg_log);

    sprintf(http_msg,"Connection: keep-alive\r\n");
    send(conn,http_msg,strlen(http_msg),0);

    sprintf(http_msg,"Server: Web Server\r\n");
    send(conn,http_msg,strlen(http_msg),0);

    sprintf(http_msg,"%s",date);
    send(conn,http_msg,strlen(http_msg),0);

    sprintf(http_msg,"%s",mod_date);
    send(conn,http_msg,strlen(http_msg),0);

    sprintf(http_msg,"%s",type);
    send(conn,http_msg,strlen(http_msg),0);

    sprintf(content, "Content-length: %ld\r\n\r\n", get_file_size(filepath));
    sprintf(http_msg,"%s",content);
    send(conn,http_msg,strlen(http_msg),0);

    free(content);
    free(mod_date);
    free(http_msg);
    free(msg_log);

}


/*
 * to send error header when file not exists
 */
void send_error_response(int conn)
{
    char *date = alloc_string(38);
    char *http_msg = alloc_string(256);
    date = get_current_time();
    char *content = alloc_string(64);

    char  body[] = "<!DOCTYPE html>\n"
                   "<html lang=\"en\">\n"
                   "<head>\n"
                   "    <meta charset=\"UTF-8\">\n"
                   "    <title>Home Page</title>\n"
                   "</head>\n"
                   "<body>\n"
                   "    <br>\n"
                   "    <br>\n"
                   "    <div align=\"center\">\n"
                   "        <h1 align=\"center\">Error 404! File not found</h1>\n"
                   "</body>\n"
                   "</html>\0";

    sprintf(http_msg, "HTTP/1.1 404 Not Found\r\n");
    send(conn,http_msg,strlen(http_msg),0);

    sprintf(http_msg,"Connection: keep-alive\r\n");
    send(conn,http_msg,strlen(http_msg),0);

    sprintf(http_msg,"Server: Web Server\r\n");
    send(conn,http_msg,strlen(http_msg),0);

    sprintf(http_msg,"%s",date);
    send(conn,http_msg,strlen(http_msg),0);

    sprintf(http_msg,"Content-type: text/html\r\n");
    send(conn,http_msg,strlen(http_msg),0);

    sprintf(content, "Content-length: %ld\r\n\r\n", strlen(body));
    sprintf(http_msg,"%s",content);
    send(conn,http_msg,strlen(http_msg),0);

    send(conn,body,strlen(body),0);

    free(content);
    free(date);
    free(http_msg);
}




/*
 * to send error header when method is not implemented
 */
void send_unimplemented(int conn)
{
    char *date = alloc_string(38);
    char *http_msg = alloc_string(256);
    date = get_current_time();
    char *content = alloc_string(64);

    char  body[] = "<!DOCTYPE html>\n"
                   "<html lang=\"en\">\n"
                   "<head>\n"
                   "    <meta charset=\"UTF-8\">\n"
                   "    <title>Home Page</title>\n"
                   "</head>\n"
                   "<body>\n"
                   "    <br>\n"
                   "    <br>\n"
                   "    <div align=\"center\">\n"
                   "        <h1 align=\"center\">Request method not supported</h1>\n"
                   "</body>\n"
                   "</html>\0";

    sprintf(http_msg, "HTTP/1.1 405 Method not allowed\r\n");
    send(conn,http_msg,strlen(http_msg),0);

    sprintf(http_msg,"Connection: keep-alive\r\n");
    send(conn,http_msg,strlen(http_msg),0);

    sprintf(http_msg,"Server: Web Server\r\n");
    send(conn,http_msg,strlen(http_msg),0);

    sprintf(http_msg,"%s",date);
    send(conn,http_msg,strlen(http_msg),0);

    sprintf(http_msg,"Content-type: text/html\r\n");
    send(conn,http_msg,strlen(http_msg),0);

    sprintf(content, "Content-length: %ld\r\n\r\n", strlen(body));
    sprintf(http_msg,"%s",content);
    send(conn,http_msg,strlen(http_msg),0);

    send(conn,body,strlen(body),0);

    free(content);
    free(date);
    free(http_msg);
}


