#ifndef WEBSERVER_SERVER_HPP
#define WEBSERVER_SERVER_HPP

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>
#include "connection.hpp"
#include "request_handler.hpp"


namespace webserver {

typedef boost::asio::ip::tcp::endpoint tcp_endpoint;

class Server {
public:
    Server(std::string location,
           std::string port="8000",
           size_t thread_count=1)
            : thread_count_(thread_count)
            , acceptor_(io_service_)
            , connection_()
            , signals_(io_service_)
            , request_handler_(location)
            , port_(port) {
        setup_server();
    }

    void run() {
        initialize_threads_pool();
        join_threads();
    }

private:
    size_t thread_count_;
    std::vector<boost::thread> thread_poll_;
    boost::asio::io_service io_service_;
    boost::asio::ip::tcp::acceptor acceptor_;
    connection_ptr connection_;
    boost::asio::signal_set signals_;
    RequestHandler request_handler_;
    std::string port_;

    void initialize_threads_pool() {
        for (std::size_t i = 0; i < thread_count_; ++i) {
            boost::thread thread(new boost::thread(
                  boost::bind(&boost::asio::io_service::run, &io_service_)));
            thread_poll_.push_back(thread);
        }
    }

    void join_threads() {
        // Wait until all threads complete execution
        for (std::size_t i = 0; i < thread_poll_.size(); ++i)
            thread_poll_[i].join();
    }

    void setup_server() {
        set_signals();
        tcp_endpoint endpoint = create_endpoint();
        open_acceptor(endpoint);
        start_connection();
    }

    tcp_endpoint create_endpoint() {
        boost::asio::ip::tcp::resolver resolver(io_service_);
        boost::asio::ip::tcp::resolver::query query("127.0.0.1", port_);
        tcp_endpoint endpoint = *resolver.resolve(query);
        return endpoint;
    }

    void open_acceptor(tcp_endpoint endpoint) {
        acceptor_.open(endpoint.protocol());
        acceptor_.bind(endpoint);
        acceptor_.listen();
    }

    void set_signals() {
        /* Set signals for process termination */
        signals_.add(SIGINT);
        signals_.add(SIGTERM);
        signals_.add(SIGQUIT);
        signals_.async_wait(boost::bind(&Server::stop, this));
    }

    void start_connection() {
        connection_.reset(new Connection(io_service_, request_handler_));
        acceptor_.async_accept(
            connection_->socket(),
            boost::bind(&Server::handle_connection, this,
                        boost::asio::placeholders::error)
        );
    }

    void handle_connection(boost::system::error_code& error_code) {
        if (!error_code) connection_->start();
        start_connection();
    }

    void stop() {
        io_service_.stop();
    }
};

} // namespace webserver

#endif //WEBSERVER_SERVER_HPP
