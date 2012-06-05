
#include "mongoose.h"

static void *callback(enum mg_event event,
                      struct mg_connection *conn) {
  const struct mg_request_info *ri = mg_get_request_info(conn);

  if (event == MG_NEW_REQUEST) {
    const char *content = "hello from mongoose!";
    mg_printf(conn, "HTTP/1.1 200 OK\r\n"
              "Content-Length: %u\r\n"        // Always set Content-Length
              "Content-Type: text/plain\r\n\r\n",
              (unsigned int)strlen(content));
    mg_mark_end_of_header_transmission(conn);
    mg_printf(conn, "%s", content);
    // Mark as processed
    return "";
  } else {
    return NULL;
  }
}

int main(void) {
  struct mg_context *ctx;
  const char *options[] = {"listening_ports", "8080", NULL};
  const struct mg_user_class_t ucb = {
    callback,  // User-defined callback function
    NULL       // Arbitrary user-defined data
  };

  ctx = mg_start(&ucb, options);
  getchar();  // Wait until user hits "enter"
  mg_stop(ctx);

  return 0;
}
