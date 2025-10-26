#ifndef HTTP_H
#define HTTP_H

#define HTTP_MAX_REQUEST_LEN (8192*4)
#define HTTP_METHOD_MAX_LEN 8
#define HTTP_PATH_MAX_LEN 2048
#define HTTP_PROTOCOL_LEN 16
#define HTTP_MAX_HEADER_KEY_LEN 256
#define HTTP_MAX_HEADER_VAL_LEN 256

#include  <stdio.h>

typedef enum {
    HTTP_PARSE_OK,
    HTTP_PARSE_INVALID,
} http_parse_e;

typedef struct {
    char key[HTTP_MAX_HEADER_KEY_LEN];
    char value[HTTP_MAX_HEADER_VAL_LEN];
} http_header_t;

typedef struct {
    int status_code;
    char reason_phrase[64];
    http_header_t *headers;
    size_t header_count;
    char *body;
    size_t body_length;
} http_response;

typedef struct {
    char method[HTTP_METHOD_MAX_LEN];
    char path[HTTP_PATH_MAX_LEN];
    char protocol[HTTP_PROTOCOL_LEN];
    char buffer[HTTP_MAX_REQUEST_LEN];
    size_t header_count;
    http_header_t *headers;
} http_request;

http_parse_e read_http_request(int socket_fd, http_request *request);
http_parse_e parse_http_headers(const char *raw_request, http_request *request);
void free_http_headers(http_request *request);

void init_http_response(http_response *response);
void add_http_header(http_response *response, const char *key, const char *value);
void free_http_response(http_response *response);

void send_http_response(int client_fd, const http_response *response);
char *construct_http_response(const http_response *response, size_t *response_length);

#endif //HTTP_H