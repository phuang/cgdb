#ifndef CGDB_SOURCE_H
#define CGDB_SOURCE_H

class Source {
 public:
  Source();
  virtual ~Source();

  int fd() { return fd; }

  virtual bool Prepare(int* timeout) = 0;
  virtual bool Dispatch() = 0;
 
  private:
   int fd_;
};

#endif // SOURCE_H
