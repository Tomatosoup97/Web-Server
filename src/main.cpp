#include <iostream>
#include <string>
#include "server.hpp"


void runserver(const std::string &port,
               const std::string &location,
               std::size_t thread_count) {
    webserver::Server server(port, location, thread_count);
    server.run();
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
      std::cout << "Usage: web_server <location> <port> <threads_num>\n";
      std::cout << "Example:\n";
      std::cout << "  webserver 8000 1 .";
      return 1;
    }
    runserver(argv[1], argv[2], (size_t) argv[3]);
}
