#ifndef HTTP_SERVER3_REQUEST_HANDLER_HPP
#define HTTP_SERVER3_REQUEST_HANDLER_HPP

#include <string>
#include <ifstream>
#include "request.hpp"
#include "response.hpp"
#include "status_code.hpp"


namespace webserver {

#define DEFAULT_WEB_PAGE "index.html"
#define RESPONSE_CHUNK_SIZE 512


class RequestHandler {
public:
    RequestHandler(std::string &location) : location_(location) {
    }

    void handle(Request request, Response response) {
        // TODO: Refactor
        try {
            std::string request_uri = url_decode(request.uri);
            is_path_absolute(request_uri);
        }
        catch (const std::exception& e) {
            response = Response::response(status::HTTP_400_BAD_REQUEST);
            return;
        }
        // Append default web page if path is a directory
        if (request_uri[request_uri.size() - 1] == '/') {
            request_uri += DEFAULT_WEB_PAGE;
        }
        std::size_t last_dot_pos = request_path.find_last_of(".")
        std::string extension = request_uri.substr(last_dot_pos + 1);

        // Open the file specified in path
        std::string full_path = doc_root_ + request_path;
        std::ifstream server_file(full_path.c_str(), std::ios::in | std::ios::binary);
        if (!server_file) {
            response = Response::response(status::HTTP_404_NOT_FOUND);
            return;
        }

        // Write data stream to response
        // TODO: Examine cases where files are very big
        response = Response::response(status::HTTP_200_OK,
                                      status::get_mime_type(extension);
        char buffer[RESPONSE_CHUNK_SIZE];
        while (server_file.read(buffer, sizeof(buffer)).gcount() > 0)
            response.content.append(buffer, server_file.gcount());
    }

private:
    std::string location_;

    static std::string url_decode(std::string str) {
        // TODO: implement
        return str;
    }

    bool is_path_absolute(std::string path) {
        // TODO: check if path is absolute
        return true;
    }
};

} // namespace webserver

#endif // HTTP_SERVER3_REQUEST_HANDLER_HPP
