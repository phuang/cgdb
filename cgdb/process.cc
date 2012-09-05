#include "cgdb/process.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

namespace {

char** SplitString(const char *str) {
  assert(str);

  int size = 32;
  char** p = static_cast<char**>(malloc(sizeof(char*) * size));
  int i = 0; 
  const char *p1 = str;

  while (*p1 != '\0') {
    while (*p1 == ' ')
      ++p1;
    const char* p2 = p1;

    while (*p2 != ' ' && *p2 != '\0') ++p2;
    if (i == size - 1) {
      size = size << 1;
      p = static_cast<char**>(realloc(p, sizeof(char*) * size));
    }
    p[i++] = strndup(p1, p2 - p1);
    p2 = p1;
  }
  p[i] = NULL;
  return p;
}

void FreeStrv(char** sv) {
  assert(sv);

  char** p = sv;
  while (*p)
    free(*p++);
  free(sv);
}

}

namespace cgdb {

Process::Process(pid_t pid, int fdin, int fdout, int fderr)
  : pid_(pid),
  stdin_(fdin),
  stdout_(fdout),
  stderr_(fderr) {
}

Process::~Process() {
}

Process* Process::Execute(const char* cmdline) {
  int fdin[2];
  int fdout[2];
  int fderr[2];

  assert(pipe(fdin) == 0);
  assert(pipe(fdout) == 0);
  assert(pipe(fderr) == 0);

  pid_t pid = fork();

  assert(pid != -1);

  if (pid != 0) {
    // Parent process
    close(fdin[0]);
    close(fdout[1]);
    close(fderr[1]);
    return new Process(pid, fdin[1], fdout[0], fderr[0]);
  } else {
    // Child process
    close(fdin[1]);
    close(fdout[0]);
    close(fderr[0]);

    for (int i = 0; i < 255; i++) {
      if (i != fdin[0] && i != fdout[1] && i != fderr[1])
        close(i);
    }

    assert(dup2(fdin[0], 0) == 0);
    close(fdin[0]);
    assert(dup2(fdout[1], 1) == 0);
    close(fdout[1]);
    assert(dup2(fderr[1], 2) == 0);
    close(fderr[1]);
    
    char** argv = SplitString(cmdline);
    assert(execvp(argv[0], argv) == 0);
    return NULL;
  }
}

}  // namespace cgdb
