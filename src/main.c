#include "main.h"
#include "tcp.h"
#include "http.h"

void debug_log(const char *message) {
    printf("%s\n", message);
}

int main() {
    tcp_server server = {0};
    server_status_e status = bind_tcp_port(&server, 8080);
    if (status != SERVER_OK) {
        debug_log("Server initialization failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        int client_fd = accept_client(server.socket_fd);
        if (client_fd == -1) {
            debug_log("Failed to accept client connection");
            continue;
        }

        debug_log("Client connected");

        http_request req = {0};

        if (read_http_request(client_fd, &req) != HTTP_PARSE_OK) {
            debug_log("Failed to read or parse HTTP request");
            close(client_fd);
            return 0;
        }

        if (parse_http_headers(req.buffer, &req) != HTTP_PARSE_OK) {
            debug_log("Failed to read or parse HTTP headers");
            close(client_fd);
            return 0;
        }

        printf("Parsed HTTP Headers\n");
        for (size_t i = 0; i < req.header_count; i++) {
            printf("%s: %s\n", req.headers[i].key, req.headers[i].value);
        }

        free_http_headers(&req);

        http_response response = {0};
        init_http_response(&response);
        add_http_header(&response, "Content-Type", "text/html");
        add_http_header(&response, "Connection", "close");
        // set_http_body(&response, "<html><body><h1>Hello, world!</h1></body></html>");
        response.body = "hehe123";
        response.body_length = 7;

        send_http_response(client_fd, &response);

        free_http_response(&response);
        close(client_fd);
        debug_log("Response sent and client connection closed");
    }

    close(server.socket_fd);

    return 0;
}