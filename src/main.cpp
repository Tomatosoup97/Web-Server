#include <iostream>
#include "async_client.hpp"


int main(int argc, char *argv[]) {
    if (argc != 3) {
      std::cout << "Usage: async_client <server> <path>\n";
      std::cout << "Example:\n";
      std::cout << "  async_client www.boost.org /LICENSE_1_0.txt\n";
      return 1;
    }
    webserver::run_async_client(argv[1], argv[0]);
}
