#ifndef WEBSERVER_REQUEST_PARSER_HPP
#define WEBSERVER_REQUEST_PARSER_HPP

#include "connection.hpp"
#include "request.hpp"
#include "exceptions.hpp"
#include "status_code.hpp"


namespace webserver {

#define array_size (sizeof(a)/sizeof(*a))
#define REQUEST_SIZE 16384 // 2^14
#define HTTP_VERB_MAX_LEN 7

typedef boost::array<char, REQUEST_SIZE> request_buffer;

enum parser_state {
    completed = 1,
    unfinished = 2,
    failed = 3,
};

const std::string supported_methods [] = {"GET", "POST", "HEAD"};
const std::string supported_versions [] = {"HTTP/1.0", "HTTP/1.1"};


class RequestParser {
    /* Callable instance parsing and validating incoming request.
     * */
public:
    RequestParser() {}

    parser_state parse(Request &request,
                       request_buffer buffer_beg,
                       request_buffer buffer_end) 
            : request(request)
            , buffer_beg(buffer_beg)
            , buffer_end(buffer_end) {
        consume_request();
        check_request();
    }

    bool check_request() {
        return (check_http_version() && check_http_verb());
    }

private:
    Request request;
    request_buffer buffer_beg;
    request_buffer buffer_end;

    parser_state consume_request() {
        std::vector<parser_state> result;
        result.push_back(consume_method());
        result.push_back(consume_uri());
        result.push_back(consume_version());
        result.push_back(consume_headers());

        std::vector<parser_state>::iterator iter = result.begin();
        for (iter; iter != result.end(); ++iter)
            if (iter == failed)
                return failed;
        return completed;
    }

    parser_state consume_method() {
        parser_state result = consume(supported_methods, HTTP_VERB_MAX_LEN);
        if (result == failed)
            output_error("HTTP verb not supported");  // TODO: return response with 405 status code
        return result;
    }

    parser_state consume_uri() {
        std::string uri = "";
        while ((buffer_beg != ' ') && (buffer_beg != buffer_end))
            uri += buffer_beg++;
        if (!is_path_absolute(uri))
            return failed;
        request.uri = uri;
        return completed;
    }

    parser_state consume_version() {
        consume("HTTP/");
        request.http_version = buffer_beg++;
        consume(".");
        request.http_subversion = buffer_beg++;
        bool correctness = check_http_version();
        if (correctness) return completed;
        else return failed;
    }

    parser_state consume_headers() {
        while ((buffer_beg != '\n') && (buffer_beg+1 != '\n') &&
                (buffer_beg != buffer_end))
            consume_header();
        return completed;
    }

    parser_state consume_header() {
        Header header;
        while ((buffer_beg != ':') && (buffer_beg != buffer_end))
            header.name += buffer_beg++;

        while ((buffer_beg != '\n') && (buffer_beg != buffer_end))
            header.value += buffer_beg++;

        if (!check_header(header)) return failed;
        request.headers.push_back(header);
        return completed;
    }

    parser_state consume(const std::string token, int n) {
        int i=0;
        std::string result;
        while (i < n && buffer_beg != buffer_end) {
            result += buffer_beg++;
            if (result == token) return completed;
            i++;
        }
        return failed;
    }

    parser_state consume(const std::string array[], int n) {
        int i=0;
        std::string result;
        while (i < n && buffer_beg != buffer_end) {
            result += buffer_beg++;
            if (in_array(result, array)) return completed; 
            i++;
        }
        return failed;
    }

    bool check_header(Header header) {
        // TODO: check if header is valid
        return true;
    }

    bool check_http_version() {
        /* Supported HTTP version: 1.0 v 1.1 */
        if ((request.http_version != 1) ||
            (request.http_subversion != 0 ||
             request.http_subversion != 1)) {
            output_error("HTTP version not supported");  // TODO: return response with 505 status code
            return false;
        }
        return true;
    }

    bool check_http_verb(std::string verb) {
        for (int i; i < array_size(supported_methods); ++i)
            if (verb == supported_methods[i])
                return true;
        return false;
    }

    bool is_path_absolute(std::string path) {
        if (path.find("..") != std::string::npos ||
                path.empty() || 
                path[0] != '/')
            return false;
        return true;
    }
};

} // namespace webserver
#endif // WEBSERVER_REQUEST_PARSER_HPP
