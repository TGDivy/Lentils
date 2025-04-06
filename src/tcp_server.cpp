// Simple TCP Echo Server (Minimal Template)
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>

int main() {
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);

  sockaddr_in address{};
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(8080); // Listen on port 8080

  auto rc = bind(server_fd, (sockaddr *)&address, sizeof(address));
  listen(server_fd, 3);

  std::cout << "TCP Echo Server listening on port 8080...\n";

  int addrlen = sizeof(address);
  int new_socket =
      accept(server_fd, (sockaddr *)&address, (socklen_t *)&addrlen);

  char buffer[1024] = {0};
  int valread = read(new_socket, buffer, 1024);
  std::cout << "Received: " << buffer << "\n";

  send(new_socket, buffer, strlen(buffer), 0);
  close(new_socket);
  close(server_fd);
  return 0;
}
