#ifndef MAIN_LOOP_H
#define MAIN_LOOP_H

#include <map>

class IOListener {
 public:
  virtual bool OnEvent(int fd, unsigned int event) = 0;
};

class MainLoop {
 public:
  MainLoop();
  ~MainLoop();

  void Run();
  void Quit();

  bool IOAddWatch(int fd, unsigned int event, IOListener* listener);
  void IORemoveWatch(int fd);

 private:
  typedef std::map<int, IOListener*> IOListenerMap;

  int epfd_;
  int loop_level_;

  IOListenerMap io_listeners_;
};

#endif // MAIN_LOOP_H
