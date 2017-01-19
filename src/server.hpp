#ifndef WEBSERVER_SERVER_HPP
#define WEBSERVER_SERVER_HPP

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include "connection.hpp"


namespace webserver {

class Server {
public:
    Server(int thread_count=1)
            : thread_count_(thread_count)
            , acceptor_(io_service_)
            , connection_(){
    }

    void run() {
        io_service_.run();
    }

private:
    int thread_count_;
    std::vector<std::thread> thread_poll_;
    boost::asio::io_service io_service_;
    boost::asio::ip::tcp::acceptor acceptor_;
    connection_ptr connection_;

    void stop() {
        io_service_.stop();
    }
};

} // namespace webserver

#endif //WEBSERVER_SERVER_HPP
