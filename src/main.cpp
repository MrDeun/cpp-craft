#include <asio.hpp>
#include <print>

import mc.protocol.buffer;

int main(int argc, char **argv) {
  asio::io_context io;
  asio::ip::tcp::acceptor acceptor(
      io, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 25565));
  Buffer buf{};
  std::println("Listening on port {}", acceptor.local_endpoint().port());
  io.run();
  return 0;
}
