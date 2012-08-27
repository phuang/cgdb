#include "main_loop.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <unistd.h>

#include <iostream>

MainLoop::MainLoop()
  : epfd_(-1),
    loop_level_(0) {
  epfd_ = epoll_create(1);
  if (epfd_ == -1) {
    perror("epoll_create");
    exit(EXIT_FAILURE);
  }
}

void MainLoop::Run() {
  assert(epfd_ != -1);

  int old_level = loop_level_++;
  struct epoll_event events[64];

  while(loop_level_> old_level) {
    int n = epoll_wait(epfd_, events, 64, -1);
    if (n == -1) {
      perror("epoll_wait");
      exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
      IOListenerMap::const_iterator it =
        io_listeners_.find(events[i].data.fd);
      
      if (it == io_listeners_.end()) {
        std::cerr << "Can not find fd in io_listeners_" << std::endl;
        continue;
      }
      it->second->OnEvent(events[i].data.fd, events[i].events);
    }
  }
}

void MainLoop::Quit() {
  if (loop_level_ > 0)
    loop_level_--;
}

bool MainLoop::IOAddWatch(
  int fd, unsigned int events, IOListener* listener) {
  assert(listener);
  assert(fd >= 0);
  assert(io_listeners_.find(fd) == io_listeners_.end());
  
  struct epoll_event ev;
  ev.events = events;
  ev.data.fd = fd;

  if (epoll_ctl(epfd_, EPOLL_CTL_ADD, fd, &ev) == -1) {
    std::cerr << "Add epoll failed." << std::endl;
    return false;
  }

  io_listeners_[fd] = listener;
  return true;
}

void MainLoop::IORemoveWatch(int fd) {
  assert(fd >= 0);
  assert(io_listeners_.find(fd) != io_listeners_.end());

  struct epoll_event ev;
  ev.data.fd = fd;

  io_listeners_.erase(fd);

  if (epoll_ctl(epfd_, EPOLL_CTL_DEL, fd, &ev) == -1) {
    std::cerr << "dell epoll failed." << std::endl;
  }
}

MainLoop::~MainLoop() {
  if (epfd_ != -1) {
    close(epfd_);
    epfd_ = -1;
  }

  if (loop_level_ != 0)
    std::cerr << "loop level is not 0!" << std::endl;
}
