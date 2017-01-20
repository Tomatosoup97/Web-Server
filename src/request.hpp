#ifndef WEBSERVER_REQUEST_HPP
#define WEBSERVER_REQUEST_HPP

#include <boost/asio.hpp>


namespace webserver {

typedef struct Headers {
    std::string name;
    std::string value;
} Header;


class Request {
public:
    int http_version;
    int http_subversion;
    std::string method;
    std::string uri;
    std::vector<Header> headers;

    Request() {
    }
};

} // namespace webserver

#endif //WEBSERVER_REQUEST_HPP
