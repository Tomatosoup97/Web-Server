#ifndef WEBSERVER_ASYNC_CLIENT_HPP
#define WEBSERVER_ASYNC_CLIENT_HPP

#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "exceptions.hpp"


using boost::asio::ip::tcp;
using std::cout;
using std::string;


namespace webserver {

class Client {
public:
    Client(boost::asio::io_service &io_service,
           const string &server, 
           const string &path) : resolver_(io_service),
                                 socket_(io_service) {

        // Form the request
        std::ostream request_stream(&request_);
        request_stream << "GET " << path << " HTTP/1.0\r\n";
        request_stream << "Host: " << server << "\r\n";
        request_stream << "Accept: */*\r\n";
        request_stream << "Connection: close\r\n\r\n";

        // Resolve query into a list of endpoints
        tcp::resolver::query query(server, "http");
        resolver_.async_resolve(query,
            boost::bind(
                &Client::handle_resolve, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::iterator)
        );
    }

private:
    tcp::resolver resolver_;
    tcp::socket socket_;
    boost::asio::streambuf request_;
    boost::asio::streambuf response_;

    void handle_resolve(const boost::system::error_code &error,
                        tcp::resolver::iterator endpoint_iterator) {
        /* Attempt a connection to each endpoint until we establish
         * a successful one.
         * */
        check_error_code(error);
        boost::asio::async_connect(
            socket_, endpoint_iterator,
            boost::bind(
                &Client::handle_connect, this,
                boost::asio::placeholders::error)
        );
    }

    void handle_connect(const boost::system::error_code &error) {
        // Send request on successful connection.
        check_error_code(error);
        boost::asio::async_read_until(
            socket_, response_, "\r\n",
            boost::bind(
                &Client::handle_write_request, this,
                boost::asio::placeholders::error)
        );
    }

    void handle_write_request(const boost::system::error_code &error) {
        // Read the response status line. The buffer will automatically grow
        // to accommodate the entire line.
        check_error_code(error);
        boost::asio::async_read_until(
            socket_, response_, "\r\n",
            boost::bind(&Client::handle_read_status_line, this,
                        boost::asio::placeholders::error)
        );
    }

    void handle_read_status_line(const boost::system::error_code &error) {
        check_error_code(error);
        // Check that response is OK.
        std::istream response_stream(&response_);
        string http_version;
        response_stream >> http_version;
        unsigned int status_code;
        response_stream >> status_code;
        string status_message;
        std::getline(response_stream, status_message);
        
        if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
            cout << "Invalid response\n";
            return;
        }
        if (status_code != 200) {
            cout << "Response returned with status code";
            cout << status_code << "\n";
            return;
        }
        // Read the response headers, which are terminated by a blank line.
        boost::asio::async_read_until(socket_, response_, "\r\n\r\n",
            boost::bind(
                &Client::handle_read_headers, this,
                boost::asio::placeholders::error)
        );
    }

    void handle_read_headers(const boost::system::error_code &error) {
        check_error_code(error);
        // Process the response headers.
        std::istream response_stream(&response_);
        string header;
        while (std::getline(response_stream, header) && header != "\r")
            cout << header << "\n";
        cout << "\n";

        if (response_.size() > 0)
            cout << &response_;

        boost::asio::async_read(socket_, response_,
            boost::asio::transfer_at_least(1),
            boost::bind(
                &Client::handle_read_content, this,
                boost::asio::placeholders::error)
        );
    }

    void handle_read_content(const boost::system::error_code &error) {
        if (!error) {
            cout << &response_;

            boost::asio::async_read(socket_, response_,
                boost::asio::transfer_at_least(1),
                boost::bind(
                    &Client::handle_read_content, this,
                    boost::asio::placeholders::error)
            );
        } else if (error != boost::asio::error::eof) {
            output_error(error);
        }
    }
};


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

} // namespace webserver

#endif //WEBSERVER_ASYNC_CLIENT_HPP
