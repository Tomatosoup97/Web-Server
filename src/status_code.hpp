#ifndef WEBSERVER_STATUS_CODE_HPP
#define WEBSERVER_STATUS_CODE_HPP

#include <boost/asio.hpp>


namespace webserver {
namespace status {


bool is_informational(status_codes code){
    return (code >= 100 && code <= 199)
}


bool is_success(status_codes code){
    return (code >= 200 && code <= 299)
}


bool is_redirect(status_codes code){
    return (code >= 300 && code <= 399)
}


bool is_client_error(status_codes code){
    return (code >= 400 && code <= 499)
}


bool is_server_error(status_codes code){
    return (code >= 500 && code <= 599)
}


enum status_codes {
    HTTP_100_CONTINUE = 100,
    HTTP_101_SWITCHING_PROTOCOLS = 101,
    HTTP_200_OK = 200,
    HTTP_201_CREATED = 201,
    HTTP_202_ACCEPTED = 202,
    HTTP_203_NON_AUTHORITATIVE_INFORMATION = 203,
    HTTP_204_NO_CONTENT = 204,
    HTTP_205_RESET_CONTENT = 205,
    HTTP_206_PARTIAL_CONTENT = 206,
    HTTP_300_MULTIPLE_CHOICES = 300,
    HTTP_301_MOVED_PERMANENTLY = 301,
    HTTP_302_FOUND = 302,
    HTTP_303_SEE_OTHER = 303,
    HTTP_304_NOT_MODIFIED = 304,
    HTTP_307_TEMPORARY_REDIRECT = 307,
    HTTP_400_BAD_REQUEST = 400,
    HTTP_401_UNAUTHORIZED = 401,
    HTTP_403_FORBIDDEN = 403,
    HTTP_404_NOT_FOUND = 404,
    HTTP_405_METHOD_NOT_ALLOWED = 405,
    HTTP_406_NOT_ACCEPTABLE = 406,
    HTTP_407_PROXY_AUTHENTICATION_REQUIRED = 407,
    HTTP_408_REQUEST_TIMEOUT = 408,
    HTTP_409_CONFLICT = 409,
    HTTP_410_GONE = 410,
    HTTP_411_LENGTH_REQUIRED = 411,
    HTTP_412_PRECONDITION_FAILED = 412,
    HTTP_413_REQUEST_ENTITY_TOO_LARGE = 413,
    HTTP_414_REQUEST_URI_TOO_LONG = 414,
    HTTP_415_UNSUPPORTED_MEDIA_TYPE = 415,
    HTTP_416_REQUESTED_RANGE_NOT_SATISFIABLE = 416,
    HTTP_417_EXPECTATION_FAILED = 417,
    HTTP_500_INTERNAL_SERVER_ERROR = 500,
    HTTP_501_NOT_IMPLEMENTED = 501,
    HTTP_502_BAD_GATEWAY = 502,
    HTTP_503_SERVICE_UNAVAILABLE = 503,
    HTTP_504_GATEWAY_TIMEOUT = 504,
    HTTP_505_HTTP_VERSION_NOT_SUPPORTED = 505,
};

// Status strings
const std::string HTTP_200_OK = "200 OK";
const std::string HTTP_201_CREATED = "201 Created";
const std::string HTTP_202_ACCEPTED = "202 Accepted";
const std::string HTTP_204_NO_CONTENT = "204 No Content";
const std::string HTTP_300_MULTIPLE_CHOICES = "300 Multiple Choices";
const std::string HTTP_301_MOVED_PERMANENTLY = "301 Moved Permanently";
const std::string HTTP_302_FOUND = "302 Found";
const std::string HTTP_304_NOT_MODIFIED = "304 Not Modified";
const std::string HTTP_307_TEMPORARY_REDIRECT = "307 Temporary Redirect";
const std::string HTTP_400_BAD_REQUEST = "400 Bad Request";
const std::string HTTP_401_UNAUTHORIZED = "401 Unauthorized";
const std::string HTTP_403_FORBIDDEN = "403 Forbidden";
const std::string HTTP_404_NOT_FOUND = "404 Not Found";
const std::string HTTP_500_INTERNAL_SERVER_ERROR = "500 Internal Server Error";
const std::string HTTP_501_NOT_IMPLEMENTED = "501 Not Implemented";
const std::string HTTP_502_BAD_GATEWAY = "502 Bad Gateway";
const std::string HTTP_503_SERVICE_UNAVAILABLE = "503 Service Unavailable";
const std::string HTTP_504_GATEWAY_TIMEOUT = "504 Gateway Timeout";
const std::string HTTP_505_HTTP_VERSION_NOT_SUPPORTED = "505 HTTP version not supported";

} // namespace status
} // namespace webserver

#endif //WEBSERVER_STATUS_CODE_HPP
