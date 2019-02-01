#ifndef thread_connection_job_h
#define thread_connection_job_h

void build_req_logmsg(char *msg_log, struct thread_node *data,char *client_req);
void *accept_connection(void *data);

#endif
