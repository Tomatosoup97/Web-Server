#ifndef WEBSERVER_CONNECTION_HPP
#define WEBSERVER_CONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "request.hpp"
#include "response.hpp"


namespace webserver {

typedef boost::shared_ptr<connection> connection_ptr;


class Connection : public boost::enable_shared_from_this<connection> {
    /* Class representing asynchronous TCP connection.
     *
     * Shared_ptr references are used in order to keep the connection
     * alive. When no new async operation occurs, all shared_ptr disappear
     * and destructor closes the socket.
     * */
public:
    Connection(boost::asio::io_service &io_service)
            : strand_(io_service)
            , socket_(io_service) {
    }

    void start() {
        socket_.async_read_some(boost::asio::buffer(buffer_),
            strand.wrap(
                boost::bind(&connection::handle_read, shared_from_this(),
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred))
            );
    }

    boost::asio::ip::tcp::socket& socket() {
        return socket_;
    }

private:
    boost::asio::io_service::strand strand_;
    boost::asio::ip::tcp::socket socket_;
    Request request_;
    Response response_;

    void shutdown_socket(boost::system::error_code& e) {
        /* Disable both send and receive on the socket */
        if (e) return;
        boost::system::error_code error_code;
        socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both,
                         error_code);
    }

    void handle_read(boost::system::error_code& e) {
        /* Parse incoming request and reply with a response */
        if (e) return;
        // TODO:
        // Parse request
        // Reply with a response
        // Recursively invoke handle_read untill error occurs
        // Continuously pass shared_ptr refrence
    }
};

} // namespace webserver

#endif // WEBSERVER_CONNECTION_HPP
