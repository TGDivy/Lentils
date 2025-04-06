
#include "utils.h"
#include <arpa/inet.h>
#include <cstdio>
#include <cstring>
#include <format>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <string_view>

int main(int argc, char *argv[]) {
  struct addrinfo hints, *res;
  int status;

  if (argc != 2) {
    std::cerr << "usage: showip hostname\n";
    return 1;
  }

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  {
    ScopedTimer timer("getaddrinfo");
    status = getaddrinfo(argv[1], nullptr, &hints, &res);
  }

  if (status != 0) {
    std::cerr << std::format("getaddrinfo: {}\n", gai_strerror(status));
    return 2;
  }

  std::cout << std::format("IP addresses for: {}\n", argv[1]);

  char ipstr[INET6_ADDRSTRLEN];
  for (addrinfo *p = res; p != NULL; p = p->ai_next) {
    void *addr;
    std::string ipver;

    if (p->ai_family == AF_INET) {
      auto *ipv4 = reinterpret_cast<sockaddr_in *>(p->ai_addr);
      addr = &(ipv4->sin_addr);
      ipver = "IPv4";
    } else if (p->ai_family == AF_INET6) {
      auto *ipv6 = reinterpret_cast<sockaddr_in6 *>(p->ai_addr);
      addr = &(ipv6->sin6_addr);
      ipver = "IPv6";
    } else {
      std::cerr << std::format("Unknown ai_family: {}\n", p->ai_family);
      continue;
    }

    if (inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr)) == nullptr) {
      std::cerr << std::format("inet_ntop error: {}\n", strerror(errno));
      continue;
    }

    std::cout << std::format("\t{}: {}\n", ipver, std::string_view(ipstr));
  }

  freeaddrinfo(res);

  return 0;
}
