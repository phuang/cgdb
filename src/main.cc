#include <sys/epoll.h>
#include <unistd.h>

#include <iostream>


int main() {
    int fd = epoll_create(0);
    close(fd);
}
