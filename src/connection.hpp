#ifndef WEBSERVER_CONNECTION_HPP
#define WEBSERVER_CONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "request.hpp"
#include "response.hpp"


namespace webserver {

#define REQUEST_SIZE 16384 // 2^14

typedef boost::shared_ptr<connection> connection_ptr;
typedef boost::array<char, REQUEST_SIZE> request_buffer;


class Connection : public boost::enable_shared_from_this<connection> {
    /* Class representing asynchronous TCP connection.
     *
     * Shared_ptr references are used in order to keep the connection
     * alive. When no new async operation occurs, all connection_ptr disappear
     * and destructor closes the socket.
     * */
public:
    Connection(boost::asio::io_service &io_service,
               RequestHandler request_handler)
            : strand_(io_service)
            , socket_(io_service)
            , request_handler_(request_handler) {
    }

    void start() {
        read_data();
    }

    boost::asio::ip::tcp::socket& socket() {
        return socket_;
    }

private:
    boost::asio::io_service::strand strand_;
    boost::asio::ip::tcp::socket socket_;
    request_buffer buffer_;
    Request request_;
    Response response_;
    RequestParser request_parser_;
    RequestHandler request_handler_;

    void read_data() {
        socket_.async_read_some(boost::asio::buffer(buffer_),
            strand.wrap(
                boost::bind(&handle_reading_date, shared_from_this(),
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred))
            );
    }

    void handle_reading_date(boost::system::error_code& e,
                             std::size_t bytes_transferred) {
        /* Handler which parse incoming request and return a response */
        if (e) return;
        parse_state = request_parser.parse(request_, buffer_.data(),
                                           buffer_.data() + bytes_transferred);
        switch (parse_state) {
            case completed:
                request_handler_.handle(request_, response_);
                write_response();
                break;
            case unfinished:
                read_data();
                break;
            case failed:
                response_ = response.response(HTTP_400_BAD_REQUEST);
                write_response();
                break;
            default:
                respone_ = response.response(HTTP_500_INTERNAL_SERVER_ERROR);
                write_response();
        }
    }

    void write_response() {
        boost::asio::async_write(socket_, response_.to_buffers(),
            strand_.wrap(boost::bind(&shutdown_socket, shared_from_this(),
                                     boost::asio::placeholders::error)));
    }

    void shutdown_socket(boost::system::error_code& e) {
        /* Disable both sending and receiving on the socket */
        if (e) return;
        boost::system::error_code error_code;
        socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both,
                         error_code);
        // connection_ptr reference disappear destroying the connection object
    }
};

} // namespace webserver

#endif // WEBSERVER_CONNECTION_HPP
