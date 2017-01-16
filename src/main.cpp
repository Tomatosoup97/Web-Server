#include <iostream>
#include "server.hpp"


void runserver(const std::string &port,
               const std::string &location,
               std::size_t thread_count) {
    return;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
      std::cout << "Usage: web_server <port> <threads_num> <location>\n";
      std::cout << "Example:\n";
      std::cout << "  webserver 8000 1 .";
      return 1;
    }
    runserver(argv[1], argv[2], argv[3]);
}
