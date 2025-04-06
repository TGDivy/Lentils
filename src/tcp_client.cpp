// Simple TCP Echo Client (Minimal Template)
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <unistd.h>

int main() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);

  sockaddr_in serv_addr{};
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(8080);

  if (auto rc = inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr); rc <= 0) {
    return rc;
  }

  auto rc = connect(sock, (sockaddr *)&serv_addr, sizeof(serv_addr));

  const char *message = "Hello, Echo Server!";
  send(sock, message, strlen(message), 0);

  char buffer[1024] = {0};
  int valread = read(sock, buffer, 1024);
  std::cout << "Echoed back: " << buffer << "\n";

  close(sock);
  return 0;
}
