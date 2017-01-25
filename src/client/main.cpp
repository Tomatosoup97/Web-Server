#include <iostream>
#include "client/async_client.hpp"


namespace webserver {
namespace client {

void run_async_client(char *argv1, char *argv2) {
    /* Client flow:
     * 1. Resolve
     * 2. Connect
     * 3. Send request
     * 4. Receive response
     * */
    try {
        boost::asio::io_service io_service;
        Client c(io_service, argv1, argv2);
        io_service.run();
    }
    catch (std::exception &e) {
        output_exception(e);
    }
}

} // namespace client
} // namespace webserver


int main(int argc, char *argv[]) {
    if (argc != 3) {
      std::cout << "Usage: async_client <server> <path>\n";
      std::cout << "Example:\n";
      std::cout << "  async_http_client www.example.com /api/data";
      return 1;
    }
    webserver::client::run_async_client(argv[1], argv[2]);
}
