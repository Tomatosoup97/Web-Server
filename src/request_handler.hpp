#ifndef WEBSERVER_REQUEST_HANDLER_HPP
#define WEBSERVER_REQUEST_HANDLER_HPP

#include <string>
#include <fstream>
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
        std::string request_uri = create_uri(&request, &response);
        if (request_uri == "") return;
        std::string extension = get_extension(request_uri);

        std::fstream server_file = open_file(location_ + request_uri);
        if (!server_file) {
            response = Response::response(status::HTTP_404_NOT_FOUND);
            return;
        }
        response = Response::response(status::HTTP_200_OK,
                                      status::get_mime_type(extension));
        write_data_stream(response, server_file);
    }

private:
    std::string location_;

    std::string create_uri(Request *request, Response *response) {
        std::string request_uri;
        try {
            request_uri = url_decode(request->uri);
        }
        catch (const std::exception& e) {
            *response = Response::response(status::HTTP_400_BAD_REQUEST);
            return "";
        }
        request_uri = append_web_page(request_uri);
        return request_uri;
    }

    static std::string get_extension(std::string request_uri) {
        std::size_t last_dot_pos = request_uri.find_last_of(".");
        std::string extension = request_uri.substr(last_dot_pos + 1);
        return extension;
    }

    static void write_data_stream(Response &response, std::fstream file) {
        // TODO: Examine cases where files are very big
        char buffer[RESPONSE_CHUNK_SIZE];
        while (file.read(buffer, sizeof(buffer)).gcount() > 0)
            response.content.append(buffer, file.gcount());
    }

    static std::string append_web_page(std::string path) {
        /* Append default web page if path is a directory */
        if (path[path.size() - 1] == '/')
            path += DEFAULT_WEB_PAGE;
        return path;
    }

    static std::string url_decode(std::string str) {
        // TODO: implement
        return str;
    }

    static std::fstream open_file(std::string path) {
        std::fstream file(path.c_str(), std::ios::in | std::ios::binary);
        return file;
    }
};

} // namespace webserver

#endif // WEBSERVER_REQUEST_HANDLER_HPP
