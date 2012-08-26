#ifndef MAIN_LOOP_H
#define MAIN_LOOP_H

class MainLoop {
 public:
  MainLoop();
  ~MainLoop();

  void Run();
  void Quit();

 private:
  int epfd_;
  int loop_level_;
};

#endif // MAIN_LOOP_H
