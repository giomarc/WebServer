#include "format.h"
#include "log.h"
#include "file.h"
#include "configuration.h"
#include "http_request.h"
#include "http_response.h"


/*
 * finds where starts user agent header message
 */
void get_user_agent(char *message, char *useragent)
{
    char * temp = alloc_string(1024);

    strcpy(temp,message);
    temp[strlen(message)-1] = '\0';
    strcpy(useragent,strstr(temp,"User-Agent")+12);

}


/*
 * finds accept header
 */
void find_accept(char *buf, char *accept)
{
    char *temp = alloc_string(1024);

    strcpy(temp,buf);
    temp[strlen(buf)-1]='\0';
    strcpy(accept,strstr(temp,"Accept:")+8);
}


/*
 * parse a line
 */
void parse_line(char *line, char *buf)
{
    buf[0] = '\0';
    int len = (int) strlen(line);
    int i = 0;
    bool found = false;

    while(i < len && !found)
    {
        if(line[i] == '=')
        {
            strcpy(buf, &line[i+1]);
            line[i] = '\0';
            found = true;
        }
        i++;
    }
    return;
}



/*
 * parse accept line, filling q,w and h values
 */
void parse_accept(char *accept, char *q, char *w, char *h)
{
    if(strstr(accept,"q="))
    {
        //trova il fattore di qualità
        strcpy(q,strstr(accept,"q="));
        char *q_value = alloc_string(128);
        parse_line(q,q_value);
        float fq = cast_to_float(q_value);
        sprintf(q_value,"%.1f",fq);
        strcpy(q,q_value);
    }

    if(strstr(accept,"h="))
    {
        //trova l'altezza dell'immagine
        strcpy(h,strstr(accept,"h="));
        char *h_value = alloc_string(128);
        parse_line(h,h_value);
        int ih = cast_to_int(h_value);
        sprintf(h_value,"%d",ih);
        strcpy(h,h_value);
    }

    if(strstr(accept,"w="))
    {
        //trova la larghezza dell'immagine
        strcpy(w,strstr(accept,"w="));
        char *w_value = alloc_string(128);
        parse_line(w,w_value);
        int iw = cast_to_int(w_value);
        sprintf(w_value,"%d",iw);
        strcpy(w,w_value);
    }
}



/*
 * checks if the method of the client request is valid
 * then saves into url the requested file
 */
char * getRequestLine(int clientsock,char * message, char *url,char *method)
{
    char *start = NULL;
    char *end = NULL;
    char *PATTERN_GET = "GET ";
    char *PATTERN_HTTP = " HTTP/1.1";
    char *PATTERN_HEAD = "HEAD ";

    if ((start = strstr(message,PATTERN_GET)) != NULL)
    {
        sprintf(method,"%s","GET");
        start += strlen(PATTERN_GET);
        end = strstr(start,PATTERN_HTTP);
        memcpy(url,start,end-start);
        if(strcmp(url,"/") == 0)
        {
            strcat(url,"index.html");
        }
        else
        {
            url[(end-start)/sizeof(char)] = '\0';
        }

    }
    else if((start = strstr(message,"HEAD"))!=NULL)
    {
        sprintf(method,"%s","HEAD");
        start += strlen(PATTERN_HEAD);
        end = strstr(start,PATTERN_HTTP);
        memcpy(url,start,end-start);
        sprintf(method,"%s","HEAD");
        if(strcmp(url,"/") == 0)
        {
            strcat(url,"index.html");
        }
        else
        {
            url[(end-start)/sizeof(char)] = '\0';
        }
    }
    else{
        ///method is not implemented
        strcat(url,"");
    }

}


/*
 * reads from socket client's messages
 */
int read_from_client(char *buffer, int filedes)
{
    int nbytes;
    errno = 0;

    nbytes = read(filedes,buffer,MAX_MSG);
    if(nbytes < 0)
    {
        //errore in lettura
        perror("read");
        printf("errno: %d\n",errno);
        exit(EXIT_FAILURE);
    }
    else if(nbytes == 0)
    {
        //non sono stati più ricevuti dati
        return -1;
    }
    else
    {
         //sono stati ricevuti dei dati
         return 0;
    }
}



