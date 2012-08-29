#include <sys/epoll.h>
#include <unistd.h>

#include "cgdb/main_loop.h"

int main() {
  MainLoop loop;

  loop.Run();
}
