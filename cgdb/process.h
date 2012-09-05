#ifndef CGDB_PROCESS_H
#define CGDB_PROCESS_H

#include <unistd.h>

namespace cgdb {

class Process {
 public:
  ~Process();
  static Process* Execute(const char* cmdline);

 private:
  Process(pid_t pid, int fdin, int fdout, int fderr);

 private:
  pid_t pid_;
  int stdin_;
  int stdout_;
  int stderr_;
};

}  // namespace cgdb

#endif // CGDB_PROCESS_H
