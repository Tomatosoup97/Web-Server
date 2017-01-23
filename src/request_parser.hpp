#include "request.hpp"
#include "exceptions.hpp"


namespace webserver {

#define array_size (sizeof(a)/sizeof(*a))

enum parser_state {
    completed = 1,
    unfinished = 2,
    failed = 3,
};


class RequestParser {
    /* Callable instance parsing headers and checking if request is valid
     * */
public:
    RequestParser() {}

    void parse(Request &request,
               request_buffer buffer_beg,
               request_buffer buffer_end) {
        while (begin != end)
            consume(request, *buffer_beg++);
        check_request(request);
    }

    void check_request(Request &request) {
        check_http_version();
        check_http_verb();
    }

    void operator() {
        parse();
    }

private:
    Request request;

    parser_state consume(Request &request, request_buffer buffer_beg) {
        // TODO: Parse the data stream
    }

    void parse_headers() {
        std::vector<int>::iterator header_iter;
        for (header_iter = request.headers.begin();
             header_iter != request.headers.end();
             ++header_iter) {
            check_header(*header_iter);
        }
    }

    void check_header(struct Header header) {
        // TODO: check if header is valid
        return;
    }

    void check_http_version() {
        /* Supported HTTP version: 1.0 v 1.1 */
        if ((request.http_version != 1) ||
            (request.http_subversion != 0 ||
             request.http_subversion != 1))
            // TODO: return response with 505 status code
            output_error("HTTP version not supported");
    }

    void check_http_verb() {
        std::string supported_methods [] = {"GET", "POST", "HEAD"};
        bool is_valid = false;

        for (int i; i < array_size(supported_methods); ++i) {
            if (request.method == supported_methods[i]) {
                is_valid = true;
                break;
            }
        }
        if (!is_valid)
            // TODO: return response with 405 status code
            output_error("HTTP verb not supported");
    }
};

} // namespace webserver
