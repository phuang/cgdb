#include <sys/epoll.h>
#include <unistd.h>

#include "main_loop.h"

int main() {
  MainLoop loop;

  loop.Run();
}
