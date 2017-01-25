#ifndef WEBSERVER_RESPONSE_HPP
#define WEBSERVER_RESPONSE_HPP

#include <boost/asio.hpp>
#include "status_code.hpp"
#include <string>
#include <map>


namespace webserver {

class Response {
public:
    int http_version;
    int http_subversion;
    std::string content;
    std::vector<Header> headers;
    status::status_codes status_code;

    Response() {}

    static Response response(status::status_codes status_code,
                             std::string mime_type = status::get_mime_type()) {
        Response response;
        response.status_code = status_code;
        response.content = status::verbose_status_code(status_code);
        response.headers.resize(1);
        // TODO: Provide more headers
        response.headers[0].name = "Content-Type";
        response.headers[0].value = mime_type;
        return response;
    }

    std::vector<boost::asio::const_buffer> as_buffers() {
        /* Pack response into const buffers */
        std::vector<boost::asio::const_buffer> buffers;
        buffers.push_back(boost::asio::buffer(
                status::verbose_status_code(status_code)));
        push_headers_as_buffers(buffers);
        buffers.push_back(boost::asio::buffer(content));
        return buffers;
    }

private:
    void push_headers_as_buffers(std::vector<boost::asio::const_buffer> buffers) {
        const std::string separator = ": ";
        const std::string carriage_newline = "\r\n";
        for (std::size_t i=0; i < headers.size(); ++i) {
            buffers.push_back(boost::asio::buffer(headers[i].name));
            buffers.push_back(boost::asio::buffer(separator));
            buffers.push_back(boost::asio::buffer(headers[i].value));
            buffers.push_back(boost::asio::buffer(carriage_newline));
        }
    }
};

} // namespace webserver

#endif //WEBSERVER_RESPONSE_HPP
