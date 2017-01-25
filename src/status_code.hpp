#ifndef WEBSERVER_STATUS_CODE_HPP
#define WEBSERVER_STATUS_CODE_HPP

#include <boost/asio.hpp>
#include <map>
#include <string>


namespace webserver {
namespace status {

const std::map<const std::string, const std::string> mime_types = {
        {"html", "text/html"},
        {"css", "text/css"},
        {"js", "text/js"},
        {"json", "application/json"},
        {"xml", "application/xml"},
        {"jpg", "image/jpg"},
        {"png", "image/png"},
        {"gif", "image/gif"},
        {"default", "text/plain"},
};

const std::string get_mime_type(std::string extension="default") {
    if (mime_types.find(extension) == mime_types.end())
        return mime_types.at("default");
    return mime_types.find(extension)->first;
}

bool is_informational(status_codes code){
    return (code >= 100 && code <= 199);
}


bool is_success(status_codes code){
    return (code >= 200 && code <= 299);
}


bool is_redirect(status_codes code){
    return (code >= 300 && code <= 399);
}


bool is_client_error(status_codes code){
    return (code >= 400 && code <= 499);
}


bool is_server_error(status_codes code){
    return (code >= 500 && code <= 599);
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

const std::map<const int, const std::string> status_strings = {
    {200, "200 OK"},
    {202, "202 Accepted"},
    {204, "204 No Content"},
    {300, "300 Multiple Choices"},
    {301, "301 Moved Permanently"},
    {302, "302 Found"},
    {304, "304 Not Modified"},
    {307, "307 Temporary Redirect"},
    {400, "400 Bad Request"},
    {401, "401 Unauthorized"},
    {403, "403 Forbidden"},
    {404, "404 Not Found"},
    {405, "404 Method Not Allowed"},
    {500, "500 Internal Server Error"},
    {501, "501 Not Implemented"},
    {502, "502 Bad Gateway"},
    {503, "503 Service Unavailable"},
    {504, "504 Gateway Timeout"},
    {505, "505 HTTP version not supported"},
};

std::string verbose_status_code(status_codes code) {
    std::string result;
    try {
        result = status_strings.at(code);
    } catch (const std::exception& e) {
        result = status_strings.at(400);
    };
    return result;
}

} // namespace status
} // namespace webserver

#endif //WEBSERVER_STATUS_CODE_HPP
