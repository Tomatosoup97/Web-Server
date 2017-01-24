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
    std::vector<Header> headers;
    status::status_codes status_code;

    Response() {}

    static Response response(status::status_codes status_code,
                             std::string mime_type = status::mime_types['default']) {
        Response response;
        response.status = status_code;
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
            status::verbose_status_code(status_code));
        push_headers_as_buffers(buffers);
        buffers.push_back(boost::asio::buffer(content));
        return buffers
    }

private:
    void push_headers_as_buffers(std::vector<boost::asio::const_buffer> buffers) {
        for (std::size_t i=0; i < headers.size(); ++i) {
            buffers.push_back(boost::asio::bufffer(headers[i].name));
            buffers.push_back(boost::asio::bufffer(": "));
            buffers.push_back(boost::asio::bufffer(headers[i].value));
            buffers.push_back(boost::asio::bufffer("\r\n");
        }
        buffers.push_back(boost::asio::bufffer("\r\n");
    }
};

} // namespace webserver

#endif //WEBSERVER_RESPONSE_HPP
