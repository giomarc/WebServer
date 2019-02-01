#ifndef http_response_h
#define http_response_h


char * responseMsg();
void responseMsgHeader(int conn, struct sockaddr *client,char *filename_to_send,char *filepath);
void send_body(char *buffer, int connsk,char *filepath);
void send_error_response(int conn);
void send_unimplemented(int conn);

#endif
