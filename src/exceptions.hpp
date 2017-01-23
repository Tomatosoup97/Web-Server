#ifndef WEBSERVER_EXCEPTIONS_HPP
#define WEBSERVER_EXCEPTIONS_HPP


#include <iostream>
#include <boost/asio.hpp>


namespace webserver {

void output_exception(std::exception &e) {
    std::cout << "Exception: " << e.what() << "\n";
}

void output_error(const boost::system::error_code &error) {
    std::cout << "Error: " << error.message() << "\n";
}

void output_error(std::string error_message) {
	std::cout << error_message << "\n";
}

void check_error_code(const boost::system::error_code &error) {
    if (error) {
        output_error(error);
        return;
    }
}

} // namespace webserver

#endif //WEBSERVER_EXCEPTIONS_HPP
