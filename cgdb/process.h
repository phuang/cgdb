#ifndef CGDB_PROCESS_H
#define CGDB_PROCESS_H

class Process {
 public:
  ~Process();
  static Process* Execute(const char* cmdline);

 private:
  Process();

 private:
  int stdin_;
  int stdout_;
  int stderr_;
};

#endif // CGDB_PROCESS_H
