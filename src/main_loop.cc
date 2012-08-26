#include "main_loop.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <unistd.h>

#include <iostream>


MainLoop::MainLoop()
  : epfd_(-1),
    loop_level_(0) {
}

void MainLoop::Run() {
  if (epfd_ == -1) {
    epfd_ = epoll_create(1);
    if (epfd_ == -1) {
      perror("epoll_create");
      exit(EXIT_FAILURE);
    }
  }
  
  int old_level = loop_level_++;
  struct epoll_event events[64];
  while(loop_level_> old_level) {
    int n = epoll_wait(epfd_, events, 64, -1);
    if (n == -1) {
      perror("epoll_wait");
      exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
    }
  }
}

void MainLoop::Quit() {
  if (loop_level_ > 0)
    loop_level_--;
}

MainLoop::~MainLoop() {
  if (epfd_ != -1) {
    close(epfd_);
    epfd_ = -1;
  }

  if (loop_level_ != 0)
    std::cerr << "loop level is not 0!" << std::endl;
}
