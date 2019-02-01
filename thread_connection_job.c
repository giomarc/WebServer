#include "threadmanager.h"
#include "http_request.h"
#include "thread_connection_job.h"
#include "http_response.h"
#include "format.h"
#include "init_server.h"
#include "cache.h"
#include "configuration.h"
#include "file.h"
#include "log.h"
#include "content_adaptation.h"



void *accept_connection(void *data) {

    struct thread_node *td = (struct thread_node *) data;
    char *request_file = alloc_string(64);
    char method[5];
    char *body_buf = alloc_string(4096);
    char *buffer = alloc_string(4096);
    char *user_agent = alloc_string(64);
    char *accept = alloc_string(64);
    char *q = alloc_string(12);
    char *w = alloc_string(12);
    char *h = alloc_string(12);
    char *adapted_path = alloc_string(128);
    char *imagetosend = alloc_string(128);
    char msg_log[512];
    int nread;

    while ((nread = read_from_client(buffer, td->tconnsk)) == 0) {

        build_req_logmsg(msg_log,td,buffer);
        write_on_buffer(msg_log);
        getRequestLine(td->tconnsk, buffer,request_file,method);
        get_file_path(request_file,td->req_filepath);

        if (strcmp(method,"") == 0) //method not implemented
        {
            send_unimplemented(td->tconnsk);
        }
        else if(strcmp(method,"HEAD") == 0) //HEAD method
        {
            responseMsgHeader(td->tconnsk,td->clientaddr, request_file, td->req_filepath);
        }
        else if(exist_file(td->req_filepath)==-1) //check if exists file
        {
            send_error_response(td->tconnsk);
        }
        else //file exists
        {
            if (strcmp(request_file, "/index.html") == 0)
            {
                    responseMsgHeader(td->tconnsk,td->clientaddr, request_file, td->req_filepath);
                    send_body(body_buf, td->tconnsk, td->req_filepath);
            }
            else //has been requested an image
            {
                get_user_agent(buffer, user_agent);
                find_accept(buffer, accept);
                parse_accept(accept,q,w,h);

                int res = hashmap_search_item(imagetosend, td->h_map, request_file, q, "", ""); //search if file is in cache
                if (res == -1)
                {
                    insert_in_hashmap(td->h_map, request_file, q, "", "", adapted_path,td->req_filepath); //inserts new node in hashmap
                    responseMsgHeader(td->tconnsk,td->clientaddr,request_file, adapted_path);
                    send_body(body_buf, td->tconnsk, adapted_path);
                }
                else
                {
                    responseMsgHeader(td->tconnsk, td->clientaddr, request_file, imagetosend);
                    send_body(body_buf, td->tconnsk, imagetosend);
                }
                memset(adapted_path, 0, sizeof(adapted_path));
                memset(imagetosend, 0, sizeof(imagetosend));
            }
        }
        memset(td->req_filepath,0, sizeof(td->req_filepath));
        memset(request_file,0,sizeof(request_file));
        memset(buffer,0,sizeof(buffer));
    }
    pthread_exit(0);
}



void build_req_logmsg(char *msg_log, struct thread_node *data,char *client_req)
{
    char client_address[12] = {0};
    struct sockaddr_in * caddr = (struct sockaddr_in *) data->clientaddr;
    strcpy(client_address,inet_ntoa(caddr->sin_addr));
    sprintf(msg_log,"[REQUEST]\nclient [%s] on port [%d] to thread [%ld] on socket [%d]\nasks:\n%s",client_address,caddr->sin_port,data->tid,data->tconnsk,client_req);
}



