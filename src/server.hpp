#ifndef WEBSERVER_SERVER_HPP
#define WEBSERVER_SERVER_HPP

#include <boost/asio.hpp>


namespace webserver {

class Server {
public:
	Server(int thread_count=1)
			: thread_count_(thread_count)
		  	, acceptor_(io_service_) {
	}
private:
	int thread_count_;
	std::vector<std::thread> thread_poll_;
	boost::asio::io_service io_service_;
	boost::asio::ip::tcp::acceptor acceptor_;
};

} // namespace webserver

#endif //WEBSERVER_SERVER_HPP
