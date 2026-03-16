#include <iostream>
#include <asio.hpp>
#include <print>
int main(int argc, char** argv) {
    asio::io_context io;
    asio::ip::tcp::acceptor acceptor(
        io,
        asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 25565)
    );

    std::println("Listening on port {}",acceptor.local_endpoint().port());
    io.run();
    return 0;
}
    