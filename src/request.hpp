#ifndef WEBSERVER_REQUEST_HPP
#define WEBSERVER_REQUEST_HPP

#include <boost/asio.hpp>


namespace webserver {

class Request {
public:
    int http_version;
    int http_subversion;
    std::string method;
    std::string uri;
    std::map<std::string, std::string> headers;
    
    Request() {
    }
};

} // namespace webserver

#endif //WEBSERVER_REQUEST_HPP
