#ifndef WEBSERVER_RESPONSE_HPP
#define WEBSERVER_RESPONSE_HPP

#include <boost/asio.hpp>
#include "status_code.hpp"


namespace webserver {

class Response {
public:
    int http_version;
    int http_subversion;
    std::string content;
    std::map<std::string, std::string> headers;
    status::status_codes status_code;

    Response() {
    }
};

} // namespace webserver

#endif //WEBSERVER_RESPONSE_HPP
